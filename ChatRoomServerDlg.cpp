// ChatRoomServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "instantmessaging.h"
#include "ChatRoomServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChatRoomServerDlg dialog

#include "InstantMessagingDlg.h"
#include "ChatRoomServerSocket.h"

CChatRoomServerDlg::CChatRoomServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatRoomServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChatRoomServerDlg)
	//}}AFX_DATA_INIT

	/// 加载图像列表，并将32*32的图像缩小为16*16
	m_imageList.Create( 16, 16, ILC_MASK | ILC_COLOR24, 0, 0 );
	CBitmap bitmap32;
	CBitmap bitmap16;
	HBITMAP hBitmap;
	for( int nIndex = 0; nIndex < MAXFACES; nIndex++ )
	{
		bitmap32.LoadBitmap( IDB_BITMAP1 + nIndex );
		hBitmap = ( HBITMAP )::CopyImage( ( HBITMAP )bitmap32, IMAGE_BITMAP, 16, 16, LR_COPYDELETEORG );
		bitmap16.Attach( hBitmap );
		m_imageList.Add( &bitmap16, FACEBGCOLOR );
		bitmap16.DeleteObject();
		bitmap32.DeleteObject();
		::DeleteObject( hBitmap );
	}
}


void CChatRoomServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChatRoomServerDlg)
	DDX_Control(pDX, IDE_SEND, m_editSend);
	DDX_Control(pDX, IDE_RECEIVED, m_editReceived);
	DDX_Control(pDX, IDC_LIST_OUTOFCHAT, m_listCtrlOutOfChat);
	DDX_Control(pDX, IDC_LIST_INCHAT, m_listCtrlInChat);
	DDX_Control(pDX, IDB_DELFRIENDS, m_btnDelFriends);
	DDX_Control(pDX, IDB_ADDFRIENDS, m_btnAddFriends);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChatRoomServerDlg, CDialog)
	//{{AFX_MSG_MAP(CChatRoomServerDlg)
	ON_BN_CLICKED(IDB_COLSE, OnColse)
	ON_BN_CLICKED(IDB_SEND, OnSend)
	ON_BN_CLICKED(IDB_ADDFRIENDS, OnAddfriends)
	ON_BN_CLICKED(IDB_DELFRIENDS, OnDelfriends)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatRoomServerDlg message handlers

BOOL CChatRoomServerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	/// 进行初始化工作
	Init();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChatRoomServerDlg::OnOK() 
{
}

void CChatRoomServerDlg::OnCancel() 
{	
	if( IDOK == MessageBox( "要关闭聊天室吗？", "关闭", MB_OKCANCEL | MB_ICONINFORMATION | MB_DEFBUTTON2 ) )
	{
		/// 向所有客户端发送关闭服务器消息
		for( int nIndex = 1; nIndex < m_listCtrlInChat.GetItemCount(); nIndex++ )
		{
			USER user = m_arrFriendsInChat.GetAt( nIndex );
			SendUserCommandToIP( CHATROOM_SERVER_CLOSED, user.strIP, CHATROOM_CLIENT_PORT, NULL );
		}

		/// 关闭UDP套接字
		m_pCRSSocket->Close();
		delete [] m_pCRSSocket;
		m_pCRSSocket = NULL;

		/// 清空用户列表
		m_arrFriendsInChat.RemoveAll();
		m_arrFriendsOutOfChat.RemoveAll();

		DestroyWindow();
	}
}

