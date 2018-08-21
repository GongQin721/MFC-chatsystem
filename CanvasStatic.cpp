
#include "stdafx.h"
#include "instantmessaging.h"
#include "CanvasStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "WhiteBoardServerDlg.h"
#include "WhiteBoardClientDlg.h"


static BOOL bTrackLeave = FALSE;

CCanvasStatic::CCanvasStatic()
{
	m_hCursor		= ::GetCursor();
	m_bDrawing		= FALSE;
	m_bOwnerDraw	= TRUE;
}

CCanvasStatic::~CCanvasStatic()
{
}


BEGIN_MESSAGE_MAP(CCanvasStatic, CStatic)
	//{{AFX_MSG_MAP(CCanvasStatic)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_MESSAGE( WM_MOUSELEAVE, OnMouseLeave )
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



void CCanvasStatic::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	/// 首次绘画，创建内存dc
	if( !m_dcMem.m_hDC )
	{
		m_dcMem.CreateCompatibleDC( &dc );
		m_bitmap.CreateCompatibleBitmap( &dc, 
			GetSystemMetrics( SM_CXSCREEN ), 
			GetSystemMetrics( SM_CYSCREEN ) );
		m_dcMem.SelectObject( m_bitmap );
		m_dcMem.FillSolidRect( 0, 0, GetSystemMetrics( SM_CXSCREEN ), GetSystemMetrics( SM_CYSCREEN ), 
			DEFAULT_WHITEBOARD_CANVAS_COLOR );
	}

	if( !m_dcOld.m_hDC )
	{
		m_dcOld.CreateCompatibleDC( &m_dcMem );
		m_bitmapOld.CreateCompatibleBitmap( &m_dcMem, 
			GetSystemMetrics( SM_CXSCREEN ), 
			GetSystemMetrics( SM_CYSCREEN ) );
		m_dcOld.SelectObject( m_bitmapOld );
		m_dcOld.FillSolidRect( 0, 0, GetSystemMetrics( SM_CXSCREEN ), GetSystemMetrics( SM_CYSCREEN ), 
			DEFAULT_WHITEBOARD_CANVAS_COLOR ); 
	}

	UpdataCanvas();
}

/// 更新画布
void CCanvasStatic::UpdataCanvas()
{
	CDC *pDC = GetDC();
	CRect rect;
	GetClientRect( &rect );
	CBrush br( RGB( 0, 0, 0 ) );
	pDC->FrameRect( rect, &br );
	rect.DeflateRect( 1, 1 );
	pDC->BitBlt( rect.left, rect.top, rect.Width(), rect.Height(),
		&m_dcMem,
		0, 0,
		SRCCOPY );
	ReleaseDC( pDC );
}

/// 设置鼠标指针
void CCanvasStatic::SetCursorByTool()
{
	DWORD nID;
	switch( m_emTool )
	{
	case PENCIL:
		nID = IDC_PENCIL;
		break;
	case ERASER:
		{
			switch( m_nWidth )
			{
			case WHITEBOARD_WIDTH_1:
				nID = IDC_ERASER_1;
				break;
			case WHITEBOARD_WIDTH_2:
				nID = IDC_ERASER_2;
				break;
			case WHITEBOARD_WIDTH_3:
				nID = IDC_ERASER_3;
				break;
			case WHITEBOARD_WIDTH_4:
				nID = IDC_ERASER_4;
				break;
			default:
				break;
			}
		}
		break;
	default:
		nID = IDC_CURSOR;
		break;
	}
	HCURSOR hCursor = ::LoadCursor( AfxGetResourceHandle(), MAKEINTRESOURCE( nID ) );
	::SetClassLong( GetSafeHwnd(), GCL_HCURSOR, ( LONG )hCursor );
}

