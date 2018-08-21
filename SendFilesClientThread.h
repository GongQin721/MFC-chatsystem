#if !defined(AFX_SENDFILESCLIENTTHREAD_H__B50835DE_3B5E_4D21_B116_E482C7130E1D__INCLUDED_)
#define AFX_SENDFILESCLIENTTHREAD_H__B50835DE_3B5E_4D21_B116_E482C7130E1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SendFilesClientThread.h : header file
//

#include "ReceiveFilesSocket.h"
#include "SendFilesClientDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CSendFilesClientThread thread

class CSendFilesClientThread : public CWinThread
{
	DECLARE_DYNCREATE(CSendFilesClientThread)
protected:
	CSendFilesClientThread();           // protected constructor used by dynamic creation

// Attributes
private:
	CReceiveFilesSocket		m_receiveFilesSocket;				/// 与此线程相关的socket
	CSendFilesClientDlg		*m_pDlgSendFilesClient;				/// 接收文件对话框指针
	DWORD					m_dwLength;							/// 要传输文件的总长度
	DWORD					m_dwReceived;						/// 已经接收的长度
	CString					m_strSourcePath;					/// 传输文件的源路径
	char					m_szSoureceIP[ 16 ];				/// 传输文件的源IP
	CString					m_strDesPath;						/// 保存的路径
	CString					m_strConfig;						/// 配置文件的路径
	BOOL					m_bRun;								/// 程序持续运行的标记

	CFile					m_fileSave;							/// 保存的文件类
	CFile					m_fileCfg;							/// 配置的文件类　

	DWORD					m_dwReceiveCount;					/// 在timer内接收的长度

	BOOL					m_bStop;							/// 是否停止接收文件

// Operations
public:
	/// 附加套接字
	void AttachSocket( SOCKET hSocket );

	/// 接收网络数据
	void OnReceive();

	/// 接收文件对话框指针
	void SetSendFilesClientDlg( CSendFilesClientDlg *pDlgSendFilesClient )
	{
		m_pDlgSendFilesClient = pDlgSendFilesClient;
	}

	/// 设置
	void SetInfo( CString strSourcePath, CString strDesPath, DWORD dwLength, LPCSTR szSourceIP )
	{
		m_strSourcePath = strSourcePath;
		m_strDesPath	= strDesPath;
		m_strConfig		= m_strDesPath.Left( m_strDesPath.ReverseFind( '\\' ) + 1 ) 
			+ m_strDesPath.Right( m_strDesPath.GetLength() - 1 - m_strDesPath.ReverseFind( '\\' ) )
			+ "." + SENDFILES_CONFIG_SUB;
		m_dwLength		= dwLength;
		m_dwReceived	= 0;
		memcpy( m_szSoureceIP, szSourceIP, 16 );
	}

	/// 发送请求文件的消息
	void SendReceiveMessage( DWORD dwReceived );

	/// 接收数据
	void ReceiveData( LPCSTR szReceive );
	
	/// 删除接收线程
	void StopReceive();

	/// 关闭连接
	void OnClose();

	CString GetSourceFilePath(){ return m_strSourcePath; }
	CString GetDesFilePath(){ return m_strDesPath; }
	LPCSTR	GetIP(){ return m_szSoureceIP; }
	DWORD	GetLength(){ return m_dwLength; }
	DWORD	GetReceived(){ return m_dwReceived; }
	BOOL	GetStop(){ return m_bStop ; }
	DWORD	GetReceiveCount(){ DWORD dwReceiveCount = m_dwReceiveCount; m_dwReceiveCount = 0; return dwReceiveCount; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSendFilesClientThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSendFilesClientThread();

	// Generated message map functions
	//{{AFX_MSG(CSendFilesClientThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDFILESCLIENTTHREAD_H__B50835DE_3B5E_4D21_B116_E482C7130E1D__INCLUDED_)
