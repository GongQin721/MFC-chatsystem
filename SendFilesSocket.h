#if !defined(AFX_SENDFILESSOCKET_H__15CAEF68_3EAE_4362_970C_51368872DE0A__INCLUDED_)
#define AFX_SENDFILESSOCKET_H__15CAEF68_3EAE_4362_970C_51368872DE0A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SendFilesSocket.h : header file
//

class CSendFilesServerThread;

/////////////////////////////////////////////////////////////////////////////
// CSendFilesSocket command target

class CSendFilesSocket : public CSocket
{
// Attributes
private:
	CSendFilesServerThread			*m_pSFSThead;			/// 与此socket相关连的线程

public:
	/// 设置线程指针
	void SetSendFileServerThread( CSendFilesServerThread *pSFSThead )
	{
		m_pSFSThead = pSFSThead;
	}

// Operations
public:
	CSendFilesSocket();
	virtual ~CSendFilesSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSendFilesSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CSendFilesSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDFILESSOCKET_H__15CAEF68_3EAE_4362_970C_51368872DE0A__INCLUDED_)
