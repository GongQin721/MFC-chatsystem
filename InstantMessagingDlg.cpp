// InstantMessagingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "InstantMessaging.h"
#include "InstantMessagingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "ListeningSocket.h"
#include "Debug.h"

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

DWORD WINAPI AddFriendsProc( LPVOID lpParameter );

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInstantMessagingDlg dialog

CInstantMessagingDlg::CInstantMessagingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInstantMessagingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInstantMessagingDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CInstantMessagingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInstantMessagingDlg)
	DDX_Control(pDX, IDC_COMBO_IP, m_comboxIP);
	DDX_Control(pDX, IDC_LIST_FRIENDS, m_listCtrlFriends);
	DDX_Control(pDX, IDC_STATIC_FACE, m_staticFace);
	DDX_Control(pDX, IDC_EDIT_NICKNAME, m_editNickName);
	DDX_Control(pDX, IDC_COMBO_STATE, m_comboxState);
	DDX_Control(pDX, IDC_COMBO_FRIEND, m_comboxFriend);
	DDX_Control(pDX, IDC_BTN_WHITEBOARD, m_btnWhiteBoard);
	DDX_Control(pDX, IDC_BTN_SENDFILES, m_btnSendFiles);
	DDX_Control(pDX, IDC_BTN_CHATROOM, m_btnChatRoom);
	DDX_Control(pDX, IDC_BTN_ADDFRIEND, m_btnAddFriend);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CInstantMessagingDlg, CDialog)
	//{{AFX_MSG_MAP(CInstantMessagingDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, OnOk)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_COMMAND(IDM_EXIT, OnExit)
	ON_COMMAND(IDM_SETTING, OnSetting)
	ON_CBN_SELCHANGE(IDC_COMBO_STATE, OnSelchangeComboState)
	ON_COMMAND(IDM_STATE, OnState)
	ON_BN_CLICKED(IDC_BTN_ADDFRIEND, OnBtnAddfriend)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_CHATROOM, OnBtnChatroom)
	ON_COMMAND(IDM_CHATROOM, OnChatroom)
	ON_BN_CLICKED(IDC_BTN_SENDFILES, OnBtnSendfiles)
	ON_COMMAND(IDM_SENDFILES, OnSendfiles)
	ON_COMMAND(IDM_RECEIVEFILES, OnReceivefiles)
	ON_BN_CLICKED(IDB_ADD_SECTION, OnAddSection)
	ON_BN_CLICKED(IDC_BTN_WHITEBOARD, OnBtnWhiteboard)
	ON_MESSAGE( WM_SHELLNOTIFY, OnShellNotifyProc )
	ON_MESSAGE( WM_HOTKEY, OnHotkey )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInstantMessagingDlg message handlers

BOOL CInstantMessagingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	/// 初始化工作
	Init();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CInstantMessagingDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}

	/// 最小化和单击关闭按钮时的处理
	else if( nID == SC_MINIMIZE )
	{
		this->ShowWindow( SW_HIDE);
	}
	else if( nID == SC_CLOSE )
	{
		OnCancel();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CInstantMessagingDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CInstantMessagingDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/// 按Enter和Esc时不会退出程序
void CInstantMessagingDlg::OnOk() 
{	
}

void CInstantMessagingDlg::OnCancel() 
{
	if( IDOK == MessageBox( "要退出吗？", "退出", MB_OKCANCEL | MB_ICONINFORMATION | MB_DEFBUTTON2 ) )
	{
		/// 对所有用户发送下线信息
		SendOffLineMessage();

		/// 删除用户列表的所有好友
		m_listCtrlFriends.DeleteAllUsers();

		/// 关闭监听套接字
		m_pLisSocket->Close();
		delete [] m_pLisSocket;
		m_pLisSocket = NULL;
		DestroyWindow();
	}
}

void CInstantMessagingDlg::OnDestroy() 
{
	/// 删除在托盘建立的图标
	::Shell_NotifyIcon( NIM_DELETE, &m_nid );	

	CDialog::OnDestroy();
}

void CInstantMessagingDlg::OnHotkey( WPARAM wParam, LPARAM lParam )
{
	if( 0 != m_arrMessageArrive.GetSize() )
	{
		OnChat( m_arrMessageArrive.GetAt( m_nTrayShowIndex ) );
		return;
	}
	if( this->IsWindowVisible() )
	{
		ShowWindow( SW_HIDE );
	}
	else
	{
		ShowWindow( SW_SHOW );
		::SetForegroundWindow( m_hWnd );
	}
}

void CInstantMessagingDlg::OnShellNotifyProc( WPARAM wParam, LPARAM lParam )
{
	if( lParam == WM_LBUTTONDBLCLK )
	{
		/// 如果没有消息，则显示面板
		if( 0 == m_arrMessageArrive.GetSize() )
		{
			::AfxGetApp()->m_pMainWnd->ShowWindow( SW_SHOW );
			::SetForegroundWindow( m_hWnd );
		}
		else
		{
			OnChat( m_arrMessageArrive.GetAt( m_nTrayShowIndex ) );
		}
	}
	else if( lParam == WM_RBUTTONUP )
	{
		
		CMenu menu;
		menu.LoadMenu( IDR_MENU1 );
		CMenu *pSubMenu;
		pSubMenu = menu.GetSubMenu( 0 );
		pSubMenu->ModifyMenu( IDM_STATE, MF_BYCOMMAND, IDM_STATE, STATE_ONLINE == m_wState ? "下线" : "上线" );
		if( STATE_OFFLINE == m_wState )
		{
			pSubMenu->DeleteMenu( IDM_CHATROOM, MF_BYCOMMAND );
		}
		CPoint mouse;
		GetCursorPos( &mouse );
		SetForegroundWindow();
		pSubMenu->TrackPopupMenu( 0, mouse.x, mouse.y, this );
	}
}

void CInstantMessagingDlg::Init()
{
	/// 设置用户列表框类的主对话框
	m_listCtrlFriends.SetMainDlg( this );

	/// 配置文件路径
	char szPath[ MAX_PATH ] ;
	::GetModuleFileName( NULL, szPath, MAX_PATH );
	CString strPath( szPath );
	strPath = strPath.Left( strPath.ReverseFind( '\\' ) ) + "\\" + CONFIG_FILE;

	/// 不在任务显示程序图标
	ModifyStyleEx( WS_EX_APPWINDOW, 0 );

	/// 将窗口放在顶层
	SetWindowPos( &wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );

	/// 注册热键，热键信息保存在CONFIG_FILE文件中
	m_wVirtualKeyCode	= ::GetPrivateProfileInt( "HOTKEY", "wVirtualKeyCode", DEFAULT_VIRTUALKEYCODE, strPath );
	m_wModifiers		= ::GetPrivateProfileInt( "HOTKEY", "wModifiers", DEFAULT_MODIFIERS, strPath );
	WORD wModifiers		= m_wModifiers & HOTKEYF_SHIFT ? MOD_SHIFT : 0;
	wModifiers			+= m_wModifiers & HOTKEYF_CONTROL ? MOD_CONTROL : 0;
	wModifiers			+= m_wModifiers & HOTKEYF_ALT ? MOD_ALT : 0;
	::RegisterHotKey( m_hWnd, IDHOTKEY, wModifiers, m_wVirtualKeyCode );

	m_bAutoAddFriends	= ::GetPrivateProfileInt( "SETTING", "bAUTOADDFRIENDS", DEFAULT_AUTOADDFRIENDS, strPath );

	/// 设置用户的初始化数据
	m_wFace		= ::GetPrivateProfileInt( "USERDATA", "wFace", DEFAULT_FACE, strPath );
	m_wState	= ::GetPrivateProfileInt( "USERDATA", "wState", DEFAULT_STATE, strPath );
	::GetPrivateProfileString( "USERDATA", "strNickName", DEFAULT_NICKNAME,
					m_strNickName.GetBuffer( MAXNICKNAMELENGTH ), MAXNICKNAMELENGTH, strPath );
	m_bmpFace.LoadBitmap( IDB_BITMAP1 + m_wFace );
	m_staticFace.SetBitmap( ( HBITMAP )m_bmpFace ); 
	m_comboxState.SetCurSel( m_wState );
	m_editNickName.SetWindowText( m_strNickName );
	m_strNickName.ReleaseBuffer();
	if( m_strNickName.GetLength() > MAXNICKNAMELENGTH )
	{
		m_strNickName = m_strNickName.Left( MAXNICKNAMELENGTH );
	}

	/// 程序最小化到托盘区
	HICON hIcon				= AfxGetApp()->LoadIcon( m_wState == STATE_ONLINE ? IDR_MAINFRAME : IDI_OFFLINE );
	m_nid.hIcon				= hIcon;
	m_nid.hWnd				= m_hWnd;
	m_nid.cbSize			= sizeof( NOTIFYICONDATA );
	m_nid.uCallbackMessage	= WM_SHELLNOTIFY;
	m_nid.uFlags			= NIF_ICON | NIF_MESSAGE | NIF_TIP;
	m_nid.uID				= IDR_MENU1;
	sprintf( m_nid.szTip, "即时聊天软件" );
	Shell_NotifyIcon( NIM_ADD, &m_nid );

	/// 设置添加联系人的图标
	m_btnAddFriend.setBmp( IDB_ADDFRIEND_NORMAL, 
						   IDB_ADDFRIEND_HOVER, 
						   IDB_ADDFRIEND_DOWN, 
						   IDB_ADDFRIEND_DISABLE );

	/// 设置聊天室的图标
	m_btnChatRoom.setBmp( IDB_CHATROOM_NORMAL, 
						  IDB_CHATROOM_HOVER, 
						  IDB_CHATROOM_DOWN, 
						  IDB_CHATROOM_DISABLE );

	/// 设置发送文件的图标
	m_btnSendFiles.setBmp( IDB_SENDFILES_NORMAL, 
						   IDB_SENDFILES_HOVER, 
						   IDB_SENDFILES_DOWN, 
						   IDB_SENDFILES_DISABLE );


	/// 设置白板的图标
	m_btnWhiteBoard.setBmp( IDB_WHITEBOARD_NORMAL, 
							IDB_WHITEBOARD_HOVER, 
							IDB_WHITEBOARD_DOWN, 
							IDB_WHITEBOARD_DISABLE );

	/// 设置历史联系人记录
	int	nCount = ::GetPrivateProfileInt( "HISTORYFRIENDS", "nCount", 0, strPath );
	CString strIndex;
	CString strHistoryIP;
	for( int nIndex = 1; nIndex <= nCount; nIndex++ )
	{
		strIndex.Format( "%d", nIndex );
		::GetPrivateProfileString( "HISTORYFRIENDS", strIndex, "0.0.0.0",
					strHistoryIP.GetBuffer( 16 ), 16, strPath );
		m_comboxFriend.AddString( strHistoryIP );
		strHistoryIP.ReleaseBuffer();
	}

	/// 初始化用户列表框
	m_listCtrlFriends.InsertColumn( 0, "", LVCFMT_LEFT, -1 );

	/// 初始化添加好友的UDP套接字
	m_pLisSocket = new CListeningSocket( this );
	m_pLisSocket->Create( DEFAULT_PORT, SOCK_DGRAM );

	/// 添加网段用户的socket
	m_pSocket.Create( 0, SOCK_DGRAM );

	/// 得到自己的IP
	char szHostName[128]; 
	if( gethostname( szHostName, 128 ) == 0 ) 
	{
		struct hostent * pHost;	 
		pHost = gethostbyname( szHostName );   
		for( int i = 0; pHost != NULL && pHost->h_addr_list[ i ] != NULL; i++ )   
		{ 
			LPCSTR pszIP = inet_ntoa( *( struct in_addr * )pHost->h_addr_list[ i ] ); 
			m_strlstIP.AddTail( pszIP );
			m_comboxIP.AddString( pszIP );
		}
		m_strlstIP.AddTail( "127.0.0.1" );
		m_strlstIP.AddTail( "127.1" );
	}
	
	m_comboxIP.SetCurSel( 0 );

	/// 将用小数点隔开的IP转化为unsigned long型数字
	POSITION pos, posHead, posTail;
	posHead = m_strlstIP.GetHeadPosition();
	posTail = m_strlstIP.GetTailPosition();
	for( pos = posHead; pos < posTail; )
	{
		CString strNumIP;
		strNumIP.Format( "%u", htonl( inet_addr( m_strlstIP.GetNext( pos ) ) ) );
		m_strlstIP.AddTail( strNumIP ) ;
	}

	/// 设置定时器，用于检测联系人是否保持接连
	if( STATE_ONLINE == m_wState )
	{
		SetTimer( TIMER_CONNECT, DEFAULT_REFRESH_TIME, NULL ); 
	}

	/// 创建imagelist，用于托盘的显示
	m_imageListMA.Create( 16, 16, ILC_COLOR24 | ILC_MASK, 0, 0 );
	m_nTrayShowIndex = 0;

	/// 判断是否注册richtx32.ocx
	HKEY hKey;
	if( RegOpenKeyEx( HKEY_CLASSES_ROOT, "RICHTEXT.RichtextCtrl\\CLSID", 0, KEY_READ, &hKey ) != ERROR_SUCCESS ) 
	{
		HINSTANCE hLib = LoadLibrary( "RICHTX32.OCX" );
		
		/// 控件不存在
		if( !hLib )
		{
			MessageBox( "RICHTX32.OCX控件未找到" );
		}
		else
		{
			//获取注册函数DllRegisterServer地址
			FARPROC lpDllEntryPoint;
			lpDllEntryPoint = GetProcAddress( hLib, "DllRegisterServer" );
			
			/// 注册richtx32.ocx控件
			lpDllEntryPoint();
		}
	}

}

void CInstantMessagingDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	::PostMessage( m_hWnd, WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM( point.x, point.y ) );	
	CDialog::OnLButtonDown(nFlags, point);
}


