#if !defined(AFX_SENDFILESSERVERSOCKET_H__7DD99C42_C676_40F1_BAF0_663D9BF27588__INCLUDED_)
#define AFX_SENDFILESSERVERSOCKET_H__7DD99C42_C676_40F1_BAF0_663D9BF27588__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SendFilesServerSocket.h : header file
//

#include "SendFilesServerDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CSendFilesServerSocket command target

class CSendFilesServerSocket : public CSocket
{
// Attributes
private:
	CSendFilesServerDlg		*m_pSFSDlg;			/// 发送文件服务器的以话框指针

// Operations
public:
	CSendFilesServerSocket();
	virtual ~CSendFilesServerSocket();

	/// 带发送文件服务器的以话框指针的构造函数
	CSendFilesServerSocket( CSendFilesServerDlg *pSFSDlg ){ m_pSFSDlg = pSFSDlg;}

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSendFilesServerSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CSendFilesServerSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDFILESSERVERSOCKET_H__7DD99C42_C676_40F1_BAF0_663D9BF27588__INCLUDED_)
