// SendFilesServerThread.cpp : implementation file
//

#include "stdafx.h"
#include "instantmessaging.h"
#include "SendFilesServerThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSendFilesServerThread

IMPLEMENT_DYNCREATE(CSendFilesServerThread, CWinThread)

CSendFilesServerThread::CSendFilesServerThread()
{
	m_bStop			= FALSE;
	m_dwSendCount	= 0;
}

CSendFilesServerThread::~CSendFilesServerThread()
{
}

BOOL CSendFilesServerThread::InitInstance()
{
	/// 设置与socket对应的线程
	m_sendFilesSocket.SetSendFileServerThread( this );

	while( m_bRun )
	{
		Sleep( 1 );
	}
	return TRUE;
}

int CSendFilesServerThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CSendFilesServerThread, CWinThread)
	//{{AFX_MSG_MAP(CSendFilesServerThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSendFilesServerThread message handlers

/// 附加套接字
void CSendFilesServerThread::AttachSocket( SOCKET hSocket )
{
	m_sendFilesSocket.Attach( hSocket );
}

/// 接收网络数据
void CSendFilesServerThread::OnReceive()
{
	char szReceive[ MAXDATAPACKETLENGTH ];
	m_sendFilesSocket.Receive( szReceive, MAXDATAPACKETLENGTH );

	/// 装配数据包
	DATAPACKET dataPacket;
	memcpy( &dataPacket, szReceive, sizeof( DATAPACKET ) );
	
	switch( dataPacket.command )
	{
	case SENDFILES_REQUEST:									/// 接收数据的请求
		SendData( szReceive );
		break;
	case SENDFILES_FILEINFO:								/// 设置发送文件
		SetInfo( szReceive );
		break;
	case SENDFIELS_DONE:									/// 接收完毕
		m_dwSended = m_dwLength;
		m_fileSend.Close();
		m_sendFilesSocket.Close();
		m_pDlgSendFileServer->RefreshListBox();
		m_bRun = FALSE;
		break;
	default:
		break;
	}
}

/// 设置
void CSendFilesServerThread::SetInfo( LPCSTR szReceive )
{
	DATAPACKET dataPacket;
	memcpy( &dataPacket, szReceive, sizeof( DATAPACKET ) );

	CString strSourcePath;
	DWORD	dwLength;
	DWORD	dwSended;
  
	memcpy( strSourcePath.GetBuffer( MAX_PATH ), szReceive + sizeof( DATAPACKET ), MAX_PATH );
	strSourcePath.ReleaseBuffer( -1 );
	memcpy( &dwLength, szReceive + sizeof( DATAPACKET ) + MAX_PATH, sizeof( DWORD ) );
	memcpy( &dwSended, szReceive + sizeof( DATAPACKET ) + MAX_PATH + sizeof( DWORD ), sizeof( DWORD ) );

	m_strSourcePath	= strSourcePath;
	m_dwLength		= dwLength;
	m_dwSended		= dwSended;
	m_dwSendCount	= 0;
	CString strIP;
	UINT uPort;
	m_sendFilesSocket.GetPeerName( strIP, uPort );
	memcpy( m_szDesIP, strIP, 16 );

	m_fileSend.Open( m_strSourcePath, CFile::modeRead | CFile::typeBinary );
	m_fileSend.Seek( dwSended, CFile::begin );

	/// 发送给接收者开始发送接收的消息
	dataPacket.command = SENDFILES_BEGIN;
	UINT uDataLength = sizeof( DATAPACKET );
	BYTE *pSendData = new BYTE[ uDataLength ];
	memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
	m_sendFilesSocket.Send( pSendData, uDataLength );
	delete pSendData;
}

/// 发送数据
void CSendFilesServerThread::SendData( LPCSTR szReceive )
{
	DWORD dwSended;
	memcpy( &dwSended, szReceive + sizeof( DATAPACKET ), sizeof( DWORD ) );
	m_dwSended = dwSended;

	DWORD dwReadLength = MAXDATAPACKETLENGTH - sizeof( DATAPACKET );
	if( dwSended + dwReadLength > m_dwLength )
	{
		dwReadLength = m_dwLength - dwSended;
	}
	m_dwSendCount += dwReadLength;
	BYTE * pUnCompressData = new BYTE[ dwReadLength ];

	/// 读取数据并发送
	m_fileSend.Read( pUnCompressData, dwReadLength );

	DATAPACKET dataPacket;
	dataPacket.command	= SENDFILES_RESPONSE;
	dataPacket.dwLength	= dwReadLength;

	UINT uDataLength = sizeof( DATAPACKET ) + dwReadLength;
	BYTE *pSendData = new BYTE[ uDataLength ];
	memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
	memcpy( pSendData + sizeof( DATAPACKET ), pUnCompressData, dwReadLength );
	m_sendFilesSocket.Send( pSendData, uDataLength );
	
	delete pSendData;
	delete pUnCompressData;
}

/// 删除传输线程
void CSendFilesServerThread::StopSend()
{	
	m_sendFilesSocket.Close();
	m_fileSend.Close();
	m_bRun = FALSE;
}

/// 关闭连接
void CSendFilesServerThread::OnClose()
{
	m_sendFilesSocket.Close();
	m_fileSend.Close();
	m_bStop = TRUE;
	m_pDlgSendFileServer->RefreshListBox();
	m_bRun	= FALSE;
}