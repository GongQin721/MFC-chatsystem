#if !defined(AFX_RECEIVEFILESSOCKET_H__389A31D1_CA8F_41E8_8FB7_D4A58BA9E8F3__INCLUDED_)
#define AFX_RECEIVEFILESSOCKET_H__389A31D1_CA8F_41E8_8FB7_D4A58BA9E8F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReceiveFilesSocket.h : header file
//

class CSendFilesClientThread;

/////////////////////////////////////////////////////////////////////////////
// CReceiveFilesSocket command target

class CReceiveFilesSocket : public CSocket
{
// Attributes
private:
	CSendFilesClientThread			*m_pSFCThead;			/// 与此socket相关连的线程

public:
	/// 设置线程指针
	void SetSendFileClientThread( CSendFilesClientThread *SFCThead )
	{
		m_pSFCThead = SFCThead;
	}

// Operations
public:
	CReceiveFilesSocket();
	virtual ~CReceiveFilesSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReceiveFilesSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CReceiveFilesSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECEIVEFILESSOCKET_H__389A31D1_CA8F_41E8_8FB7_D4A58BA9E8F3__INCLUDED_)
