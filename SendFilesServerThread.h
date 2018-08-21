#if !defined(AFX_SendFilesServerThread_H__3B5C4F9F_1FE0_4882_BEA2_970801DAB869__INCLUDED_)
#define AFX_SendFilesServerThread_H__3B5C4F9F_1FE0_4882_BEA2_970801DAB869__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SendFilesServerThread.h : header file
//

#include "SendFilesSocket.h"
#include "SendFilesServerDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CSendFilesServerThread thread

class CSendFilesServerThread : public CWinThread
{
	DECLARE_DYNCREATE(CSendFilesServerThread)
protected:
	CSendFilesServerThread();           // protected constructor used by dynamic creation

// Attributes
private:
	CSendFilesSocket		m_sendFilesSocket;				/// 与此线程相关的socket
	CSendFilesServerDlg		*m_pDlgSendFileServer;			/// 发送文件服务器对话框指针
	DWORD					m_dwLength;						/// 要传输文件的总长度
	DWORD					m_dwSended;						/// 已经传输的长度
	CString					m_strSourcePath;				/// 传输文件的源路径
	char					m_szDesIP[ 16 ];				/// 接收的IP
	BOOL					m_bRun;							/// 程序持续运行的标记

	CFile					m_fileSend;						/// 发送文件类

	DWORD					m_dwSendCount;					/// 在timer内发送的长度

	BOOL					m_bStop;						/// 是否停止发送文件

// Operations
public:
	/// 附加套接字
	void AttachSocket( SOCKET hSocket );

	/// 接收网络数据
	void OnReceive();

	/// 设置发送文件服务器对话框的指针
	void SetSendFilesServerDlg( CSendFilesServerDlg *pDlgSendFileServer )
	{
		m_pDlgSendFileServer = pDlgSendFileServer;
	}

	CString GetFilePath(){ return m_strSourcePath; }
	LPCSTR	GetIP(){ return m_szDesIP; }
	DWORD	GetLength(){ return m_dwLength; }
	DWORD	GetSended(){ return m_dwSended; }
	BOOL	GetStop(){ return m_bStop ; }
	DWORD	GetSendCount(){ DWORD dwSendCount = m_dwSendCount; m_dwSendCount = 0; return dwSendCount; }

	/// 删除传输线程
	void StopSend();

	/// 关闭连接
	void OnClose();

private:
	/// 设置
	void SetInfo( LPCSTR szReceive );

	/// 发送数据
	void SendData( LPCSTR szReceive );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSendFilesServerThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSendFilesServerThread();

	// Generated message map functions
	//{{AFX_MSG(CSendFilesServerThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SendFilesServerThread_H__3B5C4F9F_1FE0_4882_BEA2_970801DAB869__INCLUDED_)