void CChatRoomServerDlg::Init()
{
	/// 获取主对话框
	m_pMainDlg = ( CInstantMessagingDlg * )::AfxGetMainWnd();

	/// 设置添加联系人的图标
	m_btnAddFriends.setBmp( IDB_CHATROOM_ADD_NORMAL, 
							IDB_CHATROOM_ADD_HOVER, 
							IDB_CHATROOM_ADD_DOWN, 
							IDB_CHATROOM_ADD_DISABLE );

	/// 设置删除联系人的图标
	m_btnDelFriends.setBmp( IDB_CHATROOM_DEL_NORMAL, 
							IDB_CHATROOM_DEL_HOVER, 
							IDB_CHATROOM_DEL_DOWN, 
							IDB_CHATROOM_DEL_DISABLE );

	/// 设置用户列表框的图像
	m_listCtrlInChat.SetImageList( &m_imageList, LVSIL_SMALL );
	m_listCtrlInChat.SetExtendedStyle( m_listCtrlInChat.GetExtendedStyle() | 
		LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES );
	m_listCtrlInChat.InsertColumn( 0, "" );

	m_listCtrlOutOfChat.SetImageList( &m_imageList, LVSIL_SMALL );
	m_listCtrlOutOfChat.SetExtendedStyle( m_listCtrlOutOfChat.GetExtendedStyle() | 
		LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES );
	m_listCtrlOutOfChat.InsertColumn( 0, "" );

	/// 设置不在聊天室的好友，并全部选中
	m_pMainDlg->GetFriendsArray( m_arrFriendsOutOfChat );
	for( int nIndex = 0; nIndex < m_arrFriendsOutOfChat.GetSize(); nIndex++ )
	{
		USER user = m_arrFriendsOutOfChat.GetAt( nIndex );
		CString strText;
		strText.Format( "%s(%s)", user.strName, user.strIP );
		m_listCtrlOutOfChat.InsertItem( nIndex, strText, user.nFace );
		m_listCtrlOutOfChat.SetCheck( nIndex );
		m_listCtrlOutOfChat.SetColumnWidth( 0, LVSCW_AUTOSIZE_USEHEADER );
	}

	/// 将自己加入聊天室
	USER user;
	user.bHasCamera = m_pMainDlg->HasCamera();
	user.nFace		= m_pMainDlg->GetFace();
	strcpy( user.strName, m_pMainDlg->GetNickName().GetBuffer( MAXNICKNAMELENGTH ) );
	CString strText;
	strText.Format( "%s(创建者)", user.strName );
	m_listCtrlInChat.InsertItem( 0, strText, user.nFace );
	m_listCtrlInChat.SetColumnWidth( 0, LVSCW_AUTOSIZE_USEHEADER );
	m_arrFriendsInChat.Add( user );

	/// 设置　添加　和　删除　按钮的状态
	if( 0 == m_arrFriendsOutOfChat.GetSize() )
	{
		m_btnAddFriends.EnableWindow( FALSE );	
	}
	else
	{	
		m_btnAddFriends.SetNormal();
	}
	m_btnDelFriends.EnableWindow( FALSE );

	/// 初始化UDP套接字
	m_pCRSSocket = new CChatRoomServerSocket( this );
	m_pCRSSocket->Create( CHATROOM_SERVER_PORT, SOCK_DGRAM );

	/// 限定发送消息的最大字数
	m_editSend.SetLimitText( MAXDATAPACKETLENGTH - sizeof( DATAPACKET ) - sizeof( CHATROOMMESSAGEINFO ) );
}

/// 向指定IP、PORT发送指定数据
void CChatRoomServerDlg::SendUserCommandToIP( CONTROLCOMMAND command, LPCSTR szIP, UINT uPort, const USER *pUser )
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
	m_pCRSSocket->SendTo( pSendData, uDataLength, uPort, szIP );

	delete pSendData;
}

