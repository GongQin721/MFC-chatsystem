#if !defined(AFX_SENDFILESCLIENTDLG_H__31959843_17BF_45BC_9ABF_530E453AE1B2__INCLUDED_)
#define AFX_SENDFILESCLIENTDLG_H__31959843_17BF_45BC_9ABF_530E453AE1B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SendFilesClientDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSendFilesClientDlg dialog

class CInstantMessagingDlg;
class CReceiveFilesSocket;

class CSendFilesClientDlg : public CDialog
{
// Construction
public:
	CSendFilesClientDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSendFilesClientDlg)
	enum { IDD = IDD_SENDFILES_CLIENT };
	CListCtrl	m_listCtrlReceive;
	//}}AFX_DATA
	
private:
	/// 初始化工作
	void Init();

public:
	/// 从指定IP接收数据
	void ReceiveFileFromIP( CString strFilePath, LPCSTR szIP, DWORD dwLength );

	/// 数据接收完毕发消息
	void ReceivedDone();

	/// 更新列表框
	void RefreshListBox();
	
private:
	CInstantMessagingDlg	*m_pMainDlg;		/// 主对话框

	CObArray				m_arrReceiveThread;	/// 接收文件的线程列表

	CArray< USER, USER >	m_arrUserSend;		/// 要发往的用户

	unsigned long			m_ulTime;			/// 记录时间


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSendFilesClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSendFilesClientDlg)
	afx_msg void OnDelete();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDFILESCLIENTDLG_H__31959843_17BF_45BC_9ABF_530E453AE1B2__INCLUDED_)
