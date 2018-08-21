

#include "stdafx.h"
#include "instantmessaging.h"
#include "SendFilesClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



#include "InstantMessagingDlg.h"
#include "ReceiveFilesSocket.h"
#include "SendFilesClientThread.h"

CSendFilesClientDlg::CSendFilesClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSendFilesClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSendFilesClientDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSendFilesClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSendFilesClientDlg)
	DDX_Control(pDX, IDC_LIST_RECEIVE, m_listCtrlReceive);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSendFilesClientDlg, CDialog)
	//{{AFX_MSG_MAP(CSendFilesClientDlg)
	ON_BN_CLICKED(IDB_DELETE, OnDelete)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSendFilesClientDlg message handlers

BOOL CSendFilesClientDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	/// 初始化
	Init();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/// 初始化
void CSendFilesClientDlg::Init()
{
	/// 获取主对话框
	m_pMainDlg = ( CInstantMessagingDlg * )::AfxGetMainWnd();

	/// 初始化发送文件列表框
	m_listCtrlReceive.SetExtendedStyle( m_listCtrlReceive.GetExtendedStyle() | 
		LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES );

	m_listCtrlReceive.InsertColumn( 0, "文件", LVCFMT_LEFT, 275 );
	m_listCtrlReceive.InsertColumn( 1, "大小", LVCFMT_LEFT, 70 );
	m_listCtrlReceive.InsertColumn( 2, "已完成", LVCFMT_LEFT, 70 );
	m_listCtrlReceive.InsertColumn( 3, "速度", LVCFMT_LEFT, 80 );
	m_listCtrlReceive.InsertColumn( 4, "进度", LVCFMT_LEFT, 40 );
	m_listCtrlReceive.InsertColumn( 5, "发送者", LVCFMT_LEFT, 130 );

	/// 获取时间
	m_ulTime = ::GetTickCount();

	/// 设置刷新文件列表框的定时器
	SetTimer( TIMER_SENDFILES_REFRESH, 1000, NULL );
}

/// 从指定IP接收数据
void CSendFilesClientDlg::ReceiveFileFromIP( CString strFilePath, LPCSTR szIP, DWORD dwLength )
{
	CString strFile = strFilePath.Right( strFilePath.GetLength() - 1 - strFilePath.ReverseFind( '\\' ) );
	CString strSub	= strFile.Right( strFile.GetLength() - 1 - strFile.ReverseFind( '.' ) );

	CString strFilter = "*." + strSub + "|*." + strSub + "||";
	CFileDialog fileDlg( FALSE, NULL, strFile,  OFN_OVERWRITEPROMPT, strFilter, NULL );
	if( IDCANCEL == fileDlg.DoModal() )
	{
		m_pMainDlg->DenyReceiveFile( strFilePath, szIP );
		return;
	}

	/// 得到保存的路径
	CString strDesPath = fileDlg.GetPathName();
	
	/// 如果列表中有，则先删除
	for( int nListFileIndex = 0; nListFileIndex < m_listCtrlReceive.GetItemCount(); nListFileIndex++ )
	{
		CString strFilePathTmp	= m_listCtrlReceive.GetItemText( nListFileIndex, 0 );
		CString strReceiveIP	= m_listCtrlReceive.GetItemText( nListFileIndex, 5 );
		strReceiveIP			= strReceiveIP.Right( strReceiveIP.GetLength() 
			- 1 
			- strReceiveIP.ReverseFind( '(' ) );
		strReceiveIP			= strReceiveIP.Left( strReceiveIP.GetLength() - 1 );
		
		if( strFilePathTmp == strDesPath && strReceiveIP == szIP )
		{
			m_listCtrlReceive.DeleteItem( nListFileIndex );
			break;
		}
	}


	CReceiveFilesSocket rfSocket;

	CSendFilesClientThread *pSFCThread = ( CSendFilesClientThread * )AfxBeginThread( RUNTIME_CLASS( CSendFilesClientThread ),
		0,
		0,
		CREATE_SUSPENDED,
		NULL );
	
	rfSocket.Create();
	rfSocket.Connect( szIP, SENDFILESSERVER_PORT );

	pSFCThread->SetSendFilesClientDlg( this );
	pSFCThread->AttachSocket( rfSocket.Detach() );
	pSFCThread->SetInfo( strFilePath, strDesPath, dwLength, szIP );
	pSFCThread->ResumeThread();

	m_listCtrlReceive.InsertItem( m_listCtrlReceive.GetItemCount(), strDesPath, 0 );
	CString strLength;
	if( dwLength > pow( 1024, 3 ) )
	{
		float fLength = dwLength / pow( 1024, 3 );
		strLength.Format( "%.2fGB", fLength );
	}
	else if( dwLength > pow( 1024, 2 ) )
	{
		float fLength = dwLength / pow( 1024, 2 );
		strLength.Format( "%.2fMB", fLength );
	}
	else if( dwLength > 1024 )
	{
		float fLength = dwLength / 1024;
		strLength.Format( "%.2fKB", fLength );
	}
	else
	{
		strLength.Format( "%dB", dwLength );
	}
	
	m_listCtrlReceive.SetItemText( m_listCtrlReceive.GetItemCount() - 1, 1, strLength );
	m_listCtrlReceive.SetItemText( m_listCtrlReceive.GetItemCount() - 1, 2, "0" );
	m_listCtrlReceive.SetItemText( m_listCtrlReceive.GetItemCount() - 1, 3, "..." );
	m_listCtrlReceive.SetItemText( m_listCtrlReceive.GetItemCount() - 1, 4, "0%" );

	USER user;
	m_pMainDlg->GetUserFromIP( szIP, user );
	CString strSender;
	strSender.Format( "%s(%s)", user.strName, user.strIP );
	m_listCtrlReceive.SetItemText( m_listCtrlReceive.GetItemCount() - 1, 5, strSender );

	m_arrReceiveThread.Add( pSFCThread );
}

