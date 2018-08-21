#if !defined(AFX_CHATROOMSERVERSOCKET_H__6D8235DB_78AE_4EEA_9A58_820BF10CD769__INCLUDED_)
#define AFX_CHATROOMSERVERSOCKET_H__6D8235DB_78AE_4EEA_9A58_820BF10CD769__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChatRoomServerSocket.h : header file
//

#include "ChatRoomServerDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CChatRoomServerSocket command target

class CChatRoomServerSocket : public CSocket
{
// Attributes
private:
	CChatRoomServerDlg		*m_pCRServerDlg;				/// 聊天室服务器对话框指针

// Operations
public:
	CChatRoomServerSocket();
	virtual ~CChatRoomServerSocket();

	/// 带聊天室服务器对话框指针的构造函数
	CChatRoomServerSocket( CChatRoomServerDlg * pCRServerDlg );

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatRoomServerSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CChatRoomServerSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATROOMSERVERSOCKET_H__6D8235DB_78AE_4EEA_9A58_820BF10CD769__INCLUDED_)
