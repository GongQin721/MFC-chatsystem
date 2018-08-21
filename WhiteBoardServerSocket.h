#if !defined(AFX_WHITEBOARDSERVERSOCKET_H__50BA63CF_2EE3_405C_A72F_CFC5A191500A__INCLUDED_)
#define AFX_WHITEBOARDSERVERSOCKET_H__50BA63CF_2EE3_405C_A72F_CFC5A191500A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WhiteBoardServerSocket.h : header file
//


#include "WhiteBoardServerDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CWhiteBoardServerSocket command target

class CWhiteBoardServerSocket : public CSocket
{
// Attributes
private:
	CWhiteBoardServerDlg		*m_pWBServerDlg;				/// 白板服务器对话框指针

// Operations
public:
	CWhiteBoardServerSocket();
	virtual ~CWhiteBoardServerSocket();

	/// 带白板服务器对话框指针的构造函数
	CWhiteBoardServerSocket( CWhiteBoardServerDlg * pWBServerDlg );

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWhiteBoardServerSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CWhiteBoardServerSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WHITEBOARDSERVERSOCKET_H__50BA63CF_2EE3_405C_A72F_CFC5A191500A__INCLUDED_)