void CSendFilesClientDlg::OnTimer(UINT nIDEvent) 
{
	switch( nIDEvent )
	{
	case TIMER_SENDFILES_REFRESH:								/// 更新文件列表框
		RefreshListBox();
		break;
	default:
		break;
	}
	CDialog::OnTimer(nIDEvent);	
}

	/// 更新列表框
void CSendFilesClientDlg::RefreshListBox()
{
	unsigned long ulTime	= ::GetTickCount();
	unsigned long ulErased	= ulTime - m_ulTime;
	m_ulTime = ulTime;

	for( int nThreadIndex = 0; nThreadIndex < m_arrReceiveThread.GetSize(); nThreadIndex++ )
	{
		CSendFilesClientThread * pSFCThread = ( CSendFilesClientThread * )m_arrReceiveThread.GetAt( nThreadIndex );
		CString strFilePath = pSFCThread->GetDesFilePath();

		for( int nListFileIndex = 0; nListFileIndex < m_listCtrlReceive.GetItemCount(); nListFileIndex++ )
		{
			CString strFilePathTmp	= m_listCtrlReceive.GetItemText( nListFileIndex, 0 );
			CString strReceiveIP	= m_listCtrlReceive.GetItemText( nListFileIndex, 5 );
			strReceiveIP			= strReceiveIP.Right( strReceiveIP.GetLength() 
				- 1 
				- strReceiveIP.ReverseFind( '(' ) );
			strReceiveIP			= strReceiveIP.Left( strReceiveIP.GetLength() - 1 );

			if( strFilePathTmp == strFilePath && strReceiveIP == pSFCThread->GetIP() )
			{
				/// 此线程停止接收文件
				if( pSFCThread->GetStop() )
				{
					m_listCtrlReceive.SetItemText( nListFileIndex, 3, "停止" );
					
					/// 从线程列表中删除
					m_arrReceiveThread.RemoveAt( nThreadIndex );
					break;
				}

				/// 更新此行的已完成
				CString strReceived;
				DWORD dwReceived = pSFCThread->GetReceived();
				if( dwReceived > pow( 1024, 3 ) )
				{
					float fReceived = dwReceived / pow( 1024, 3 );
					strReceived.Format( "%.2fGB", fReceived );
				}
				else if( dwReceived > pow( 1024, 2 ) )
				{
					float fReceived = dwReceived / pow( 1024, 2 );
					strReceived.Format( "%.2fMB", fReceived );
				}
				else if( dwReceived > 1024 )
				{
					float fReceived = dwReceived / 1024;
					strReceived.Format( "%.2fKB", fReceived );
				}
				else
				{
					strReceived.Format( "%dB", dwReceived );
				}
				m_listCtrlReceive.SetItemText( nListFileIndex, 2, strReceived );

				/// 更新速度
				DWORD dwReceiveCount	= pSFCThread->GetReceiveCount();
				float fSpeed			= dwReceiveCount * 1000 / ulErased;
				CString strSpeed;
				if( fSpeed > pow( 1024, 2 ) )
				{
					float fSpeed1 = fSpeed / pow( 1024, 2 );
					strSpeed.Format( "%.2fMB/S", fSpeed1 );
				}
				else if( fSpeed > 1024 )
				{
					float fSpeed1 = fSpeed / 1024;
					strSpeed.Format( "%.2fKB/S", fSpeed1 );
				}
				else
				{
					strSpeed.Format( "%.2fB/S", fSpeed );
				}
				m_listCtrlReceive.SetItemText( nListFileIndex, 3, strSpeed );
				
				/// 更新进度
				CString strPercent;
				int nPercent = 100;
				if( 0 != pSFCThread->GetLength() / 100 )
				{
					nPercent = 100 * ( pSFCThread->GetReceived() / 100 ) / ( pSFCThread->GetLength() / 100 ) ;
				}
				strPercent.Format( "%d%%", nPercent );
				m_listCtrlReceive.SetItemText( nListFileIndex, 4, strPercent );

				/// 已完成传输
				if( pSFCThread->GetReceived() == pSFCThread->GetLength() )
				{
					/// 播放声音
					::PlaySound( "sendfilecomplete.wav", NULL, SND_FILENAME | SND_ASYNC);

					m_listCtrlReceive.SetItemText( nListFileIndex, 3, "完成" );
					m_listCtrlReceive.SetItemText( nListFileIndex, 4, "100%" );
					
					/// 从线程列表中删除
					m_arrReceiveThread.RemoveAt( nThreadIndex );
				}
				
				break;
			}
		}
	}
}

