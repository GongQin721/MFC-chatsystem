// SendFilesClientThread.cpp : implementation file
//

#include "stdafx.h"
#include "instantmessaging.h"
#include "SendFilesClientThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSendFilesClientThread

IMPLEMENT_DYNCREATE(CSendFilesClientThread, CWinThread)

CSendFilesClientThread::CSendFilesClientThread()
{
	m_bStop				= FALSE;
	m_bRun				= TRUE;
	m_dwReceiveCount	= 0;
}

CSendFilesClientThread::~CSendFilesClientThread()
{
}

BOOL CSendFilesClientThread::InitInstance()
{
	/// 设置与socket对应的线程	
	m_receiveFilesSocket.SetSendFileClientThread( this );

	/// 接收文件的首次判断，是重新接收还是继续传输
	CFileFind fileFind;
	
	/// 配置文件存在，读取信息
	/// 配置文件内容：MAX_PATH（保存路径）+DWORD（长度）+DWORD（已接收长度）
	if( fileFind.FindFile( m_strConfig ) )
	{
		CFile fileCfg( m_strConfig, CFile::modeRead | CFile::typeBinary );
		char szData[ MAX_PATH + 2 * sizeof( DWORD ) ];
		fileCfg.Read( szData, MAX_PATH + 2 * sizeof( DWORD ) );
		fileCfg.Close();

		/// 读取信息
		CString strDesPath;
		DWORD dwLength;
		DWORD dwReceived;
		memcpy( strDesPath.GetBuffer( MAX_PATH ), szData, MAX_PATH );
		strDesPath.ReleaseBuffer( -1 );
		memcpy( &dwLength, szData + MAX_PATH, sizeof( DWORD ) );
		memcpy( &dwReceived, szData + MAX_PATH + sizeof( DWORD ), sizeof( DWORD ) );

		/// 查找已接收文件是否存在，大不是否大于已接收到的长度
		CFileFind fileFind1;
		if( fileFind1.FindFile( m_strDesPath ) 
			&& m_dwLength == dwLength 
			&& m_strDesPath == strDesPath )
		{
			CFile file( m_strDesPath, CFile::modeRead | CFile::typeBinary );
			
			/// 文件的长度大于或等于配置文件中接收到的文件长度
			if( file.GetLength() >= dwReceived )
			{
				m_dwReceived = dwReceived;
			}
			file.Close();
		}
		fileFind1.Close();
	}
	fileFind.Close();

	/// 打开文件并设置长度，定位到写的位置
	m_fileSave.Open( m_strDesPath, CFile::modeWrite | CFile::typeBinary | CFile::modeNoTruncate | CFile::modeCreate );
	m_fileSave.SetLength( m_dwReceived );
	m_fileSave.Seek( m_dwReceived, CFile::begin );

	/// 找开配置文件
	m_fileCfg.Open( m_strConfig, CFile::modeWrite | CFile::typeBinary | CFile::modeNoTruncate | CFile::modeCreate );

	/// 发送SENDFILES_FILEINFO给发送者
	DATAPACKET dataPacket;
	dataPacket.command = SENDFILES_FILEINFO;
	UINT uDataLength = sizeof( DATAPACKET ) + MAX_PATH + 2 * sizeof( DWORD );
	BYTE *pSendData = new BYTE[ uDataLength ];
	memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
	memcpy( pSendData + sizeof( DATAPACKET ), m_strSourcePath.GetBuffer( MAX_PATH ), MAX_PATH );
	m_strSourcePath.ReleaseBuffer( -1 );
	memcpy( pSendData + sizeof( DATAPACKET ) + MAX_PATH, &m_dwLength, sizeof( DWORD ) );
	memcpy( pSendData + sizeof( DATAPACKET ) + MAX_PATH + sizeof( DWORD ), &m_dwReceived, sizeof( DWORD ) );
	m_receiveFilesSocket.Send( pSendData, uDataLength );
	delete pSendData;

	while( m_bRun )
	{
		Sleep( 1 );
	}
	return TRUE;
}

int CSendFilesClientThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CSendFilesClientThread, CWinThread)
	//{{AFX_MSG_MAP(CSendFilesClientThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSendFilesClientThread message handlers

