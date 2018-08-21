#if !defined(AFX_LISTENINGSOCKET_H__106EF71A_DB57_43A5_AA17_A99F36801F88__INCLUDED_)
#define AFX_LISTENINGSOCKET_H__106EF71A_DB57_43A5_AA17_A99F36801F88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListeningSocket.h : header file
//


#include "InstantMessagingDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CListeningSocket command target

class CListeningSocket : public CSocket
{
// Attributes
private:
	CInstantMessagingDlg		* m_pMainDlg;				/// 主对话框

// Operations
public:
	CListeningSocket();
	virtual ~CListeningSocket();

	/// 带主对话框指针的构造函数
	CListeningSocket( CInstantMessagingDlg * );

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListeningSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CListeningSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTENINGSOCKET_H__106EF71A_DB57_43A5_AA17_A99F36801F88__INCLUDED_)