void CCanvasStatic::OnMouseMove(UINT nFlags, CPoint point) 
{	
	if( !bTrackLeave )
	{
		SetCursorByTool();
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof( TRACKMOUSEEVENT );
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE;
		::_TrackMouseEvent( &tme );
		bTrackLeave = TRUE;
	}

	/// 如果在绘图中，则先清除原先图的，再画新的
	if( m_bDrawing )
	{
		m_bOwnerDraw = TRUE;
		m_ptEnd = point;
		Draw();
	}
	CStatic::OnMouseMove(nFlags, point);
}

void CCanvasStatic::OnMouseLeave( WPARAM wParam, LPARAM lParam )
{
	bTrackLeave = FALSE;
}

void CCanvasStatic::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_bOwnerDraw	= TRUE;
	m_ptStart		= point;
	m_ptEnd			= point;
	m_bDrawing		= TRUE;
	SetCapture();
	Draw();
	CStatic::OnLButtonDown(nFlags, point);
}

void CCanvasStatic::OnLButtonUp(UINT nFlags, CPoint point) 
{
	/// 如果不是在绘画中，则直接返回
	if( !m_bDrawing )
	{
		return;
	}
	m_bOwnerDraw	= TRUE;
	m_ptEnd			= point;
	m_bDrawing		= FALSE;
	::ReleaseCapture();
	Draw();
	CStatic::OnLButtonUp(nFlags, point);
}

/// 画图
void CCanvasStatic::Draw()
{
	/// 如果是自己画的图，则把画图信息传送给服务器对话框或其他客户端
	if( m_bOwnerDraw )
	{
		/// 如果是最终画的图或工具是画笔或画刷
		if( !m_bDrawing || PENCIL == m_emTool || ERASER == m_emTool )
		{
			if( GetParent()->IsKindOf( RUNTIME_CLASS( CWhiteBoardServerDlg ) ) )
			{
				( ( CWhiteBoardServerDlg * )GetParent() )->SendDrawInfoToAllUser( m_ptStart, m_ptEnd );
			}
			else if( GetParent()->IsKindOf( RUNTIME_CLASS( CWhiteBoardClientDlg ) ) )
			{
				( ( CWhiteBoardClientDlg * )GetParent() )->SendDrawInfoToServer( m_ptStart, m_ptEnd );
			}
		}
	}

	/// 如果在绘画中，则先恢复原来的图像
	if( m_bDrawing )
	{
		m_dcMem.BitBlt( 0, 0, GetSystemMetrics( SM_CXSCREEN ), GetSystemMetrics( SM_CYSCREEN ),
			&m_dcOld, 0, 0, SRCCOPY );
	}
	switch( m_emTool )
	{
	case ERASER:
		Erase();
		break;
	case PENCIL:
		DrawPoint();
		break;
	case LINE:
		DrawLine();
		break;
	case RECTANGLE_EMPTY:
		DrawEmptyRectangle();
		break;
	case RECTANGLE:
		DrawRectangle();
		break;
	case ELLIPSE_EMPTY:
		DrawEmptyEllipse();
		break;
	case ELLIPSE:
		DrawEllipse();
		break;
	default:
		break;
	}

	/// 画完之后更新画布
	UpdataCanvas();

	/// 如果是最终画的图或别人画的图，则保存到原来的dc上
	if( !m_bOwnerDraw || !m_bDrawing || ERASER == m_emTool || PENCIL == m_emTool )
	{
		m_dcOld.BitBlt( 0, 0, GetSystemMetrics( SM_CXSCREEN ), GetSystemMetrics( SM_CYSCREEN ),
			&m_dcMem, 0, 0, SRCCOPY );
	}
}

/// 画线
void CCanvasStatic::DrawLine()
{
	CPen pen;
	pen.CreatePen( PS_SOLID, m_nWidth, m_clDrawColor );
	CPen *pOldPen = m_dcMem.SelectObject( &pen );
	m_dcMem.MoveTo( m_ptStart );
	m_dcMem.LineTo( m_ptEnd );
	pOldPen->DeleteObject();
}