void CInstantMessagingDlg::OnRButtonUp(UINT nFlags, CPoint point) 
{
	CMenu menu;
	menu.LoadMenu( IDR_MENU1 );
	CMenu *pSubMenu;
	pSubMenu = menu.GetSubMenu( 0 );
	pSubMenu->ModifyMenu( IDM_STATE, MF_BYCOMMAND, IDM_STATE, m_wState == STATE_ONLINE ? "下线" : "上线" );
	if( STATE_OFFLINE == m_wState )
	{
		pSubMenu->DeleteMenu( IDM_CHATROOM, MF_BYCOMMAND );
	}
	ClientToScreen( &point );
	SetForegroundWindow();
	pSubMenu->TrackPopupMenu( 0, point.x, point.y, this );
	CDialog::OnRButtonUp(nFlags, point);
}

void CInstantMessagingDlg::OnExit() 
{
	OnCancel();
}

void CInstantMessagingDlg::OnSetting() 
{
	CDialogSetting dlgSetting;
	dlgSetting.SetMainDlg( this );
	dlgSetting.DoModal();
}

void CInstantMessagingDlg::SetNickName( const CString strNickName )
{
	m_strNickName = strNickName;
	if( m_strNickName.IsEmpty() )
	{
		m_strNickName = DEFAULT_NICKNAME;
	}
	m_editNickName.SetWindowText( m_strNickName );

	/// 配置文件路径
	char szPath[ MAX_PATH ] ;
	::GetModuleFileName( NULL, szPath, MAX_PATH );
	CString strPath( szPath );
	strPath = strPath.Left( strPath.ReverseFind( '\\' ) ) + "\\" + CONFIG_FILE;
	::WritePrivateProfileString( "USERDATA", "strNickName", m_strNickName, strPath );
	UpdateData( FALSE );
}

void CInstantMessagingDlg::SetFace( WORD wFace )
{
	m_wFace = wFace;
	m_bmpFace.DeleteObject();
	m_bmpFace.LoadBitmap( IDB_BITMAP1 + m_wFace );
	m_staticFace.SetBitmap( ( HBITMAP )m_bmpFace );

	/// 配置文件路径
	char szPath[ MAX_PATH ] ;
	::GetModuleFileName( NULL, szPath, MAX_PATH );
	CString strPath( szPath );
	strPath = strPath.Left( strPath.ReverseFind( '\\' ) ) + "\\" + CONFIG_FILE;

	CString strFace;
	strFace.Format( "%d", m_wFace );

	::WritePrivateProfileString( "USERDATA", "wFace", strFace, strPath );
	UpdateData( FALSE );
}

void CInstantMessagingDlg::SetAutoAddFriends( BOOL bAutoAddFriends )
{
	m_bAutoAddFriends = bAutoAddFriends;

	/// 配置文件路径
	char szPath[ MAX_PATH ] ;
	::GetModuleFileName( NULL, szPath, MAX_PATH );
	CString strPath( szPath );
	strPath = strPath.Left( strPath.ReverseFind( '\\' ) ) + "\\" + CONFIG_FILE;

	CString strAutoAddFriendse;
	strAutoAddFriendse.Format( "%d", m_bAutoAddFriends );

	::WritePrivateProfileString( "SETTING", "bAUTOADDFRIENDS", strAutoAddFriendse, strPath );
	UpdateData( FALSE );
}