/// 从UDP中接收数据
void CChatRoomServerDlg::OnReceive()
{
	/// 接收数据
	CString strIP;
	UINT uPort;
	char szReceive[ MAXDATAPACKETLENGTH ];
	m_pCRSSocket->ReceiveFrom( szReceive, MAXDATAPACKETLENGTH, strIP, uPort );

	/// 装配数据包
	DATAPACKET dataPacket;
	memcpy( &dataPacket, szReceive, sizeof( DATAPACKET ) );
	USER user;
	CHATROOMMESSAGEINFO CRMInfo;

	/// 根据命令进行不同的处理
	switch( dataPacket.command )
	{
	case CHATROOM_ADDREQUEST_DENY:							/// 客户端拒绝加入聊天室服务器
		break;
	case CHATROOM_ADDREQUEST_ALLOW:							/// 客户端允许加入聊天室服务器
		memcpy( &user, szReceive + sizeof( DATAPACKET ), sizeof( USER ) );
		memcpy( user.strIP, strIP.GetBuffer( 16 ), 16 );
		strIP.ReleaseBuffer();
		AddUserToChatRoom( user );
		break;
	case CHATROOM_CLIENT_CLOSED:							/// 客户端关闭聊天室
		memcpy( &user, szReceive + sizeof( DATAPACKET ), sizeof( USER ) );
		memcpy( user.strIP, strIP.GetBuffer( 16 ), 16 );
		strIP.ReleaseBuffer();
		DelUserFromChatRoom( user );
		break;
	case CHATROOM_TEXT:										/// 接收到文本消息
		memcpy( &CRMInfo, szReceive + sizeof( DATAPACKET ), sizeof( CHATROOMMESSAGEINFO ) );
		memcpy( CRMInfo.szSrcIP, strIP.GetBuffer( 16 ), 16 );
		strIP.ReleaseBuffer();
		ReceiveText( CRMInfo, 
			szReceive + sizeof( DATAPACKET ) + sizeof( CHATROOMMESSAGEINFO ), 
			dataPacket.dwLength );
		break;
	default:
		break;
	}
}

void CChatRoomServerDlg::OnColse() 
{
	OnCancel();
}

void CChatRoomServerDlg::OnAddfriends() 
{
	/// 发起聊天室请求的USER
	USER userSelf;
	userSelf.nFace		= m_pMainDlg->GetFace();
	memcpy( userSelf.strName, m_pMainDlg->GetNickName().GetBuffer( MAXNICKNAMELENGTH + 1 ), MAXNICKNAMELENGTH + 1 );

	for( int nIndex = 0; nIndex < m_listCtrlOutOfChat.GetItemCount(); nIndex++ )
	{
		if( m_listCtrlOutOfChat.GetCheck( nIndex ) )
		{
			USER user = m_arrFriendsOutOfChat.GetAt( nIndex );
			SendUserCommandToIP( CHATROOM_ADDREQUEST, user.strIP, DEFAULT_PORT, &userSelf );
		}
	}
}

void CChatRoomServerDlg::OnDelfriends() 
{
	static BOOL bFirst = TRUE;
	for( int nIndex = 1; nIndex < m_listCtrlInChat.GetItemCount(); nIndex++ )
	{
		if( m_listCtrlInChat.GetCheck( nIndex ) )
		{
			if( bFirst == TRUE )
			{
				/// 提示
				CString strPrompt;
				strPrompt.Format( "您是否要从聊天室删除这些好友？" );
				
				/// 拒绝请求
				if( IDCANCEL == MessageBox( strPrompt, "聊天室", MB_OKCANCEL | MB_ICONINFORMATION | MB_DEFBUTTON1 ) )
				{
					return;
				}
				bFirst = FALSE;
			}
			
			USER user = m_arrFriendsInChat.GetAt( nIndex );
			
			/// 向被删除用户发送删除消息
			SendUserCommandToIP( CHATROOM_CLIENT_KICKED, user.strIP, CHATROOM_CLIENT_PORT, NULL );

			/// 把用户从其他聊用户列表中移除
			for( int nIndex1 = 1; nIndex1 < m_arrFriendsInChat.GetSize(); nIndex1++ )
			{
				USER userTmp = m_arrFriendsInChat.GetAt( nIndex1 );
				SendUserCommandToIP( CHATROOM_CLIENT_DELDUSER, userTmp.strIP, CHATROOM_CLIENT_PORT, &user );
			}

			/// 更新接收编辑框
			CString strDelText;
			CTime time = CTime::GetCurrentTime();
			CString strTime = time.Format( "%H:%M:%S" );
			strDelText.Format( "%s(%s) %s 离开了聊天室！\r\n\r\n", 
				user.strName, user.strIP, strTime.GetBuffer( 10 ) );
			strTime.ReleaseBuffer( -1 );
			CString strReceiveText;
			m_editReceived.GetWindowText( strReceiveText );
			m_editReceived.SetWindowText( strReceiveText + strDelText );

			m_arrFriendsOutOfChat.Add( user );
			CString strText;
			strText.Format( "%s(%s)", user.strName, user.strIP );
			m_listCtrlOutOfChat.InsertItem( m_listCtrlOutOfChat.GetItemCount(), strText, user.nFace );
			m_listCtrlOutOfChat.SetCheck( m_listCtrlOutOfChat.GetItemCount() - 1, TRUE );
			m_listCtrlOutOfChat.SetColumnWidth( 0, LVSCW_AUTOSIZE_USEHEADER );
			m_arrFriendsInChat.RemoveAt( nIndex );
			m_listCtrlInChat.DeleteItem( nIndex );
			m_listCtrlInChat.SetColumnWidth( 0, LVSCW_AUTOSIZE_USEHEADER );
			nIndex--;
		}
	}
	bFirst = TRUE;
	
	UpdateButtons();
}