void CSendFilesClientDlg::OnDelete() 
{
		/// 提示
	if( IDCANCEL == MessageBox( "您确定要停止传输这些文件吗？", "停止传输", MB_OKCANCEL | MB_ICONINFORMATION | MB_DEFBUTTON2 ) )
	{
		return;
	}

	for( int nListFileIndex = 0; nListFileIndex < m_listCtrlReceive.GetItemCount(); nListFileIndex++ )
	{
		/// 没有选中这项
		if( !m_listCtrlReceive.GetCheck( nListFileIndex ) )
		{
			continue;
		}

		/// 拒绝接收的直接从列表中删除
		if( m_listCtrlReceive.GetItemText( nListFileIndex, 3 ) == "完成"
			|| m_listCtrlReceive.GetItemText( nListFileIndex, 3 ) == "停止" )
		{
			m_listCtrlReceive.DeleteItem( nListFileIndex-- );
			continue;
		}

		/// 查找与选中正在传输的线程
		for( int nThreadIndex = 0; nThreadIndex < m_arrReceiveThread.GetSize(); nThreadIndex++ )
		{
			CSendFilesClientThread * pSFCThread = ( CSendFilesClientThread * )m_arrReceiveThread.GetAt( nThreadIndex );
			CString strFilePath = pSFCThread->GetDesFilePath();
			
			CString strFilePathTmp	= m_listCtrlReceive.GetItemText( nListFileIndex, 0 );
			CString strReceiveIP	= m_listCtrlReceive.GetItemText( nListFileIndex, 5 );
			strReceiveIP			= strReceiveIP.Right( strReceiveIP.GetLength() 
				- 1 
				- strReceiveIP.ReverseFind( '(' ) );
			strReceiveIP			= strReceiveIP.Left( strReceiveIP.GetLength() - 1 );
			
			/// 线程与列表中的项相关
			if( strFilePathTmp == strFilePath && strReceiveIP == pSFCThread->GetIP() )
			{	
				pSFCThread->StopReceive();
				m_arrReceiveThread.RemoveAt( nThreadIndex-- );
				m_listCtrlReceive.DeleteItem( nListFileIndex-- );
				break;
			} 
		}
	}
}
