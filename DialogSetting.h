#if !defined(AFX_DIALOGSETTING_H__D2756048_57B2_44AD_A2BC_954AF388FAA5__INCLUDED_)
#define AFX_DIALOGSETTING_H__D2756048_57B2_44AD_A2BC_954AF388FAA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogSetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogSetting dialog

class CInstantMessagingDlg;

class CDialogSetting : public CDialog
{
// Construction
public:
	CDialogSetting(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogSetting)
	enum { IDD = IDD_SETTING };
	CButton	m_btnAutoAddFriends;
	CComboBoxEx	m_comboxExFace;
	CHotKeyCtrl	m_hotKey;
	CEdit	m_editNickName;
	//}}AFX_DATA

public:
	/// 设置主对话框
	void SetMainDlg( CInstantMessagingDlg *pMainDlg );

private:
	CInstantMessagingDlg		*m_dlgMain;			/// 主界面对话框
	CImageList					m_imageList;		/// 头像的图像列表

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogSetting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogSetting)
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnSave();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGSETTING_H__D2756048_57B2_44AD_A2BC_954AF388FAA5__INCLUDED_)