/// 附加套接字
void CSendFilesClientThread::AttachSocket( SOCKET hSocket )
{
	m_receiveFilesSocket.Attach( hSocket );
}

/// 接收网络数据
void CSendFilesClientThread::OnReceive()
{
	char szReceive[ MAXDATAPACKETLENGTH ];
	m_receiveFilesSocket.Receive( szReceive, MAXDATAPACKETLENGTH );

	/// 装配数据包
	DATAPACKET dataPacket;
	memcpy( &dataPacket, szReceive, sizeof( DATAPACKET ) );
	
	switch( dataPacket.command )
	{
	case SENDFILES_RESPONSE:									/// 接收数据
		ReceiveData( szReceive );
		break;
	case SENDFILES_BEGIN:										/// 通知接收者开始发送接收消息
		SendReceiveMessage( m_dwReceived );
		break;
	default:
		break;
	}
}

/// 发送请求文件的消息
void CSendFilesClientThread::SendReceiveMessage( DWORD dwReceived )
{
	DATAPACKET dataPacket;

	/// 如果收到的长度与总长度相等，则接收完毕
	if( dwReceived == m_dwLength )
	{
		m_fileSave.Close();
		m_fileCfg.Close();
		CFile::Remove( m_strConfig );
		dataPacket.command = SENDFIELS_DONE;
		UINT uDataLength = sizeof( DATAPACKET );
		BYTE *pSendData = new BYTE[ uDataLength ];
		memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
		m_receiveFilesSocket.Send( pSendData, uDataLength );
		delete pSendData;
		m_receiveFilesSocket.Close();
		m_pDlgSendFilesClient->RefreshListBox();
		m_bRun = FALSE;
		return;
	}

	/// 还未接收完毕
	dataPacket.command = SENDFILES_REQUEST;
	UINT uDataLength = sizeof( DATAPACKET ) + sizeof( DWORD );
	BYTE *pSendData = new BYTE[ uDataLength ];
	memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
	memcpy( pSendData + sizeof( DATAPACKET ), &dwReceived, sizeof( DWORD ) );
	m_receiveFilesSocket.Send( pSendData, uDataLength );
	delete pSendData;
}

/// 接收数据
void CSendFilesClientThread::ReceiveData( LPCSTR szReceive )
{
	DATAPACKET dataPacket;
	memcpy( &dataPacket, szReceive, sizeof( DATAPACKET ) );

	BYTE * pCompressData	= new BYTE[ dataPacket.dwLength ];
	memcpy( pCompressData, szReceive + sizeof( DATAPACKET ), dataPacket.dwLength );
	
	m_fileSave.Write( pCompressData, dataPacket.dwLength );
	m_dwReceiveCount += dataPacket.dwLength;

	m_dwReceived += dataPacket.dwLength;

	BYTE * pData = new BYTE[ MAX_PATH + 2 * sizeof( DWORD ) ];
	memcpy( pData, m_strDesPath.GetBuffer( MAX_PATH ), MAX_PATH );
	m_strDesPath.ReleaseBuffer( -1 );
	memcpy( pData + MAX_PATH, &m_dwLength, sizeof( DWORD ) );
	memcpy( pData + MAX_PATH + sizeof( DWORD ), &m_dwReceived, sizeof( DWORD ) );

	m_fileCfg.SeekToBegin();
	m_fileCfg.Write( pData, MAX_PATH + 2 * sizeof( DWORD ) );

	delete pData;

	delete pCompressData;

	/// 发送继续接收数据的消息
	SendReceiveMessage( m_dwReceived );
}

/// 删除传输线程
void CSendFilesClientThread::StopReceive()
{
	m_receiveFilesSocket.Close();
	m_fileCfg.Close();
	m_fileSave.Close();
	m_bRun = FALSE;
}

/// 关闭连接
void CSendFilesClientThread::OnClose()
{
	m_receiveFilesSocket.Close();
	m_fileCfg.Close(); 
	m_fileSave.Close();
	m_bStop = TRUE;
	m_pDlgSendFilesClient->RefreshListBox();
	m_bRun	= FALSE;
}