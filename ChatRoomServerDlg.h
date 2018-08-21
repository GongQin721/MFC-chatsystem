#if !defined(AFX_CHATROOMSERVERDLG_H__15DBAC8F_1F81_4EB6_95F3_C543D7BEAADB__INCLUDED_)
#define AFX_CHATROOMSERVERDLG_H__15DBAC8F_1F81_4EB6_95F3_C543D7BEAADB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChatRoomServerDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChatRoomServerDlg dialog

#include "AdvButton.h"

class CInstantMessagingDlg;
class CChatRoomServerSocket;

class CChatRoomServerDlg : public CDialog
{
// Construction
public:
	CChatRoomServerDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChatRoomServerDlg)
	enum { IDD = IDD_CHATROOM_SERVER };
	CEdit	m_editSend;
	CEdit	m_editReceived;
	CListCtrl	m_listCtrlOutOfChat;
	CListCtrl	m_listCtrlInChat;
	CAdvButton	m_btnDelFriends;
	CAdvButton	m_btnAddFriends;
	//}}AFX_DATA

private:
	/// 初始化工作
	void Init();

	/// 向指定IP、PORT发送指定用户和数据
	void SendUserCommandToIP( CONTROLCOMMAND command, LPCSTR szIP, UINT nPort, const USER *pUser );

	/// 向指定IP、PORT发送消息数据
	void SendTextToIP( LPCSTR szDesIP, UINT uPort, CString strSendText, LPCSTR szTextIP );

	/// 向聊天室添加用户
	void AddUserToChatRoom( const USER user );

	/// 移除用户
	void DelUserFromChatRoom( const USER user );

	/// 更新添加和删除按钮
	void UpdateButtons();

	/// 接收文本消息
	void ReceiveText( CHATROOMMESSAGEINFO CRMInfo, char *pData, DWORD dwTextLength ); 

private:
	CInstantMessagingDlg	*m_pMainDlg;		/// 主对话框
	CImageList				m_imageList;		/// 头像图像列表
	CArray< USER, USER >	m_arrFriendsInChat;	/// 聊天室中的好友列表
	CArray< USER, USER >	m_arrFriendsOutOfChat;
												/// 不在聊天室中的好友列表
	CChatRoomServerSocket	*m_pCRSSocket;		/// 聊天室服务器socket

public:
	/// 接收网络数据
	void OnReceive();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatRoomServerDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChatRoomServerDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnColse();
	afx_msg void OnSend();
	afx_msg void OnAddfriends();
	afx_msg void OnDelfriends();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATROOMSERVERDLG_H__15DBAC8F_1F81_4EB6_95F3_C543D7BEAADB__INCLUDED_)