void CInstantMessagingDlg::SetHotKey( WORD wVirtualKeyCode, WORD wModifiers )
{
	m_wVirtualKeyCode	= wVirtualKeyCode;
	m_wModifiers		= wModifiers;
	::UnregisterHotKey( m_hWnd, IDHOTKEY );
	wModifiers			= m_wModifiers & HOTKEYF_SHIFT ? MOD_SHIFT : 0;
	wModifiers			+= m_wModifiers & HOTKEYF_CONTROL ? MOD_CONTROL : 0;
	wModifiers			+= m_wModifiers & HOTKEYF_ALT ? MOD_ALT : 0;
	::RegisterHotKey( m_hWnd, IDHOTKEY, wModifiers, m_wVirtualKeyCode );

	/// 配置文件路径
	char szPath[ MAX_PATH ] ;
	::GetModuleFileName( NULL, szPath, MAX_PATH );
	CString strPath( szPath );
	strPath = strPath.Left( strPath.ReverseFind( '\\' ) ) + "\\" + CONFIG_FILE;
	
	CString strVirtualKeyCode;
	CString strModifiers;
	strVirtualKeyCode.Format( "%d", m_wVirtualKeyCode );
	strModifiers.Format( "%d", m_wModifiers );

	::WritePrivateProfileString( "HOTKEY", "wVirtualKeyCode", strVirtualKeyCode, strPath );
	::WritePrivateProfileString( "HOTKEY", "wModifiers", strModifiers, strPath );
}