void CChatRoomServerDlg::UpdateButtons()
{
	/// 更改添加好友的按钮状态
	if( 0 != m_arrFriendsInChat.GetSize() )
	{
		m_btnDelFriends.SetNormal();
	}
	else
	{
		m_btnDelFriends.EnableWindow( FALSE );
	}
	
	/// 更改删除好友的按钮
	if( 0 != m_arrFriendsOutOfChat.GetSize() )
	{
		m_btnAddFriends.SetNormal();
	}
	else
	{
		m_btnAddFriends.EnableWindow( FALSE );
	}
}

void CChatRoomServerDlg::AddUserToChatRoom( const USER user )
{
	for( int nIndex = 0; nIndex < m_arrFriendsOutOfChat.GetSize(); nIndex++ )
	{
		USER userNew = m_arrFriendsOutOfChat.GetAt( nIndex );
		if( 0 == strcmp(user.strIP, userNew.strIP ) )
		{
			for( int nIndex1 = 1; nIndex1 < m_arrFriendsInChat.GetSize(); nIndex1++ )
			{
				USER userTmp = m_arrFriendsInChat.GetAt( nIndex1 );

				/// 向新用户聊天室用户列表框中添加已有的用户
				SendUserCommandToIP( CHATROOM_CLIENT_ADDUSER, userNew.strIP, CHATROOM_CLIENT_PORT, &userTmp );

				/// 把新用户添加到已有的用户的聊天室中
				SendUserCommandToIP( CHATROOM_CLIENT_ADDUSER, userTmp.strIP, CHATROOM_CLIENT_PORT, &userNew );
			}

			/// 更新接收编辑框
			CString strJoinText;
			CTime time = CTime::GetCurrentTime();
			CString strTime = time.Format( "%H:%M:%S" );
			strJoinText.Format( "%s(%s) %s 加入了聊天室！\r\n\r\n", 
				userNew.strName, userNew.strIP, strTime.GetBuffer( 10 ) );
			strTime.ReleaseBuffer( -1 );
			CString strReceiveText;
			m_editReceived.GetWindowText( strReceiveText );
			m_editReceived.SetWindowText( strReceiveText + strJoinText );
			m_editReceived.LineScroll( m_editReceived.GetLineCount() );

			/// 更新聊天室列表
			m_arrFriendsInChat.Add( userNew );

			CString strText;
			strText.Format( "%s(%s)", userNew.strName, userNew.strIP );
			m_listCtrlInChat.InsertItem( m_listCtrlInChat.GetItemCount(), strText, userNew.nFace );
			m_listCtrlInChat.SetColumnWidth( 0, LVSCW_AUTOSIZE_USEHEADER );
			m_arrFriendsOutOfChat.RemoveAt( nIndex );
			m_listCtrlOutOfChat.DeleteItem( nIndex );
			m_listCtrlOutOfChat.SetColumnWidth( 0, LVSCW_AUTOSIZE_USEHEADER );
			break;
		}
	}

	UpdateButtons();
}

