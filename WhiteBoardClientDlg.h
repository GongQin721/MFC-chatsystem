#if !defined(AFX_WHITEBOARDCLIENTDLG_H__2874C727_04E1_4EC2_91F9_6AC913C09F07__INCLUDED_)
#define AFX_WHITEBOARDCLIENTDLG_H__2874C727_04E1_4EC2_91F9_6AC913C09F07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "AdvButton.h"
#include "CanvasStatic.h"


class CInstantMessagingDlg;
class CWhiteBoardClientSocket;

class CWhiteBoardClientDlg : public CDialog
{
// Construction
public:
	CWhiteBoardClientDlg(CWnd* pParent = NULL);   // standard constructor

	/// 支持RUNTIME_CLASS
	DECLARE_DYNAMIC( CWhiteBoardClientDlg );

private:
	/// 初始化工作
	void Init();
	
	/// 向指定IP、PORT发送指定用户和数据
	void SendUserCommandToIP( CONTROLCOMMAND command, LPCSTR szIP, UINT nPort, const USER *pUser );
	
	/// 调整各控件的位置
	void SetPosition();
	
	/// 恢复工具的状态
	void ResetTools();
	
	///	恢复线宽
	void ResetWidth();

	/// 服务器关闭
	void ServerClosed();

	/// 被踢出共享屏幕
	void Kicked();

	/// 接收绘画数据
	void ReceiveDrawData( char *pReceivedData );

private:
	CInstantMessagingDlg	*m_pMainDlg;		/// 主对话框
	CImageList				m_imageList;		/// 头像图像列表
	CString					m_strServerIP;		/// 服务器IP
	CWhiteBoardClientSocket	
							*m_pWBCSocket;		/// 白板客户端socket
	
	TOOL					m_emTool;			/// 工具
	int						m_nWidth;			/// 线宽
	COLORREF				m_clDrawColor;		/// 颜色
	
public:
	/// 接收网络数据
	void OnReceive();

	/// 返回对应的服务器IP
	CString GetServerIP(){ return m_strServerIP; }

	/// 同意添加请求
	void AcceptAddRequest( const USER userServer );

	/// 将画图信息发送到服务器
	void SendDrawInfoToServer( const CPoint ptStart, const CPoint ptEnd );

// Dialog Data
	//{{AFX_DATA(CWhiteBoardClientDlg)
	enum { IDD = IDD_WHITEBOARD_CLIENT };
	CStatic	m_staticColor;
	CCanvasStatic	m_staticCanvas;
	CAdvButton	m_btnWidth4;
	CAdvButton	m_btnWidth3;
	CAdvButton	m_btnWidth2;
	CAdvButton	m_btnWidth1;
	CAdvButton	m_btnRectangleEmpty;
	CAdvButton	m_btnRectangle;
	CAdvButton	m_btnPencil;
	CAdvButton	m_btnLine;
	CAdvButton	m_btnEraser;
	CAdvButton	m_btnEllipseEmpty;
	CAdvButton	m_btnEllipse;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWhiteBoardClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWhiteBoardClientDlg)
	afx_msg void OnOk();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEraser();
	afx_msg void OnPencil();
	afx_msg void OnLine();
	afx_msg void OnRectangleEmpty();
	afx_msg void OnRectangle();
	afx_msg void OnEllipseEmpty();
	afx_msg void OnEllipse();
	afx_msg void OnColor();
	afx_msg void OnWidth1();
	afx_msg void OnWidth2();
	afx_msg void OnWidth3();
	afx_msg void OnWidth4();
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WHITEBOARDCLIENTDLG_H__2874C727_04E1_4EC2_91F9_6AC913C09F07__INCLUDED_)