/// 擦除
void CCanvasStatic::Erase()
{
	CPen pen;
	pen.CreatePen( PS_SOLID, m_nWidth, DEFAULT_WHITEBOARD_CANVAS_COLOR );
	CPen *pOldPen = m_dcMem.SelectObject( &pen );
	m_dcMem.MoveTo( m_ptStart );
	m_dcMem.LineTo( m_ptEnd );
	m_ptStart = m_ptEnd;
	pOldPen->DeleteObject();
}

/// 画点
void CCanvasStatic::DrawPoint()
{
	CPen pen;
	pen.CreatePen( PS_SOLID, m_nWidth, m_clDrawColor );
	CPen *pOldPen = m_dcMem.SelectObject( &pen );
	m_dcMem.MoveTo( m_ptStart );
	m_dcMem.LineTo( m_ptEnd );
	m_ptStart = m_ptEnd;
	pOldPen->DeleteObject();
}

/// 画空心矩形
void CCanvasStatic::DrawEmptyRectangle()
{
	CPen pen;
	pen.CreatePen( PS_SOLID, m_nWidth, m_clDrawColor );
	CPen *pOldPen = m_dcMem.SelectObject( &pen );
	CBrush *pBr =CBrush::FromHandle( ( HBRUSH )GetStockObject( NULL_BRUSH ) );
	CBrush *pOldBr = m_dcMem.SelectObject( pBr );
	CRect rect( m_ptStart, m_ptEnd );
	m_dcMem.Rectangle( rect );
	pOldPen->DeleteObject();
	pOldBr->DeleteObject();
}

/// 画矩形
void CCanvasStatic::DrawRectangle()
{
	CPen pen;
	pen.CreatePen( PS_SOLID, m_nWidth, m_clDrawColor );
	CPen *pOldPen = m_dcMem.SelectObject( &pen );
	CBrush br( m_clDrawColor );
	CBrush *pOldBr = m_dcMem.SelectObject( &br );
	CRect rect( m_ptStart, m_ptEnd );
	m_dcMem.Rectangle( rect );
	pOldPen->DeleteObject();
	pOldBr->DeleteObject();
}

/// 画空心椭圆
void CCanvasStatic::DrawEmptyEllipse()
{
	CPen pen;
	pen.CreatePen( PS_SOLID, m_nWidth, m_clDrawColor );
	CPen *pOldPen = m_dcMem.SelectObject( &pen );
	CBrush *pBr =CBrush::FromHandle( ( HBRUSH )GetStockObject( NULL_BRUSH ) );
	CBrush *pOldBr = m_dcMem.SelectObject( pBr );
	CRect rect( m_ptStart, m_ptEnd );
	m_dcMem.Ellipse( rect );
	pOldPen->DeleteObject();
	pOldBr->DeleteObject();
}

/// 画椭圆
void CCanvasStatic::DrawEllipse()
{
	CPen pen;
	pen.CreatePen( PS_SOLID, m_nWidth, m_clDrawColor );
	CPen *pOldPen = m_dcMem.SelectObject( &pen );
	CBrush br( m_clDrawColor );
	CBrush *pOldBr = m_dcMem.SelectObject( &br );
	CRect rect( m_ptStart, m_ptEnd );
	m_dcMem.Ellipse( rect );
	pOldPen->DeleteObject();
	pOldBr->DeleteObject();
}