void CChatRoomServerDlg::DelUserFromChatRoom( const USER user )
{
	/// 把用户从其他聊用户列表中移除
	for( int nIndex = 1; nIndex < m_arrFriendsInChat.GetSize(); nIndex++ )
	{
		USER userTmp = m_arrFriendsInChat.GetAt( nIndex );
		if( 0 != strcmp( user.strIP, userTmp.strIP ) )
		{
			SendUserCommandToIP( CHATROOM_CLIENT_DELDUSER, userTmp.strIP, CHATROOM_CLIENT_PORT, &user );
		}
	}
	
	for( nIndex = 0; nIndex < m_arrFriendsInChat.GetSize(); nIndex++ )
	{
		USER userDel = m_arrFriendsInChat.GetAt( nIndex );
		if( 0 == strcmp(user.strIP, userDel.strIP ) )
		{
			/// 更新接收编辑框
			CString strDelText;
			CTime time = CTime::GetCurrentTime();
			CString strTime = time.Format( "%H:%M:%S" );
			strDelText.Format( "%s(%s) %s 离开了聊天室！\r\n\r\n", 
				userDel.strName, userDel.strIP, strTime.GetBuffer( 10 ) );
			strTime.ReleaseBuffer( -1 );
			CString strReceiveText;
			m_editReceived.GetWindowText( strReceiveText );
			m_editReceived.SetWindowText( strReceiveText + strDelText );
			m_editReceived.LineScroll( m_editReceived.GetLineCount() );

			m_arrFriendsOutOfChat.Add( userDel );
			CString strText;
			strText.Format( "%s(%s)", userDel.strName, userDel.strIP );
			m_listCtrlOutOfChat.InsertItem( m_listCtrlOutOfChat.GetItemCount(), strText, userDel.nFace );
			m_listCtrlOutOfChat.SetCheck( m_listCtrlOutOfChat.GetItemCount() - 1, TRUE );
			m_listCtrlOutOfChat.SetColumnWidth( 0, LVSCW_AUTOSIZE_USEHEADER );
			m_arrFriendsInChat.RemoveAt( nIndex );
			m_listCtrlInChat.DeleteItem( nIndex );
			m_listCtrlInChat.SetColumnWidth( 0, LVSCW_AUTOSIZE_USEHEADER );
			break;
		}
	}
	
	UpdateButtons();
}

/// 向指定IP、PORT发送消息数据
void CChatRoomServerDlg::SendTextToIP( LPCSTR szDesIP, UINT uPort, CString strSendText, LPCSTR szTextIP )
{
	DATAPACKET dataPacket;
	dataPacket.command	= CHATROOM_TEXT;
	dataPacket.dwLength = strSendText.GetLength();
	
	CHATROOMMESSAGEINFO chatRoomMessage;
	CTime time = CTime::GetCurrentTime();
	CString strTime = time.Format( "%H:%M:%S" );
	memcpy( chatRoomMessage.szTime, strTime.GetBuffer( 10 ), 10 );
	strTime.ReleaseBuffer( -1 );
	memcpy( chatRoomMessage.szSrcIP, szTextIP, 16 );

	/// 分配空间
	UINT uDataLength = sizeof( DATAPACKET ) + sizeof( CHATROOMMESSAGEINFO ) + strSendText.GetLength();
	BYTE *pSendData = new BYTE[ uDataLength ];
	memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
	memcpy( pSendData + sizeof( DATAPACKET ), &chatRoomMessage, sizeof( CHATROOMMESSAGEINFO ) );
	memcpy( pSendData + sizeof( DATAPACKET ) + sizeof( CHATROOMMESSAGEINFO ), 
		strSendText.GetBuffer( strSendText.GetLength() ), strSendText.GetLength() );
	strSendText.ReleaseBuffer( -1 );
	
	/// 发送数据
	m_pCRSSocket->SendTo( pSendData, uDataLength, uPort, szDesIP );

	delete pSendData;
}

