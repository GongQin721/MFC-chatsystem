// ChatDlg.cpp : implementation file
//

#include "stdafx.h"
#include "instantmessaging.h"
#include "ChatDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChatDlg dialog

#include "InstantMessagingDlg.h"

CChatDlg::CChatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChatDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChatDlg)
	DDX_Control(pDX, IDC_RICHTEXT_RECEIVED, m_rtReceived);
	DDX_Control(pDX, IDC_RICHTEXT_SEND, m_rtSend);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChatDlg, CDialog)
	//{{AFX_MSG_MAP(CChatDlg)
	ON_BN_CLICKED(IDOK, OnOk)
	ON_BN_CLICKED(IDB_CLOSE, OnClose)
	ON_BN_CLICKED(IDB_SEND, OnSend)
	ON_BN_CLICKED(IDB_LOADFILE, OnLoadfile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatDlg message handlers

BOOL CChatDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	/// 初始化窗口
	Init();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChatDlg::OnOk() 
{
}

/// 初始化窗口
void CChatDlg::Init()
{
	/// 获取主对话框
	m_pMainDlg = ( CInstantMessagingDlg * )::AfxGetMainWnd();

	/// 设置发送编辑框的最大长度
	m_rtSend.SetMaxLength( MAXCHATLENGTH );
}

void CChatDlg::OnCancel() 
{	
	/// 从主对话框的聊天列表中删除
	m_pMainDlg->OnCloseChatDlg( m_userChat.strIP );

	/// 是否保存聊天记录
	if( ( ( CButton * )GetDlgItem( IDC_SAVEFILE ) )->GetCheck() )
	{
		VARIANT v; 
		memset( &v, 0, sizeof( v ) );
		v.vt	= VT_I4;           
		v.iVal	= 0;
		CString strPath;
		strPath = m_strFilePath.Left( m_strFilePath.ReverseFind( '\\' ) ) + "\\";
		CFileFind fileFind;

		/// 没有HISTORY文件夹
		if( !fileFind.FindFile( strPath ) )
		{
			::CreateDirectory( strPath, NULL );
		} 
		fileFind.Close();
		m_rtReceived.SaveFile( m_strFilePath, v );
	}
	CDialog::OnCancel();

	delete this;
}


/// 设置聊天的对象
void CChatDlg::SetChatUser( const USER userChat )
{
	memcpy( &m_userChat, &userChat, sizeof( USER ) );
	
	/// 设置标题
	CString strTitle;
	strTitle.Format( "聊天 - %s", m_userChat.strName );
	SetWindowText( strTitle );

	/// 设置对话框
	GetDlgItem( IDS_NICKNAME )->SetWindowText( m_userChat.strName );
	GetDlgItem( IDS_IP )->SetWindowText( m_userChat.strIP );

	m_bmpFace.DeleteObject();
	m_bmpFace.LoadBitmap( IDB_BITMAP1 + m_userChat.nFace );
	( ( CStatic * )GetDlgItem( IDS_FACE ) )->SetBitmap( ( HBITMAP )m_bmpFace );

	/// 设置保存聊天记录的文件路径
	char path[ MAX_PATH ];
	::GetModuleFileName( NULL, path, MAX_PATH );
	CString strTmp( path );
	m_strFilePath = strTmp.Left( strTmp.ReverseFind( '\\' ) + 1 );
	m_strFilePath += HISTORYPATH;
	CTime time = CTime::GetCurrentTime();
	CString file;
	file.Format( "%s(%s)%s.rtf", 
		time.Format( "%Y-%m-%d.%H%M%S" ).GetBuffer(time.Format( "%Y-%m-%d.%H%M%S" ).GetLength() ),
		m_userChat.strIP,
		m_userChat.strName );
	m_strFilePath += "\\" + file;
}


void CChatDlg::OnClose() 
{
	OnCancel();
}

void CChatDlg::OnLoadfile() 
{
	CFileDialog fileDlg( TRUE, ".rtf", NULL, NULL, "*.rtf|*.rtf||", NULL );
	if( IDOK == fileDlg.DoModal() )
	{
		CString strPath = fileDlg.GetFileName();
		VARIANT v; 
		memset( &v, 0, sizeof( v ) );
		v.vt	= VT_I4;           
		v.iVal	= 0;
		m_rtReceived.LoadFile( strPath, v );
	}
}

BOOL CChatDlg::PreTranslateMessage(MSG* pMsg) 
{
	/// 按Ctrl+Enter发送消息
	if( pMsg->hwnd == m_rtSend.m_hWnd && pMsg->message == WM_KEYDOWN )
	{
		switch( pMsg->wParam )       
		{                         
        case VK_RETURN:                                 //回车消息 
			if( ::GetKeyState(VK_CONTROL) < 0 )			//判断是否按下了Control
			{
				OnSend();
				return TRUE;
			}
			else
			{
				/// 按回车键实现回车效果
				m_rtSend.SetSelText( "\r\n" );
			}
			break;
		default:
			break;
		}
	}	
	return CDialog::PreTranslateMessage(pMsg);
}


void CChatDlg::OnSend() 
{
	/// 如果发送消息为空
	if( 153 == m_rtSend.GetTextRTF().GetLength() )
	{
		return ;
	}
	CTime time = CTime::GetCurrentTime();
	CString strTime = time.Format( "%H:%M:%S" );

	CString strText;
	strText.Format( "%s %s\r\n  ",m_pMainDlg->GetNickName(), strTime );

	/// 设置接收框
	CString strSend = m_rtSend.GetTextRTF();
	if( strSend.GetLength() > 555000 )
	{
		return;
	}

	m_rtReceived.SetSelStart( m_rtReceived.GetTextRTF().GetLength() );
	m_rtReceived.SetSelText( strText );
	m_rtReceived.SetSelRTF( strSend );
	m_rtReceived.SetSelStart( m_rtReceived.GetTextRTF().GetLength() );
	strText.Format( "\r\n" );
	m_rtReceived.SetSelText( strText );
	m_rtReceived.SetSelStart( m_rtReceived.GetTextRTF().GetLength() );

	/// 设置发送框
	m_rtSend.SetText( "" );
	m_rtSend.SetFocus();

	/// 发送聊天消息
	m_pMainDlg->SendPreChatMessage( m_userChat, strTime, strSend );
}

/// 接收消息
void CChatDlg::ReceiveMessage( LPCSTR szTime, LPCSTR szMessage )
{
	CString strText;
	strText.Format( "%s(%s) %s\r\n  ", 
		m_userChat.strName,
		m_userChat.strIP,
		szTime );

	/// 设置接收框
	m_rtReceived.SetSelStart( m_rtReceived.GetTextRTF().GetLength() );
	m_rtReceived.SetSelText( strText );
	m_rtReceived.SetSelRTF( szMessage );
	m_rtReceived.SetSelStart( m_rtReceived.GetTextRTF().GetLength() );
	strText.Format( "\r\n" );
	m_rtReceived.SetSelText( strText );
	m_rtReceived.SetSelStart( m_rtReceived.GetTextRTF().GetLength() );
}
