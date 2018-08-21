#if !defined(AFX_CHATROOMCLIENTDLG_H__FF08831A_5EAE_4394_8072_7B29D03BA943__INCLUDED_)
#define AFX_CHATROOMCLIENTDLG_H__FF08831A_5EAE_4394_8072_7B29D03BA943__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChatRoomClientDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChatRoomClientDlg dialog

class CInstantMessagingDlg;
class CChatRoomClientSocket;

class CChatRoomClientDlg : public CDialog
{
// Construction
public:
	CChatRoomClientDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChatRoomClientDlg)
	enum { IDD = IDD_CHATROOM_CLIENT };
	CEdit	m_editSend;
	CEdit	m_editReceived;
	CListCtrl	m_listCtrlInChat;
	//}}AFX_DATA

private:
	/// 初始化工作
	void Init();

	/// 向指定IP、PORT发送指定用户和数据
	void SendUserCommandToIP( CONTROLCOMMAND command, LPCSTR szIP, UINT uPort, const USER *pUser );

	/// 向指定IP、PORT发送消息数据
	void SendTextToIP( LPCSTR szDesIP, UINT uPort, CString strSendText );

	/// 向聊天室添加用户
	void AddUserToChatRoom( const USER user );

	/// 移除用户
	void DelUserFromChatRoom( const USER user );

	/// 服务器关闭
	void ServerClosed();

	/// 被踢出聊天室
	void Kicked();

	/// 接收文本消息
	void ReceiveText( CHATROOMMESSAGEINFO CRMInfo, char *pData, DWORD dwTextLength ); 

private:
	CInstantMessagingDlg	*m_pMainDlg;		/// 主对话框
	CImageList				m_imageList;		/// 头像图像列表
	CArray< USER, USER >	m_arrFriendsInChat;	/// 聊天室中的好友列表
	CChatRoomClientSocket	*m_pCRCSocket;		/// 聊天室客户端socket

public:
	/// 接收网络数据
	void OnReceive();

	/// 返回对应的服务器IP
	CString GetServerIP();

	/// 添加服务器和自己到用户列表框
	void AcceptAddRequest( const USER userServer );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatRoomClientDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChatRoomClientDlg)
	afx_msg void OnOk();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnSend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATROOMCLIENTDLG_H__FF08831A_5EAE_4394_8072_7B29D03BA943__INCLUDED_)