void CChatRoomServerDlg::OnSend() 
{
	CString strSend;
	m_editSend.GetWindowText( strSend );
	if( strSend.IsEmpty() )
	{
		return;
	}

	m_editSend.SetWindowText( "" );

	/// 更新接收编辑框
	CString strText;
	CTime time = CTime::GetCurrentTime();
	CString strTime = time.Format( "%H:%M:%S" );
	strText.Format( "%s %s\r\n  %s\r\n\r\n", 
		m_pMainDlg->GetNickName().GetBuffer( MAXNICKNAMELENGTH ), 
		strTime.GetBuffer( 10 ),
		strSend.GetBuffer( strSend.GetLength() ) );
	strSend.ReleaseBuffer( -1 );
	strTime.ReleaseBuffer( -1 );
	CString strReceiveText;
	m_editReceived.GetWindowText( strReceiveText );
	m_editReceived.SetWindowText( strReceiveText + strText );
	m_editReceived.LineScroll( m_editReceived.GetLineCount() );

	m_editSend.SetFocus();

	/// 向所有客户端发送消息
	for( int nIndex = 1; nIndex < m_arrFriendsInChat.GetSize(); nIndex++ )
	{
		USER user = m_arrFriendsInChat.GetAt( nIndex );
		SendTextToIP( user.strIP, CHATROOM_CLIENT_PORT, strSend, "" );
	}
}

/// 接收文本消息
void CChatRoomServerDlg::ReceiveText( CHATROOMMESSAGEINFO CRMInfo, char *pData, DWORD dwTextLength )
{
	pData[ dwTextLength ] = 0;
	for( int nIndex = 1; nIndex < m_arrFriendsInChat.GetSize(); nIndex++ )
	{
		USER userSrc = m_arrFriendsInChat.GetAt( nIndex );
		if( 0 == strcmp( userSrc.strIP, CRMInfo.szSrcIP ) )
		{
			CString strText;
			strText.Format( "%s(%s) %s\r\n  %s\r\n\r\n",
				userSrc.strName,
				userSrc.strIP,
				CRMInfo.szTime,
				pData );
			CString strReceiveText;
			m_editReceived.GetWindowText( strReceiveText );
			m_editReceived.SetWindowText( strReceiveText + strText );
			m_editReceived.LineScroll( m_editReceived.GetLineCount() );
			FlashWindow( TRUE );
			
			CString strSend( pData );

			/// 向所有客户端发送消息
			for( int nIndex1 = 1; nIndex1 < m_arrFriendsInChat.GetSize(); nIndex1++ )
			{
				USER userSend = m_arrFriendsInChat.GetAt( nIndex1 );
				if( 0 == strcmp( userSrc.strIP, userSend.strIP ) )
				{
					continue;
				}
				SendTextToIP( userSend.strIP, CHATROOM_CLIENT_PORT, strSend, userSrc.strIP );
			}
			break;
		}
	}	
}

BOOL CChatRoomServerDlg::PreTranslateMessage(MSG* pMsg) 
{
	/// 按Ctrl+Enter发送消息
	if( pMsg->hwnd == m_editSend.m_hWnd && pMsg->message == WM_KEYDOWN )
	{
		switch( pMsg->wParam )       
		{                         
        case VK_RETURN:                                 //回车消息 
			if( ::GetKeyState(VK_CONTROL) < 0 )			//判断是否按下了Control
			{
				OnSend();
				return TRUE;
			}
			break;
		default:
			break;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}
