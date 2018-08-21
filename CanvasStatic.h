#if !defined(AFX_CANVASSTATIC_H__9C2685EC_A4D6_40E2_9974_E602AF4EE2D9__INCLUDED_)
#define AFX_CANVASSTATIC_H__9C2685EC_A4D6_40E2_9974_E602AF4EE2D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CanvasStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCanvasStatic window

class CCanvasStatic : public CStatic
{
// Construction
public:
	CCanvasStatic();

// Attributes
private:
	CDC						m_dcMem;			/// 画图的内存dc
	CBitmap					m_bitmap;			/// 画图的内存bitmap

	CDC						m_dcOld;			/// 保存原来的dc
	CBitmap					m_bitmapOld;		/// 保存原来的bitmap

	TOOL					m_emTool;			/// 工具
	int						m_nWidth;			/// 线宽
	COLORREF				m_clDrawColor;		/// 颜色

	HCURSOR					m_hCursor;			/// 鼠标指针

	CPoint					m_ptStart;			/// 开始点
	CPoint					m_ptEnd;			/// 结束点

	BOOL					m_bDrawing;			/// 是否在绘图中
	BOOL					m_bOwnerDraw;		/// 是否是自己绘图还是别人绘图

// Operations
public:
	void SetTool( TOOL emTool ){ m_emTool = emTool; SetCursorByTool(); }
	void SetWidth( int nWidth ){ m_nWidth = nWidth; SetCursorByTool(); }
	void SetColor( COLORREF cl ){ m_clDrawColor = cl; }

	/// 根据画图信息画图
	void Draw( DRAWINFO drawInfo );

	/// 画图
	void Draw();

	/// 清除画布
	void ClearCanvas();

private:
	/// 更新画布
	void UpdataCanvas();

	/// 设置鼠标指针
	void SetCursorByTool();

	/// 画线
	void DrawLine();

	/// 擦除
	void Erase();

	/// 画点
	void DrawPoint();

	/// 画空心矩形
	void DrawEmptyRectangle();

	/// 画矩形
	void DrawRectangle();

	/// 画空心椭圆
	void DrawEmptyEllipse();

	/// 画椭圆
	void DrawEllipse();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCanvasStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCanvasStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCanvasStatic)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnMouseLeave( WPARAM wParam, LPARAM lParam );
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CANVASSTATIC_H__9C2685EC_A4D6_40E2_9974_E602AF4EE2D9__INCLUDED_)
