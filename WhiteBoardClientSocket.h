#if !defined(AFX_WHITEBOARDCLIENTSOCKET_H__F8203320_E5A3_4AEE_A70F_1511CC62C57C__INCLUDED_)
#define AFX_WHITEBOARDCLIENTSOCKET_H__F8203320_E5A3_4AEE_A70F_1511CC62C57C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WhiteBoardClientSocket.h : header file
//

#include "WhiteBoardClientDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CWhiteBoardClientSocket command target

class CWhiteBoardClientSocket : public CSocket
{
// Attributes
private:
	CWhiteBoardClientDlg		*m_pWBClientDlg;				/// 白板客户端对话框指针

// Operations
public:
	CWhiteBoardClientSocket();
	virtual ~CWhiteBoardClientSocket();

	/// 带白板客户端对话框指针的构造函数
	CWhiteBoardClientSocket( CWhiteBoardClientDlg * pWBClientDlg );

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWhiteBoardClientSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CWhiteBoardClientSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WHITEBOARDCLIENTSOCKET_H__F8203320_E5A3_4AEE_A70F_1511CC62C57C__INCLUDED_)