/// 根据画图信息画图
void CCanvasStatic::Draw( DRAWINFO drawInfo )
{
	/// 不是自己绘图
	m_bOwnerDraw	= FALSE;

	/// 如果在绘画中，则先恢复原来的图像
	if( m_bDrawing )
	{
		m_dcMem.BitBlt( 0, 0, GetSystemMetrics( SM_CXSCREEN ), GetSystemMetrics( SM_CYSCREEN ),
			&m_dcOld, 0, 0, SRCCOPY );
	}

	CPen pen;
	pen.CreatePen( PS_SOLID, drawInfo.nWidth, drawInfo.color );
	CPen *pOldPen = m_dcMem.SelectObject( &pen );
	CBrush br( drawInfo.color );
	CBrush *pOldBr = m_dcMem.SelectObject( &br );

	switch( drawInfo.tool )
	{
	case ERASER:
		pOldPen->DeleteObject();
		{
			pen.DeleteObject();
			pen.CreatePen( PS_SOLID, drawInfo.nWidth, DEFAULT_WHITEBOARD_CANVAS_COLOR );
			pOldPen = m_dcMem.SelectObject( &pen );
			m_dcMem.MoveTo( drawInfo.ptStart );
			m_dcMem.LineTo( drawInfo.ptEnd );
		}
		break;
	case PENCIL:
		m_dcMem.MoveTo( drawInfo.ptStart );
		m_dcMem.LineTo( drawInfo.ptEnd );
		break;
	case LINE:
		m_dcMem.MoveTo( drawInfo.ptStart );
		m_dcMem.LineTo( drawInfo.ptEnd );
		break;
	case RECTANGLE_EMPTY:
		pOldBr->DeleteObject();
		{
			CBrush *pBr = CBrush::FromHandle( ( HBRUSH )GetStockObject( NULL_BRUSH ) );
			pOldBr = m_dcMem.SelectObject( pBr );
			CRect rect( drawInfo.ptStart, drawInfo.ptEnd );
			m_dcMem.Rectangle( rect );
		}
		break;
	case RECTANGLE:
		{
			CRect rect( drawInfo.ptStart, drawInfo.ptEnd );
			m_dcMem.Rectangle( rect );
		}
		break;
	case ELLIPSE_EMPTY:
		pOldBr->DeleteObject();
		{
			CBrush *pBr = CBrush::FromHandle( ( HBRUSH )GetStockObject( NULL_BRUSH ) );
			pOldBr = m_dcMem.SelectObject( pBr );
			CRect rect( drawInfo.ptStart, drawInfo.ptEnd );
			m_dcMem.Ellipse( rect );
		}
		break;
	case ELLIPSE:
		{
			CRect rect( drawInfo.ptStart, drawInfo.ptEnd );
			m_dcMem.Ellipse( rect );
		}
		break;
	default:
		break;
	}

	pOldPen->DeleteObject();
	pOldBr->DeleteObject();

	m_dcOld.BitBlt( 0, 0, GetSystemMetrics( SM_CXSCREEN ), GetSystemMetrics( SM_CYSCREEN ),
		&m_dcMem, 0, 0, SRCCOPY );
	
	if( m_bDrawing )
	{
		switch( m_emTool )
		{
		case ERASER:
			Erase();
			break;
		case PENCIL:
			DrawPoint();
			break;
		case LINE:
			DrawLine();
			break;
		case RECTANGLE_EMPTY:
			DrawEmptyRectangle();
			break;
		case RECTANGLE:
			DrawRectangle();
			break;
		case ELLIPSE_EMPTY:
			DrawEmptyEllipse();
			break;
		case ELLIPSE:
			DrawEllipse();
			break;
		default:
			break;
		}
		
		if( ERASER == m_emTool || PENCIL == m_emTool )
		{
			m_dcOld.BitBlt( 0, 0, GetSystemMetrics( SM_CXSCREEN ), GetSystemMetrics( SM_CYSCREEN ),
				&m_dcMem, 0, 0, SRCCOPY );
		}
	}
	
	/// 画完之后更新画布
	UpdataCanvas();
}

/// 清除画布
void CCanvasStatic::ClearCanvas()
{
	m_bitmap.DeleteObject();
	m_dcMem.DeleteDC();
	m_bitmapOld.DeleteObject();
	m_dcOld.DeleteDC();
}