BOOL CInstantMessagingDlg::PreTranslateMessage(MSG* pMsg) 
{
	/// 双击弹出设置对话框
	if( WM_LBUTTONDBLCLK == pMsg->message ) 
	{   
		if( GetDlgItem( IDC_EDIT_NICKNAME )->m_hWnd == pMsg->hwnd 
			|| m_hWnd == pMsg->hwnd ) 
		{ 
			OnSetting();
			return TRUE;
		} 
	}

	/// 输入IP组合框按del键
	else if( ::GetParent( pMsg->hwnd ) == m_comboxFriend.m_hWnd 
		&& pMsg->message == WM_KEYDOWN )
	{
		switch( pMsg->wParam )       
		{                         
        case VK_DELETE:
			if( m_comboxFriend.GetDroppedState() )
			{
				if( CB_ERR != m_comboxFriend.GetCurSel() )
				{
					CString strCurSel;
					m_comboxFriend.GetLBText( m_comboxFriend.GetCurSel(), strCurSel );
					DeleteHistory( m_comboxFriend.GetCurSel(), strCurSel );
				}
			}
			break;
		case VK_RETURN:
			OnBtnAddfriend();
		default:
			break;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

/// 设置状态并保存
void CInstantMessagingDlg::OnSelchangeComboState() 
{
	int nState = m_comboxState.GetCurSel();
	if( nState == m_wState )
	{
		return;
	}
	m_wState = nState;

	/// 配置文件路径
	char szPath[ MAX_PATH ] ;
	::GetModuleFileName( NULL, szPath, MAX_PATH );
	CString strPath( szPath );
	strPath = strPath.Left( strPath.ReverseFind( '\\' ) ) + "\\" + CONFIG_FILE;

	CString strState;
	strState.Format( "%d", m_wState );

	::WritePrivateProfileString( "USERDATA", "wState", strState, strPath );

	/// 如果是下线，则删除所有联系人，并发送下线通知
	if( STATE_OFFLINE == m_wState )
	{
		SendOffLineMessage();
		m_arrFriends.RemoveAll();
		m_listCtrlFriends.DeleteAllItems();
		KillTimer( TIMER_CONNECT );
	}
	else if( STATE_ONLINE == m_wState )
	{
		SetTimer( TIMER_CONNECT, DEFAULT_REFRESH_TIME, NULL ); 
	}
	
	/// 更改托盘区的图标
	SetState();
}

void CInstantMessagingDlg::SetState()
{
	/// 更改程序在托盘区的图标
	HICON hIcon = AfxGetApp()->LoadIcon( m_wState == STATE_ONLINE ? IDR_MAINFRAME : IDI_OFFLINE );
	m_nid.hIcon	= hIcon;
	Shell_NotifyIcon( NIM_MODIFY, &m_nid );
}

void CInstantMessagingDlg::OnState() 
{
	m_wState = m_wState == STATE_ONLINE ? STATE_OFFLINE : STATE_ONLINE;
	m_comboxState.SetCurSel( m_wState );
	UpdateData( FALSE );
	SetState();

	/// 配置文件路径
	char szPath[ MAX_PATH ] ;
	::GetModuleFileName( NULL, szPath, MAX_PATH );
	CString strPath( szPath );
	strPath = strPath.Left( strPath.ReverseFind( '\\' ) ) + "\\" + CONFIG_FILE;

	CString strState;
	strState.Format( "%d", m_wState );

	::WritePrivateProfileString( "USERDATA", "wState", strState, strPath );
}

void CInstantMessagingDlg::OnBtnAddfriend() 
{
	/// 如果是下线状态，不能添加好友
	if( STATE_OFFLINE == m_wState )
	{
		return;
	}

	CString strFriendIP;
	m_comboxFriend.GetWindowText( strFriendIP );

	for( int nIndex = 0; nIndex < m_arrFriends.GetSize(); nIndex++ )
	{
		USER user;
		user = m_arrFriends.GetAt( nIndex );
		if( user.strIP == strFriendIP )
		{
			MessageBox( "您已添加此IP为联系人！", "添加联系人" );
			return;
		}
	}

	/// 判断地址是否合法
	if( inet_addr( strFriendIP ) == INADDR_NONE || strFriendIP.IsEmpty() )
	{
		return;
	}

	/// 判断IP是否是自己IP
	if( m_strlstIP.Find( strFriendIP ) )
	{
		MessageBox( "不能添加自己为联系人！", "添加联系人" );
		return;
	}

	/// 不能为广播地址
	if( strFriendIP.Right( 3 ) == "255" )
	{
		return;
	}

	/// 定义数据包
	DATAPACKET dataPacket;
	dataPacket.command = REQUEST_ADD;
	
	/// 设置请求的用户结构
	USER user;
	user.bHasCamera	= m_bCamera;
	user.nFace		= m_wFace;
	memcpy( user.strName, m_strNickName.GetBuffer( MAXNICKNAMELENGTH + 1 ), MAXNICKNAMELENGTH + 1 );
	m_strNickName.ReleaseBuffer();
	
	/// 分配空间
	UINT uDataLength = sizeof( DATAPACKET ) + sizeof( USER );
	BYTE *pSendData = new BYTE[ uDataLength ];
	memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
	memcpy( pSendData + sizeof( DATAPACKET ), &user, sizeof( USER ) );

	/// 发送请求
	m_pLisSocket->SendTo( pSendData, uDataLength, DEFAULT_PORT, strFriendIP );

	delete pSendData;
}

void CInstantMessagingDlg::OnListeningReceive()
{
	/// 接收数据
	CString strFriendIP;
	UINT uPort;
	char szReceive[ MAXDATAPACKETLENGTH ];
	m_pLisSocket->ReceiveFrom( szReceive, MAXDATAPACKETLENGTH, strFriendIP, uPort );

	/// 如果是下线状态，不作任何处理
	if( STATE_OFFLINE == m_wState )
	{
		return;
	}

	/// 装配数据包
	DATAPACKET dataPacket;
	memcpy( &dataPacket, szReceive, sizeof( DATAPACKET ) );
	USER user;
	CString strData;

	/// 根据命令进行不同的处理
	switch( dataPacket.command )
	{
	case REQUEST_ADD:												/// 请求加为联系人
		memcpy( &user, szReceive + sizeof( DATAPACKET ), sizeof( USER ) );
		memcpy( user.strIP, strFriendIP.GetBuffer( 16 ), 16 );
		strFriendIP.ReleaseBuffer();
		AddRequest( user );
		break;
	case REQUEST_DENY:												/// 拒绝加为联系人
		MessageBox( "您请求 " + strFriendIP + " 的好友拒绝了您的请求！", "请求结果", 
			MB_OK | MB_ICONINFORMATION);
		break;
	case REQUEST_ALLOW:												/// 允许加为联系人
		memcpy( &user, szReceive + sizeof( DATAPACKET ), sizeof( USER ) );
		memcpy( user.strIP, strFriendIP.GetBuffer( 16 ), 16 );
		strFriendIP.ReleaseBuffer();
		AddFriend( user );
		break;
	case OFFLINE:													/// 下线
		memcpy( &user, szReceive + sizeof( DATAPACKET ), sizeof( USER ) );
		memcpy( user.strIP, strFriendIP.GetBuffer( 16 ), 16 );
		strFriendIP.ReleaseBuffer();
		DeleteFriend( user );
		break;
	case REQUEST_KEEPCONNECT:										/// 请求保持接连
		KeepConnect( strFriendIP );
		break;
	case RESPONSE_KEEPCONNECT:										/// 回应保持接连
		m_strlstKeepConnent.RemoveAt( m_strlstKeepConnent.Find( strFriendIP ) );
		break;
	case CHATROOM_ADDREQUEST:										/// 加入聊天室的请求
		memcpy( &user, szReceive + sizeof( DATAPACKET ), sizeof( USER ) );
		memcpy( user.strIP, strFriendIP.GetBuffer( 16 ), 16 );
		strFriendIP.ReleaseBuffer();
		OnAddToChatRoomRequest( user );
		break;
	case CHAT_PREPARE_MESSAGE:										/// 聊天发送的消息信息
		PrepareChatMessage( szReceive, strFriendIP );
		break;
	case CHAT_MESSAGE:												/// 聊天发送的消息
		ReceiveChatMessage( szReceive, strFriendIP );
		break;
	case CHAT_RECEIVE:												/// 开始接收聊天消息的命令
		SendChatMessage( szReceive, strFriendIP );
		break;
	case SENDFILES_NOTIFY:											/// 在文件传过来的通知
		SendFilesResponse( szReceive, strFriendIP );
		break;
	case SENDFILES_DENY:											/// 拒绝接收文件
		OnBtnSendfiles();
		memcpy( strData.GetBuffer( dataPacket.dwLength ), 
			szReceive + sizeof( DATAPACKET ),
			dataPacket.dwLength );
		strData.ReleaseBuffer( -1 );
		m_dlgSendFilesServer.DenyReceiveFile( strData, strFriendIP );
		break;

	case WHITEBOARD_ADDREQUEST:										/// 白板添加请求
		memcpy( &user, szReceive + sizeof( DATAPACKET ), sizeof( USER ) );
		memcpy( user.strIP, strFriendIP.GetBuffer( 16 ), 16 );
		strFriendIP.ReleaseBuffer();
		OnAddToWhiteBoardRequest( user );
		break;

	default:
		break;
	}
}

void CInstantMessagingDlg::AddRequest( const USER user )
{
	/// 判断是否自己加自己
	CString strUserIP( user.strIP );
	if( -1 != strUserIP.Find( "127.0.0" ) )
	{
		return;
	}

	/// 判断是否已经加为联系人
	for( int nIndex = 0; nIndex < m_arrFriends.GetSize(); nIndex++ )
	{
		USER userTemp = m_arrFriends.GetAt( nIndex );
		if( 0 == strcmp( userTemp.strIP, user.strIP ) )
		{
			return;
		}
	}

	/// 判断之前是有相同IP的请求
	if( m_strlstRequest.Find( user.strIP ) )
	{
		return;
	}
	m_strlstRequest.AddTail( user.strIP );

	/// 提示是否加为好友
	CString strPrompt;
	strPrompt.Format( "来自 %s 的好友 %s 请求加您为好友\n您同意吗？", user.strIP, user.strName );

	/// 拒绝请求
	if( !m_bAutoAddFriends && IDCANCEL == MessageBox( strPrompt, "请求", MB_OKCANCEL | MB_ICONINFORMATION | MB_DEFBUTTON1 ) )
	{
		DATAPACKET dataPacket;
		dataPacket.command = REQUEST_DENY;
		
		/// 分配空间
		UINT uDataLength = sizeof( DATAPACKET );
		BYTE *pSendData = new BYTE[ uDataLength ];
		memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
		
		/// 发送拒绝请求
		m_pLisSocket->SendTo( pSendData, uDataLength, DEFAULT_PORT, user.strIP );

		delete pSendData;

		/// 从请求列表中删除请求IP
		m_strlstRequest.RemoveAt( m_strlstRequest.Find( user.strIP ) );
		return;
	}
	
	/// 允许加为好友
	DATAPACKET dataPacket;
	dataPacket.command	= REQUEST_ALLOW;
	dataPacket.dwLength = sizeof( USER );
	
	USER mySelf;
	mySelf.bHasCamera	= m_bCamera;
	mySelf.nFace		= m_wFace;
	memcpy( mySelf.strName, m_strNickName.GetBuffer( MAXNICKNAMELENGTH + 1 ), MAXNICKNAMELENGTH + 1 );
	m_strNickName.ReleaseBuffer();
	
	/// 分配空间
	UINT uDataLength = sizeof( DATAPACKET ) + sizeof( USER );
	BYTE *pSendData = new BYTE[ uDataLength ];
	memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
	memcpy( pSendData + sizeof( DATAPACKET ), &mySelf, sizeof( USER ) );
	
	/// 发送拒绝请求
	m_pLisSocket->SendTo( pSendData, uDataLength, DEFAULT_PORT, user.strIP );
	
	delete pSendData;

	/// 从请求列表中删除请求IP
	m_strlstRequest.RemoveAt( m_strlstRequest.Find( user.strIP ) );
	AddFriend( user );
}

void CInstantMessagingDlg::AddFriend( const USER user )
{
	m_listCtrlFriends.AddUser( user );
	m_arrFriends.Add( user );

	/// 配置文件路径
	char szPath[ MAX_PATH ] ;
	::GetModuleFileName( NULL, szPath, MAX_PATH );
	CString strPath( szPath );
	strPath = strPath.Left( strPath.ReverseFind( '\\' ) ) + "\\" + CONFIG_FILE;

	/// 获取历史联系人记录
	BOOL bExistFriendHistory = FALSE;

	int	nCount		= ::GetPrivateProfileInt( "HISTORYFRIENDS", "nCount", 0, strPath );
	int	nMax		= ::GetPrivateProfileInt( "HISTORYFRIENDS", "nMax", 0, strPath );
	int	nCurrent	= ::GetPrivateProfileInt( "HISTORYFRIENDS", "nCurrent", 1, strPath );
	CString strIndex;
	CString strHistoryIP;

	/// 判断是否存在记录
	for( int nIndex = 1; nIndex <= nCount; nIndex++ )
	{
		strIndex.Format( "%d", nIndex );
		::GetPrivateProfileString( "HISTORYFRIENDS", strIndex, "0.0.0.0",
					strHistoryIP.GetBuffer( 16 ), 16, strPath );
		if( !strHistoryIP.Compare( user.strIP ) )
		{
			bExistFriendHistory = TRUE;
			break;
		}
		strHistoryIP.ReleaseBuffer();
	}
	
	/// 历史记录中没有此IP
	if( !bExistFriendHistory )
	{
		/// 当前总记录数小于最大记录数
		if( nCount < nMax )
		{
			strIndex.Format( "%d", ++nCount );
			::WritePrivateProfileString( "HISTORYFRIENDS", strIndex, user.strIP, strPath );
			::WritePrivateProfileString( "HISTORYFRIENDS", "nCount", strIndex, strPath );
		}

		/// 当前总记录数等于最大记录数
		else
		{
			strIndex.Format( "%d", ++nCurrent );
			::WritePrivateProfileString( "HISTORYFRIENDS", strIndex, user.strIP, strPath );
			::WritePrivateProfileString( "HISTORYFRIENDS", "nCurrent", strIndex, strPath );
		}

		/// 重新设置历史记录组合框
		int	nCount = ::GetPrivateProfileInt( "HISTORYFRIENDS", "nCount", 0, strPath );
		CString strIndex;
		CString strHistoryIP;
		m_comboxFriend.ResetContent();
		for( int nIndex = 1; nIndex <= nCount; nIndex++ )
		{
			strIndex.Format( "%d", nIndex );
			::GetPrivateProfileString( "HISTORYFRIENDS", strIndex, "0.0.0.0",
				strHistoryIP.GetBuffer( 16 ), 16, strPath );
			m_comboxFriend.AddString( strHistoryIP );
			strHistoryIP.ReleaseBuffer();
		}
	}
}

void CInstantMessagingDlg::SendOffLineMessage()
{
	DATAPACKET dataPacket;
	dataPacket.command = OFFLINE;
	
	/// 分配空间
	UINT uDataLength = sizeof( DATAPACKET );
	BYTE *pSendData = new BYTE[ uDataLength ];
	memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
	
	
	/// 全部发送下线通知
	for( int nIndex = 0; nIndex < m_arrFriends.GetSize(); nIndex++ )
	{
		USER user = m_arrFriends.GetAt( nIndex );
		m_pLisSocket->SendTo( pSendData, uDataLength, DEFAULT_PORT, user.strIP );
	}	
	
	delete pSendData;
}

void CInstantMessagingDlg::DeleteFriend( const USER user )
{
	for( int nIndex = 0; nIndex < m_arrFriends.GetSize(); nIndex++ )
	{
		USER userDel = m_arrFriends.GetAt( nIndex );
		if( 0 == strcmp( userDel.strIP, user.strIP ) )
		{
			m_listCtrlFriends.DeleteUser( nIndex );
			m_arrFriends.RemoveAt( nIndex );
			break;
		}
	}
}

void CInstantMessagingDlg::OnTimer(UINT nIDEvent) 
{
	/// 保持接连
	if( TIMER_CONNECT == nIDEvent )	
	{
		/// 删除没有回应的联系人
		for( int nIndex = 0; nIndex < m_arrFriends.GetSize(); nIndex++ )
		{
			USER userDel = m_arrFriends.GetAt( nIndex );
			if( m_strlstKeepConnent.Find( userDel.strIP ) )
			{
				m_listCtrlFriends.DeleteUser( nIndex );
				m_arrFriends.RemoveAt( nIndex );
				nIndex--;
			}
		}
		m_strlstKeepConnent.RemoveAll();
		
		/// 分别发送保持连接的消息，将发送过的IP加入到m_strlstKeepConnent
		for( nIndex = 0; nIndex < m_arrFriends.GetSize(); nIndex++ )
		{
			USER user = m_arrFriends.GetAt( nIndex );
			
			DATAPACKET dataPacket;
			dataPacket.command = REQUEST_KEEPCONNECT;
			
			/// 分配空间
			UINT uDataLength = sizeof( DATAPACKET );
			BYTE *pSendData = new BYTE[ uDataLength ];
			memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
			
			m_pLisSocket->SendTo( pSendData, uDataLength, DEFAULT_PORT, user.strIP );
			
			delete pSendData;
			
			m_strlstKeepConnent.AddTail( user.strIP );
		}
	}

	/// 托盘显示
	else if( TIMER_TRAYSHOW == nIDEvent )
	{
		/// 显示m_nTrayShowIndex图像
		static BOOL bShow = TRUE;
		if( m_nTrayShowIndex >= m_arrMessageArrive.GetSize() )
		{
			m_nTrayShowIndex = 0;
		}

		CBitmap bitmap32;
		CBitmap bitmap16;
		HBITMAP hBitmap;
		bitmap32.LoadBitmap( IDB_BITMAP1 + m_arrFriends.GetAt( m_arrMessageArrive.GetAt( m_nTrayShowIndex ) ).nFace );
		hBitmap = ( HBITMAP )::CopyImage( ( HBITMAP )bitmap32, IMAGE_BITMAP, 16, 16, LR_COPYDELETEORG );
		bitmap16.Attach( hBitmap );
		m_imageListMA.Add( &bitmap16, FACEBGCOLOR );
		bitmap16.DeleteObject();
		bitmap32.DeleteObject();
		::DeleteObject( hBitmap );

		/// 更改程序在托盘区的图标
		HICON hIcon = m_imageListMA.ExtractIcon( 0 );
		m_imageListMA.Remove( 0 );
		if( bShow )
		{
			m_nid.hIcon	= hIcon;
			m_nTrayShowIndex++;
			if( m_nTrayShowIndex >= m_arrMessageArrive.GetSize() )
			{
				m_nTrayShowIndex = 0;
			}
		}
		else
		{
			m_nid.hIcon = NULL;
		}
		bShow = !bShow;
		Shell_NotifyIcon( NIM_MODIFY, &m_nid );
	}

	CDialog::OnTimer(nIDEvent);
}

void CInstantMessagingDlg::KeepConnect( CString strIP )
{
	DATAPACKET dataPacket;
	dataPacket.command = RESPONSE_KEEPCONNECT;
	
	/// 分配空间
	UINT uDataLength = sizeof( DATAPACKET );
	BYTE *pSendData = new BYTE[ uDataLength ];
	memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
	
	m_pLisSocket->SendTo( pSendData, uDataLength, DEFAULT_PORT, strIP );
	
	delete pSendData;
}

void CInstantMessagingDlg::DeleteFriend( int nIndex )
{
	USER user = m_arrFriends.GetAt( nIndex );

	CString strPrompt;
	strPrompt.Format( "要删除 %s 的好友 %s 吗？", user.strIP, user.strName );

	/// 提示是否删除
	if( IDCANCEL == MessageBox( strPrompt, "删除好友", MB_OKCANCEL | MB_ICONINFORMATION | MB_DEFBUTTON2 ) )
	{
		return;
	}

	DATAPACKET dataPacket;
	dataPacket.command = OFFLINE;
	
	/// 分配空间
	UINT uDataLength = sizeof( DATAPACKET );
	BYTE *pSendData = new BYTE[ uDataLength ];
	memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
	
	m_pLisSocket->SendTo( pSendData, uDataLength, DEFAULT_PORT, user.strIP );

	delete pSendData;
	
	m_listCtrlFriends.DeleteUser( nIndex );
	m_arrFriends.RemoveAt( nIndex );
}

void CInstantMessagingDlg::SendFriendMessage( const USER user, CONTROLCOMMAND command )
{
	DATAPACKET dataPacket;
	dataPacket.command = command;
	
	/// 分配空间
	UINT uDataLength = sizeof( DATAPACKET ) + sizeof( USER );
	BYTE *pSendData = new BYTE[ uDataLength ];
	memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
	memcpy( pSendData + sizeof( DATAPACKET ), &user, sizeof( USER ) );
	
	/// 发送允许请求
	m_pLisSocket->SendTo( pSendData, uDataLength, DEFAULT_PORT, user.strIP );
	
	delete pSendData;
}

void CInstantMessagingDlg::OnBtnChatroom() 
{
	if( !m_dlgCRServer )
	{
		/// GetDesktopWindow()为主对话框
		m_dlgCRServer.Create( IDD_CHATROOM_SERVER, GetDesktopWindow() );
		m_dlgCRServer.ShowWindow( SW_SHOW );
		return;
	}
	else
	{
		::SetForegroundWindow( m_dlgCRServer.m_hWnd );
		m_dlgCRServer.FlashWindow( TRUE );
	}
}

void CInstantMessagingDlg::OnChatroom() 
{
	OnBtnChatroom();
}

void CInstantMessagingDlg::OnAddToChatRoomRequest( const USER userServer )
{
	if( 0 != m_arrCRClient.GetSize() )
	{
		return;
	}
	/// 判断之前是有相同IP的请求
	if( m_strlstChatRoomRequest.Find( userServer.strIP ) )
	{
		return;
	}
	m_strlstChatRoomRequest.AddTail( userServer.strIP );

	/// 提示是否加入聊天室
	CString strPrompt;
	strPrompt.Format( "来自 %s 的好友 %s 请求您加入聊天室\n您同意吗？", userServer.strIP, userServer.strName );

	/// 拒绝请求
	if( IDCANCEL == MessageBox( strPrompt, "聊天室", MB_OKCANCEL | MB_ICONINFORMATION | MB_DEFBUTTON1 ) )
	{
		/// 向服务器发送拒绝加入聊天室的请求
		SendUserCommandToIP( CHATROOM_ADDREQUEST_DENY, userServer.strIP, CHATROOM_SERVER_PORT, NULL );
		
		/// 从请求列表中删除请求IP
		m_strlstChatRoomRequest.RemoveAt( m_strlstChatRoomRequest.Find( userServer.strIP ) );
		return;
	}

	/// 创建聊天室客户端并保存进列表
	CChatRoomClientDlg *pCRClientDlg = new CChatRoomClientDlg();
	pCRClientDlg->Create( IDD_CHATROOM_CLIENT, GetDesktopWindow() );
	pCRClientDlg->AcceptAddRequest( userServer );
	pCRClientDlg->ShowWindow( SW_SHOW );
	m_arrCRClient.Add( pCRClientDlg );

	/// 从请求列表中删除请求IP
	m_strlstChatRoomRequest.RemoveAt( m_strlstChatRoomRequest.Find( userServer.strIP ) );
}


void CInstantMessagingDlg::OnAddToWhiteBoardRequest( const USER userServer )
{
	/// 如果已经共享白板，则不能再共享其他人的白板
	if( m_dlgWhiteBoardClient )
	{
		return;
	}

	/// 判断之前是有相同IP的请求
	if( m_strlstWhiteBoardRequest.Find( userServer.strIP ) )
	{
		return;
	}
	m_strlstWhiteBoardRequest.AddTail( userServer.strIP );

	/// 提示是否加入白板
	CString strPrompt;
	strPrompt.Format( "来自 %s 的好友 %s 请求您加入白板\n您同意吗？", userServer.strIP, userServer.strName );

	/// 拒绝请求
	if( IDCANCEL == MessageBox( strPrompt, "白板", MB_OKCANCEL | MB_ICONINFORMATION | MB_DEFBUTTON1 ) )
	{
		/// 向服务器发送拒绝加入白板的请求
		SendUserCommandToIP( WHITEBOARD_ADDREQUEST_DENY, userServer.strIP, WHITEBOARD_SERVER_PORT, NULL );
		
		/// 从请求列表中删除请求IP
		m_strlstWhiteBoardRequest.RemoveAt( m_strlstWhiteBoardRequest.Find( userServer.strIP ) );
		return;
	}

	/// 创建白板客户端并保存进列表
	m_dlgWhiteBoardClient.Create( IDD_WHITEBOARD_CLIENT, GetDesktopWindow() );
	m_dlgWhiteBoardClient.AcceptAddRequest( userServer );
	m_dlgWhiteBoardClient.ShowWindow( SW_SHOW );

	/// 从请求列表中删除请求IP
	m_strlstWhiteBoardRequest.RemoveAt( m_strlstWhiteBoardRequest.Find( userServer.strIP ) );
}


/// 向指定IP、PORT发送指定数据
void CInstantMessagingDlg::SendUserCommandToIP( CONTROLCOMMAND command, LPCSTR szIP, UINT uPort, const USER *pUser )
{
	DATAPACKET dataPacket;
	dataPacket.command	= command;
	
	/// 分配空间
	UINT uDataLength = sizeof( DATAPACKET );
	if( pUser )
	{
		uDataLength += sizeof( USER );
	}
	BYTE *pSendData = new BYTE[ uDataLength ];
	memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
	if( pUser )
	{
		memcpy( pSendData + sizeof( DATAPACKET ), pUser, sizeof( USER ) );
	}
	
	/// 发送数据
	m_pLisSocket->SendTo( pSendData, uDataLength, uPort, szIP );

	delete pSendData;
}

/// 聊天室客户端关闭
void CInstantMessagingDlg::DelCRClientFromList( LPCSTR szIP )
{
	for( int nIndex = 0; nIndex < m_arrCRClient.GetSize(); nIndex++ )
	{
		CChatRoomClientDlg *pCRClientDlg = ( CChatRoomClientDlg * )m_arrCRClient.GetAt( nIndex );

		if( 0 == strcmp( pCRClientDlg->GetServerIP(), szIP ) )
		{
			/// 从列表中移除
			m_arrCRClient.RemoveAt( nIndex );
			break;
		}
	}
}

/// 聊天消息到达时接收函数
void CInstantMessagingDlg::OnChat( UINT nIndex )
{
	int nUserIndex = nIndex;
	USER userChat = m_arrFriends.GetAt( nIndex );
	
	/// 查找是否已经打开与userChat的聊天窗口
	for( nIndex = 0; nIndex < m_arrChatDlg.GetSize(); nIndex++ )
	{
		/// 已经有打开的窗口
		if( 0 == strcmp( userChat.strIP, m_arrChatDlg.GetAt( nIndex )->GetChatIP() ) )
		{
			::SetForegroundWindow( m_arrChatDlg.GetAt( nIndex )->m_hWnd );
			m_arrChatDlg.GetAt( nIndex )->FlashWindow( TRUE );
			return;
		}
	}
	
	/// 创建新窗口
	CChatDlg *pChatDlg = new CChatDlg( this );

	/// GetDesktopWindow()为主对话框
	pChatDlg->Create( IDD_CHAT, GetDesktopWindow() );
	pChatDlg->SetChatUser( userChat );
	pChatDlg->ShowWindow( SW_SHOW );
	m_arrChatDlg.Add( pChatDlg );

	/// 有消息在列表中
	CMapStringToString *pMapTimeAndMessage;
	if( m_mapIPToChat.Lookup( userChat.strIP, ( CObject*& )pMapTimeAndMessage ) )
	{
		POSITION pos = pMapTimeAndMessage->GetStartPosition();
		while( 0 != pos )
		{
			CString strTime;
			CString strMessage;
			pMapTimeAndMessage->GetNextAssoc( pos, strTime, strMessage );
			pChatDlg->ReceiveMessage( strTime, strMessage );
		}
		
		/// 从列表中删除接收到的消息
		pMapTimeAndMessage->RemoveAll();
		delete pMapTimeAndMessage;
		m_mapIPToChat.RemoveKey( userChat.strIP );
		
		/// 从托盘删除动态显示的响应图标
		for( nIndex = 0; nIndex<m_arrMessageArrive.GetSize(); nIndex++ )
		{
			if( m_arrMessageArrive.GetAt( nIndex ) == nUserIndex )
			{
				m_arrMessageArrive.RemoveAt( nIndex );

				/// 如果托盘中没有其他图标，则还原图标并关闭timer
				if( 0 == m_arrMessageArrive.GetSize() )
				{
					KillTimer( TIMER_TRAYSHOW );
					SetState();
				}
				break;
			}
		}
	}
}	

void CInstantMessagingDlg::OnCloseChatDlg( LPCSTR szIP )
{
	/// 查找已经打开与szIP的聊天窗口
	for( int nIndex = 0; nIndex < m_arrChatDlg.GetSize(); nIndex++ )
	{
		if( 0 == strcmp( szIP, m_arrChatDlg.GetAt( nIndex )->GetChatIP() ) )
		{
			m_arrChatDlg.RemoveAt( nIndex );
			return;
		}
	}
}


/// 从历史记录中删除指定记录
void CInstantMessagingDlg::DeleteHistory( int nIndex, const CString strHistory )
{
	/// 重新设置历史记录组合框
	m_comboxFriend.DeleteString( nIndex );

	/// 配置文件路径
	char szPath[ MAX_PATH ] ;
	::GetModuleFileName( NULL, szPath, MAX_PATH );
	CString strPath( szPath );
	strPath = strPath.Left( strPath.ReverseFind( '\\' ) ) + "\\" + CONFIG_FILE;

	int	nCount		= ::GetPrivateProfileInt( "HISTORYFRIENDS", "nCount", 0, strPath );
	int	nMax		= ::GetPrivateProfileInt( "HISTORYFRIENDS", "nMax", 0, strPath );
	int	nCurrent	= ::GetPrivateProfileInt( "HISTORYFRIENDS", "nCurrent", 1, strPath );

	CString strIndex;
	CString strHistoryIP;
	for( nIndex = 1; nIndex <= nCount; nIndex++ )
	{
		strIndex.Format( "%d", nIndex );
		::GetPrivateProfileString( "HISTORYFRIENDS", strIndex, "0.0.0.0",
					strHistoryIP.GetBuffer( 16 ), 16, strPath );
		strHistoryIP.ReleaseBuffer();
		if( strHistory == strHistoryIP )
		{
			if( nCurrent >= nIndex )
			{
				if( 1 == nCurrent )
				{
					nCurrent = 2;
				}
				strIndex.Format( "%d", nCurrent - 1 );
				::WritePrivateProfileString( "HISTORYFRIENDS", "nCurrent", strIndex, strPath );
			}
			for( int nIndex1 = nIndex + 1; nIndex1 <= nCount; nIndex1++ )
			{
				strIndex.Format( "%d", nIndex1 );
				::GetPrivateProfileString( "HISTORYFRIENDS", strIndex, "0.0.0.0",
					strHistoryIP.GetBuffer( 16 ), 16, strPath );
				strHistoryIP.ReleaseBuffer();
				strIndex.Format( "%d", nIndex1 - 1 );
				::WritePrivateProfileString( "HISTORYFRIENDS", strIndex, strHistoryIP, strPath );
			}
			strIndex.Format( "%d", nIndex1 - 1 );
			::WritePrivateProfileString( "HISTORYFRIENDS", strIndex, NULL, strPath );
			break;
		}
	}
	strIndex.Format( "%d", nCount - 1 );
	::WritePrivateProfileString( "HISTORYFRIENDS", "nCount", strIndex, strPath );
}

/// 发送聊天消息
void CInstantMessagingDlg::SendPreChatMessage( const USER userChat, CString strTime, CString strSend )
{
	DATAPACKET dataPacket;
	CHATPACKETINFO chatPacketInfo;

	/// 发送消息的长度
	DWORD dwSendLength = strSend.GetLength();

	/// 发送消息信息
	dataPacket.command	= CHAT_PREPARE_MESSAGE;
	dataPacket.dwLength	= dwSendLength;

	UINT uDataLength = sizeof( DATAPACKET ) + 10;
	BYTE *pSendData = new BYTE[ uDataLength ];
	memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
	memcpy( pSendData + sizeof( DATAPACKET ), strTime.GetBuffer( 10 ), 10 );
	strTime.ReleaseBuffer( -1 );

	/// 发送数据
	m_pLisSocket->SendTo( pSendData, uDataLength, DEFAULT_PORT, userChat.strIP );

	delete pSendData;

	/// 之前有未发送完的消息
	CString strBeforeSend;
	if( m_mapSendChatMessage.Lookup( userChat.strIP, strBeforeSend ) )
	{
		
	}

	/// 将要发送的消息保存到m_mapSendChatMessage
	m_mapSendChatMessage.SetAt( userChat.strIP, strSend );
}

/// 为接收聊天消息作准备
void CInstantMessagingDlg::PrepareChatMessage( LPCSTR szReceive, LPCSTR szIP )
{
	LPVOID pData = NULL;

	/// 上一次的消息还没接收完，新消息又到达，则上一次的消息作废
	if( m_mapIPToData.Lookup( szIP, pData ) )
	{
		delete pData;
		m_mapIPToData.RemoveKey( szIP );
		m_mapIPToTime.RemoveKey( szIP );
	}

	/// 重新生成map接收消息
	DATAPACKET dataPacket;
	memcpy( &dataPacket, szReceive, sizeof( DATAPACKET ) );

	char szTime[ 10 ];
	memcpy( szTime, szReceive + sizeof( DATAPACKET ), 10 );

	pData = new char[ dataPacket.dwLength ];

	m_mapIPToData.SetAt( szIP, pData );
	m_mapIPToTime.SetAt( szIP, szTime );

	/// 发送开始接收文件的命令
	CHATPACKETINFO chatPacketInfo;
	chatPacketInfo.nCurrent = 0;
	dataPacket.command = CHAT_RECEIVE;

	UINT uDataLength = sizeof( DATAPACKET ) + sizeof( CHATPACKETINFO );
	BYTE *pSendData = new BYTE[ uDataLength ];
	memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
	memcpy( pSendData + sizeof( DATAPACKET ), &chatPacketInfo, sizeof( CHATPACKETINFO ) );

	/// 发送数据
	m_pLisSocket->SendTo( pSendData, uDataLength, DEFAULT_PORT, szIP );

	delete pSendData;
}

/// 接收聊天消息
void CInstantMessagingDlg::ReceiveChatMessage( LPCSTR szReceive, LPCSTR szIP )
{
	CHATPACKETINFO chatPacketInfo;
	memcpy( &chatPacketInfo, szReceive + sizeof( DATAPACKET ), sizeof( CHATPACKETINFO ) );

	LPVOID pData = NULL;

	/// 查找到存放数据的地址
	if( m_mapIPToData.Lookup( szIP, pData ) )
	{
		memcpy( ( BYTE *)pData + chatPacketInfo.nCurrent * MAXCHATLENGTH,
			szReceive + sizeof( DATAPACKET ) + sizeof( CHATPACKETINFO ),
			chatPacketInfo.nLength );


		/// 数据接收完毕
		if( chatPacketInfo.nCurrent + 1 == chatPacketInfo.nTotal )
		{
			/// 播放声音
			::PlaySound( "msg.wav", NULL, SND_FILENAME | SND_ASYNC);

			/// 查找窗口是否已经打开
			for( int nIndex = 0; nIndex < m_arrChatDlg.GetSize(); nIndex++ )
			{
				/// 窗口已经打开，把消息直接发送到窗口接收编辑框中
				if( 0 == strcmp( szIP, m_arrChatDlg.GetAt( nIndex )->GetChatIP() ) )
				{
					CString strTime;
					m_mapIPToTime.Lookup( szIP, strTime );
					m_arrChatDlg.GetAt( nIndex )->ReceiveMessage( strTime, ( char * )pData );
					if( ::GetForegroundWindow() != m_arrChatDlg.GetAt( nIndex )->m_hWnd )
					{
						m_arrChatDlg.GetAt( nIndex )->FlashWindow( TRUE );
					}				

					/// 删除记录信息
					delete pData;
					m_mapIPToData.RemoveKey( szIP );
					m_mapIPToTime.RemoveKey( szIP );
					return;
				}
			}
			
			/// 窗口没有打开，把消息加到到m_mapIPToChat
			CString strTime;
			m_mapIPToTime.Lookup( szIP, strTime );
			
			CMapStringToString *pMapTimeAndMessage;
			if( !m_mapIPToChat.Lookup( szIP, ( CObject*& )pMapTimeAndMessage ) )
			{
				pMapTimeAndMessage = new CMapStringToString();
			}
			pMapTimeAndMessage->SetAt( strTime, ( char * )pData );
			m_mapIPToChat.SetAt( szIP, pMapTimeAndMessage );

			/// 托盘区的头像显示
			AddTrayIcon( szIP );

			/// 删除记录信息
			delete pData;
			m_mapIPToData.RemoveKey( szIP );
			m_mapIPToTime.RemoveKey( szIP );
			return;
		}

		/// 数据没接收完，继续发送接收消息的命令
		else
		{
			chatPacketInfo.nCurrent = chatPacketInfo.nCurrent + 1;

			DATAPACKET dataPacket;
			dataPacket.command = CHAT_RECEIVE;
			
			UINT uDataLength = sizeof( DATAPACKET ) + sizeof( CHATPACKETINFO );
			BYTE *pSendData = new BYTE[ uDataLength ];
			memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
			memcpy( pSendData + sizeof( DATAPACKET ), &chatPacketInfo, sizeof( CHATPACKETINFO ) );
			
			/// 发送数据
			m_pLisSocket->SendTo( pSendData, uDataLength, DEFAULT_PORT, szIP );
			
			delete pSendData;
		}
	}
}

/// 开始发送数据
void CInstantMessagingDlg::SendChatMessage( LPCSTR szReceive, LPCSTR szIP )
{
	CHATPACKETINFO chatPacketInfo;
	memcpy( &chatPacketInfo, szReceive + sizeof( DATAPACKET ), sizeof( CHATPACKETINFO ) );

	CString strSend;

	/// 查找与szIP对应的消息map
	if( m_mapSendChatMessage.Lookup( szIP, strSend ) )
	{
		/// 发送消息的长度
		DWORD dwSendLength = strSend.GetLength();
		
		/// 包的总数
		int nTotal;
		if( 0 == dwSendLength % MAXCHATLENGTH )
		{
			nTotal = dwSendLength / MAXCHATLENGTH;
		}
		else
		{	
			nTotal = dwSendLength / MAXCHATLENGTH + 1;
		}
		
		/// 最后一个包的长度
		int nLastLength = dwSendLength - MAXCHATLENGTH * ( nTotal - 1 );

		DATAPACKET dataPacket;
		dataPacket.command = CHAT_MESSAGE;

		chatPacketInfo.nLength = MAXCHATLENGTH;
		if( chatPacketInfo.nCurrent + 1 == nTotal )
		{
			chatPacketInfo.nLength = nLastLength;
		}
		chatPacketInfo.nTotal = nTotal;
		
		LPCSTR pData = strSend.GetBuffer( strSend.GetLength() );

		/// 开始发送指定的包
		UINT uDataLength = sizeof( DATAPACKET ) + sizeof( CHATPACKETINFO ) + chatPacketInfo.nLength;
		BYTE *pSendData = new BYTE[ uDataLength ];
		memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
		memcpy( pSendData + sizeof( DATAPACKET ), &chatPacketInfo, sizeof( CHATPACKETINFO ) );
		memcpy( pSendData + sizeof( DATAPACKET ) + sizeof( CHATPACKETINFO ),
			pData + chatPacketInfo.nCurrent * MAXCHATLENGTH,
			chatPacketInfo.nLength );

		strSend.ReleaseBuffer( -1 );
		
		/// 发送数据
		m_pLisSocket->SendTo( pSendData, uDataLength, DEFAULT_PORT, szIP );
		
		delete pSendData;

		/// 发送的是最后一个包
		if( chatPacketInfo.nCurrent + 1 == nTotal )
		{
			m_mapSendChatMessage.RemoveKey( szIP );
		}
	}
}

/// 把指定ip的用户的头像加入到托盘动态显示
void CInstantMessagingDlg::AddTrayIcon( LPCSTR szIP )
{
	/// 得到szIP对应的好友序号
	for( int nIndex = 0; nIndex < m_arrFriends.GetSize(); nIndex++ )
	{
		if( 0 == strcmp( szIP, m_arrFriends.GetAt( nIndex ).strIP ) )
		{
			break;
		}
	}

	/// 判断头像是否已经在托盘显示
	int nUserIndex = nIndex;
	for( nIndex = 0; nIndex < m_arrMessageArrive.GetSize(); nIndex++ )
	{
		/// 已经在托盘显示，不作任何处理
		if( m_arrMessageArrive.GetAt( nIndex ) == nUserIndex )
		{
			return;
		}
	}

	/// 此用户的头像还没有在托盘显示，增加进入托盘
	m_arrMessageArrive.Add( nUserIndex );
	SetTimer( TIMER_TRAYSHOW, 400, NULL );
}

/// 发送文件
void CInstantMessagingDlg::OnBtnSendfiles() 
{
	if( !m_dlgSendFilesServer )
	{
		/// GetDesktopWindow()为主对话框
		m_dlgSendFilesServer.Create( IDD_SENDFILES_SERVER, GetDesktopWindow() );
		m_dlgSendFilesServer.ShowWindow( SW_SHOW );
		return;
	}
	else
	{
		if( m_dlgSendFilesServer.IsWindowVisible() )
		{
			::SetForegroundWindow( m_dlgSendFilesServer.m_hWnd );
			m_dlgSendFilesServer.FlashWindow( TRUE );
		}
		else
		{
			m_dlgSendFilesServer.ShowWindow( SW_SHOW );
		}
	}
}

void CInstantMessagingDlg::OnSendfiles() 
{
	OnBtnSendfiles();
}

void CInstantMessagingDlg::OnReceivefiles() 
{
	if( !m_dlgSendFilesClient )
	{
		/// GetDesktopWindow()为主对话框
		m_dlgSendFilesClient.Create( IDD_SENDFILES_CLIENT, GetDesktopWindow() );
		m_dlgSendFilesClient.ShowWindow( SW_SHOW );
		return;
	}
	else
	{
		if( m_dlgSendFilesClient.IsWindowVisible() )
		{
			::SetForegroundWindow( m_dlgSendFilesClient.m_hWnd );
			m_dlgSendFilesClient.FlashWindow( TRUE );
		}
		else
		{
			m_dlgSendFilesClient.ShowWindow( SW_SHOW );
		}
	}
}

/// 向指定IP用户发送传送文件的通知
void CInstantMessagingDlg::SendFilesNotify( LPCSTR szIP, CString strFile, DWORD dwLength )
{
	DATAPACKET dataPacket;
	dataPacket.command = SENDFILES_NOTIFY;
	dataPacket.dwLength = strFile.GetLength();
	
	UINT uDataLength = sizeof( DATAPACKET ) + strFile.GetLength() + sizeof( DWORD );
	BYTE *pSendData = new BYTE[ uDataLength ];
	memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
	memcpy( pSendData + sizeof( DATAPACKET ), 
		strFile.GetBuffer( strFile.GetLength() ), 
		strFile.GetLength() );
	strFile.ReleaseBuffer( -1 );
	memcpy( pSendData + sizeof( DATAPACKET ) + strFile.GetLength(),
		&dwLength,
		sizeof( DWORD ) );
	
	/// 发送数据
	m_pLisSocket->SendTo( pSendData, uDataLength, DEFAULT_PORT, szIP );
	
	delete pSendData;
}

/// 回应是否接收传输的文件
void CInstantMessagingDlg::SendFilesResponse( LPCSTR szReceive, LPCSTR szIP )
{
	DATAPACKET dataPacket;
	memcpy( &dataPacket, szReceive, sizeof( DATAPACKET ) );

	for( int nIndex = 0; nIndex < m_arrFriends.GetSize(); nIndex++ )
	{
		/// 找到发送文件的USER
		if( 0 == strcmp( szIP, m_arrFriends.GetAt( nIndex ).strIP ) )
		{
			break;
		}
	}

	CString strFile;
	memcpy( strFile.GetBuffer( dataPacket.dwLength ), 
		szReceive + sizeof( DATAPACKET ),
		dataPacket.dwLength );
	strFile.ReleaseBuffer( -1 );
	DWORD dwLength;
	memcpy( &dwLength, szReceive + sizeof( DATAPACKET ) + dataPacket.dwLength,
		sizeof( DWORD ) );

	CString strPromp;
	strPromp.Format( "来自 %s 的好友 %s 向您发送文件 %s\n您是否接收？", 
		m_arrFriends.GetAt( nIndex ).strIP,
		m_arrFriends.GetAt( nIndex ).strName,
		strFile.Right( strFile.GetLength() - 1 - strFile.ReverseFind( '\\' ) ) );
	if( IDCANCEL == MessageBox( strPromp, "接收文件", MB_OKCANCEL | MB_ICONINFORMATION | MB_DEFBUTTON1 ) )
	{
		DenyReceiveFile( strFile, szIP );
		return;
	}

	/// 打开接收文件对话框
	OnReceivefiles();
	
	m_dlgSendFilesClient.ReceiveFileFromIP( strFile, szIP, dwLength );
}

/// 拒绝接收文件
void CInstantMessagingDlg::DenyReceiveFile( CString strFilePath, LPCSTR szIP )
{
	/// 发送拒绝接收的消息
	DATAPACKET dataPacket;
	dataPacket.command = SENDFILES_DENY;
	dataPacket.dwLength = strFilePath.GetLength();
	
	UINT uDataLength = sizeof( DATAPACKET ) + strFilePath.GetLength();
	BYTE *pSendData = new BYTE[ uDataLength ];
	memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
	memcpy( pSendData + sizeof( DATAPACKET ), 
		strFilePath.GetBuffer( strFilePath.GetLength() ), 
		strFilePath.GetLength() );
	strFilePath.ReleaseBuffer( -1 );
	
	/// 发送数据
	m_pLisSocket->SendTo( pSendData, uDataLength, DEFAULT_PORT, szIP );
	
	delete pSendData;
}

/// 由IP得到USER
void CInstantMessagingDlg::GetUserFromIP( LPCSTR szIP, USER &user )
{
	for( int nIndex = 0; nIndex < m_arrFriends.GetSize(); nIndex++ )
	{
		if( 0 == strcmp( szIP, m_arrFriends.GetAt( nIndex ).strIP ) )
		{
			memcpy( &user, &m_arrFriends.GetAt( nIndex ), sizeof( USER ) );
			break;
		}
	}
}
void CInstantMessagingDlg::OnAddSection() 
{
	/// 如果是下线状态，不能添加好友
	if( STATE_OFFLINE == m_wState )
	{
		return;
	}	

	CreateThread( NULL, 0, AddFriendsProc, this, 0, NULL );
}

/// 得到自己IP列表框的IP
CString CInstantMessagingDlg::GetComboBoxIP()
{
	CString strIP;
	m_comboxIP.GetWindowText( strIP );
	return strIP;
}

/// 添加网段用户的进程函数
DWORD WINAPI AddFriendsProc( LPVOID lpParameter )
{
	CInstantMessagingDlg *pDlg = ( CInstantMessagingDlg * )lpParameter;

	/// 定义数据包
	DATAPACKET dataPacket;
	dataPacket.command = REQUEST_ADD;
	
	/// 设置请求的用户结构
	USER user;
	user.bHasCamera	= pDlg->HasCamera();
	user.nFace		= pDlg->GetFace();
	
	/// 分配空间
	UINT uDataLength = sizeof( DATAPACKET ) + sizeof( USER );
	BYTE *pSendData = new BYTE[ uDataLength ];
	memcpy( user.strName, pDlg->GetNickName().GetBuffer( MAXNICKNAMELENGTH + 1 ), MAXNICKNAMELENGTH + 1 );
	pDlg->GetNickName().ReleaseBuffer();
	memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
	memcpy( pSendData + sizeof( DATAPACKET ), &user, sizeof( USER ) );

	CString strIP = pDlg->GetComboBoxIP();

	/// 得到前缀
	CString strPre = strIP.Left( strIP.ReverseFind( '.' ) + 1 );
	
	for( int i = 1 ; i <= 254; i++ )
	{
		CString strAddIP;
		strAddIP.Format( "%s%d", strPre.GetBuffer( strIP.GetLength() ), i );
		strPre.ReleaseBuffer( -1 );
				
		if( strAddIP != strIP )
		{
			/// 发送请求
			pDlg->m_pSocket.SendTo( pSendData, uDataLength, DEFAULT_PORT, strAddIP );	
		}
		Sleep( 200 );
	}
	
	delete pSendData;
	return 0;
}
void CInstantMessagingDlg::OnBtnWhiteboard() 
{
	if( !m_dlgWhiteBoardServer )
	{
		/// GetDesktopWindow()为主对话框
		m_dlgWhiteBoardServer.Create( IDD_WHITEBOARD_SERVER, GetDesktopWindow() );
		m_dlgWhiteBoardServer.ShowWindow( SW_SHOW );
		return;
	}
	else
	{
		::SetForegroundWindow( m_dlgWhiteBoardServer.m_hWnd );
		m_dlgWhiteBoardServer.FlashWindow( TRUE );
	}	
}

void CInstantMessagingDlg::OnWhiteboard() 
{
	OnBtnWhiteboard();
}

