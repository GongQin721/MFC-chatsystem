#if !defined(AFX_CHATROOMCLIENTSOCKET_H__2A23FE6C_0AD0_441B_A87C_FB1F06F67918__INCLUDED_)
#define AFX_CHATROOMCLIENTSOCKET_H__2A23FE6C_0AD0_441B_A87C_FB1F06F67918__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChatRoomClientSocket.h : header file
//

#include "ChatRoomClientDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CChatRoomClientSocket command target

class CChatRoomClientSocket : public CSocket
{
// Attributes
private:
	CChatRoomClientDlg		*m_pCRClientDlg;				/// 聊天室客户端对话框指针

// Operations
public:
	CChatRoomClientSocket();
	virtual ~CChatRoomClientSocket();

	/// 带聊天室客户端对话框指针的构造函数
	CChatRoomClientSocket( CChatRoomClientDlg * pCRServerDlg );

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatRoomClientSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CChatRoomClientSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATROOMCLIENTSOCKET_H__2A23FE6C_0AD0_441B_A87C_FB1F06F67918__INCLUDED_)
