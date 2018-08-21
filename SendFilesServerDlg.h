#if !defined(AFX_SENDFILESSERVERDLG_H__AC1469C2_2BA6_4841_9BE2_6639EAB9D243__INCLUDED_)
#define AFX_SENDFILESSERVERDLG_H__AC1469C2_2BA6_4841_9BE2_6639EAB9D243__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SendFilesServerDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSendFilesServerDlg dialog

class CInstantMessagingDlg;
class CSendFilesServerThread;
class CSendFilesServerSocket;
class CSendFilesSocket;

class CSendFilesServerDlg : public CDialog
{
// Construction
public:
	CSendFilesServerDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSendFilesServerDlg)
	enum { IDD = IDD_SENDFILES_SERVER };
	CListCtrl	m_listCtrlSend;
	CButton	m_btnDelete;
	CButton	m_btnAdd;
	//}}AFX_DATA

private:
	/// 初始化工作
	void Init();

public:
	/// 接收请求
	void OnAccept();

	/// 设置要接收的用户
	void SetReceivedUser( CArray< USER, USER > &arrUserSend );

	/// 拒绝接收文件
	void DenyReceiveFile( CString strFilePath, LPCSTR szIP );

	/// 更新列表框
	void RefreshListBox();

private:
	CInstantMessagingDlg	*m_pMainDlg;		/// 主对话框

	CSendFilesServerSocket	*m_pSFServerSocket;
												/// 监听的socket

	CArray< CString, CString >
							m_arrSendFiles;		/// 要发送的文件列表
	CArray< USER, USER >	m_arrUserSend;		/// 要发往的用户

	CObArray				m_arrSendThread;	/// 发送文件的线程列表

	unsigned long			m_ulTime;			/// 记录时间


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSendFilesServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSendFilesServerDlg)
	afx_msg void OnOk();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();
	afx_msg void OnDelete();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDFILESSERVERDLG_H__AC1469C2_2BA6_4841_9BE2_6639EAB9D243__INCLUDED_)
