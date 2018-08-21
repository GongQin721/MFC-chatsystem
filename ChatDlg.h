//{{AFX_INCLUDES()
#include "richtext.h"
//}}AFX_INCLUDES
#if !defined(AFX_CHATDLG_H__5482D6B5_A745_46C0_B094_6861282CF6C9__INCLUDED_)
#define AFX_CHATDLG_H__5482D6B5_A745_46C0_B094_6861282CF6C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChatDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChatDlg dialog

class CInstantMessagingDlg;

class CChatDlg : public CDialog
{
// Construction
public:
	CChatDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChatDlg)
	enum { IDD = IDD_CHAT };
	CRichText	m_rtReceived;
	CRichText	m_rtSend;
	//}}AFX_DATA
private:
	/// 初始化窗口
	void Init();

private:
	CInstantMessagingDlg	*m_pMainDlg;		/// 主对话框
	CFont					m_font;				/// 发送消息框的字体
	CString					m_strFilePath;		/// 保存聊天记录的文件路径
	USER					m_userChat;			/// 聊天对象的USER
	CBitmap					m_bmpFace;			/// 头像

public:
	/// 返回聊天对象的IP
	LPCSTR GetChatIP(){ return m_userChat.strIP; }

	/// 设置聊天的对象
	void SetChatUser( const USER userChat );

	/// 接收消息
	void ReceiveMessage( LPCSTR szTime, LPCSTR szMessage );


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChatDlg)
	afx_msg void OnOk();
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnSend();
	afx_msg void OnLoadfile();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATDLG_H__5482D6B5_A745_46C0_B094_6861282CF6C9__INCLUDED_)
