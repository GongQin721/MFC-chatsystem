#if !defined(AFX_ADVBUTTON_H__11B0CEDF_7AC5_41BB_97C4_D3733B6CEEF9__INCLUDED_)
#define AFX_ADVBUTTON_H__11B0CEDF_7AC5_41BB_97C4_D3733B6CEEF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AdvButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAdvButton window

class CAdvButton : public CButton
{
// Construction
public:
	CAdvButton();

// Attributes
private:
	int				m_nState;			/// 按钮的状态
	CBitmap			m_bmpNormal;		/// 正常图标
	CBitmap			m_bmpHover;			/// 焦点图标
	CBitmap			m_bmpDown;			/// 按下图标
	CBitmap			m_bmpDisable;		/// 无效图标
	CToolTipCtrl	m_pToolTipCtrl;		/// 提示类

// Operations
private:
	/// 画正常状态
	void DrawNORMAL();

	/// 画焦点状态
	void DrawHOVER();

	/// 画按下状态
	void DrawDOWN();

	/// 画无效状态
	void DrawDISABLE();

	/// 删除图像
	void DeleteBmp();

public:
	/// 设置图像
	void setBmp( const UINT nIDNormal,
				 const UINT nIDHover,
				 const UINT nIDDown,
				 const UINT nIDDisable );

	/// 设置按钮为正常状态
	void SetNormal();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdvButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAdvButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CAdvButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave( WPARAM wParam, LPARAM lParam );
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADVBUTTON_H__11B0CEDF_7AC5_41BB_97C4_D3733B6CEEF9__INCLUDED_)
