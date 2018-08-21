// AdvButton.cpp : implementation file
//

#include "stdafx.h"
#include "instantmessaging.h"
#include "AdvButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define NORMAL				1						/// 处于正常状态
#define HOVER				2						/// 处于焦点状态
#define DOWN				3						/// 处于按下状态
#define DISABLE				4						/// 处于无效状态

#define TRANSPARENTCOLOR	RGB( 255, 0, 255 )		/// 定义透明位图的RGB值

#pragma comment( lib, "C:\\Program Files\\Microsoft Visual Studio\\VC98\\Lib\\MSIMG32.LIB" )

/////////////////////////////////////////////////////////////////////////////
// CAdvButton

static BOOL bTrackLeave = FALSE;

CAdvButton::CAdvButton()
{
	m_nState = NORMAL;
}

CAdvButton::~CAdvButton()
{
	DeleteBmp();
}


BEGIN_MESSAGE_MAP(CAdvButton, CButton)
	//{{AFX_MSG_MAP(CAdvButton)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_MESSAGE( WM_MOUSELEAVE, OnMouseLeave )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdvButton message handlers

void CAdvButton::PreSubclassWindow() 
{
	ModifyStyle( 0, BS_OWNERDRAW );
	CButton::PreSubclassWindow();

	m_pToolTipCtrl.Create( this, TTS_ALWAYSTIP );
	m_pToolTipCtrl.SetDelayTime( 100 );
	CString strText;
	GetWindowText( strText );
	m_pToolTipCtrl.AddTool( this, strText ); 
}

void CAdvButton::OnMouseMove(UINT nFlags, CPoint point) 
{	
	if( !bTrackLeave )
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof( TRACKMOUSEEVENT );
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE;
		::_TrackMouseEvent( &tme );
		bTrackLeave = TRUE;
		m_nState = HOVER;
		Invalidate();
	}	
	CButton::OnMouseMove(nFlags, point);
}

void CAdvButton::OnMouseLeave( WPARAM wParam, LPARAM lParam )
{
	bTrackLeave = FALSE;
	m_nState = NORMAL;
	Invalidate();
}

void CAdvButton::OnLButtonDown(UINT nFlags, CPoint point) 
{	
	m_nState = DOWN;
	Invalidate();
	CButton::OnLButtonDown(nFlags, point);
}

void CAdvButton::OnLButtonUp(UINT nFlags, CPoint point) 
{	
	m_nState = HOVER;
	Invalidate();
	CButton::OnLButtonUp(nFlags, point);
}

void CAdvButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	if( lpDrawItemStruct->itemState & ODS_DISABLED )
	{
		m_nState = DISABLE;
	}

	switch( m_nState )
	{
	case NORMAL:
		DrawNORMAL();
		break;
	case HOVER:
		DrawHOVER();
		break;
	case DOWN:
		DrawDOWN();
		break;
	case DISABLE:
		DrawDISABLE();
		break;
	default:
		break;
	}
}

void CAdvButton::DrawNORMAL()
{
	CDC *pDC = GetDC();
	BITMAP bmp;
	if( !m_bmpNormal.m_hObject )
	{
		return;
	}
	m_bmpNormal.GetBitmap( &bmp );
	SetWindowPos( NULL, 0, 0, bmp.bmWidth, bmp.bmHeight, SWP_NOMOVE | SWP_NOZORDER);
	CDC dcMem;
	dcMem.CreateCompatibleDC( pDC );
	CBitmap *pOldBmp;
	pOldBmp = dcMem.SelectObject( &m_bmpNormal );
	pOldBmp->DeleteObject();

	TransparentBlt( pDC->m_hDC, 0, 0, bmp.bmWidth, bmp.bmHeight, 
		dcMem.m_hDC, 0, 0, bmp.bmWidth, bmp.bmHeight, TRANSPARENTCOLOR );
	dcMem.DeleteDC();
}

void CAdvButton::DrawHOVER()
{
	CDC *pDC = GetDC();
	BITMAP bmp;
	if( !m_bmpHover.m_hObject )
	{
		return;
	}
	m_bmpHover.GetBitmap( &bmp );
	SetWindowPos( NULL, 0, 0, bmp.bmWidth, bmp.bmHeight, SWP_NOMOVE | SWP_NOZORDER);
	CDC dcMem;
	dcMem.CreateCompatibleDC( pDC );
	CBitmap *pOldBmp;
	pOldBmp = dcMem.SelectObject( &m_bmpHover );
	pOldBmp->DeleteObject();

	TransparentBlt( pDC->m_hDC, 0, 0, bmp.bmWidth, bmp.bmHeight, 
		dcMem.m_hDC, 0, 0, bmp.bmWidth, bmp.bmHeight, TRANSPARENTCOLOR );
	dcMem.DeleteDC();
}

void CAdvButton::DrawDOWN()
{
	CDC *pDC = GetDC();
	BITMAP bmp;
	if( !m_bmpDown.m_hObject )
	{
		return;
	}
	m_bmpDown.GetBitmap( &bmp );
	SetWindowPos( NULL, 0, 0, bmp.bmWidth, bmp.bmHeight, SWP_NOMOVE | SWP_NOZORDER);
	CDC dcMem;
	dcMem.CreateCompatibleDC( pDC );
	CBitmap *pOldBmp;
	pOldBmp = dcMem.SelectObject( &m_bmpDown );
	pOldBmp->DeleteObject();

	TransparentBlt( pDC->m_hDC, 0, 0, bmp.bmWidth, bmp.bmHeight, 
		dcMem.m_hDC, 0, 0, bmp.bmWidth, bmp.bmHeight, TRANSPARENTCOLOR );
	dcMem.DeleteDC();
}

void CAdvButton::DrawDISABLE()
{
	CDC *pDC = GetDC();
	BITMAP bmp;
	if( !m_bmpDisable.m_hObject )
	{
		return;
	}
	m_bmpDisable.GetBitmap( &bmp );
	SetWindowPos( NULL, 0, 0, bmp.bmWidth, bmp.bmHeight, SWP_NOMOVE | SWP_NOZORDER);
	CDC dcMem;
	dcMem.CreateCompatibleDC( pDC );
	CBitmap *pOldBmp;
	pOldBmp = dcMem.SelectObject( &m_bmpDisable );
	pOldBmp->DeleteObject();

	TransparentBlt( pDC->m_hDC, 0, 0, bmp.bmWidth, bmp.bmHeight, 
		dcMem.m_hDC, 0, 0, bmp.bmWidth, bmp.bmHeight, TRANSPARENTCOLOR );
	dcMem.DeleteDC();
}

void CAdvButton::setBmp( const UINT nIDNormal,
						 const UINT nIDHover,
						 const UINT nIDDown,
						 const UINT nIDDisable )
{
	DeleteBmp();
	if( nIDNormal )
	{
		m_bmpNormal.LoadBitmap( nIDNormal );
	}
	if( nIDHover )
	{
		m_bmpHover.LoadBitmap( nIDHover );
	}
	if( nIDDown )
	{
		m_bmpDown.LoadBitmap( nIDDown );
	}
	if( nIDDisable )
	{
		m_bmpDisable.LoadBitmap( nIDDisable );
	}
}


void CAdvButton::DeleteBmp()
{
	if( m_bmpNormal.m_hObject )
	{
		m_bmpNormal.DeleteObject();
	}
	if( m_bmpHover.m_hObject )
	{
		m_bmpHover.DeleteObject();
	}
	if( m_bmpDown.m_hObject )
	{
		m_bmpDown.DeleteObject();
	}
	if( m_bmpDisable.m_hObject )
	{
		m_bmpDisable.DeleteObject();
	}
}

BOOL CAdvButton::PreTranslateMessage(MSG* pMsg) 
{
	if(	pMsg->message == WM_LBUTTONDOWN ||
		pMsg->message == WM_LBUTTONUP ||
		pMsg->message == WM_MOUSEMOVE )
	{
		m_pToolTipCtrl.RelayEvent( pMsg );
	}		
	return CButton::PreTranslateMessage(pMsg);
}

void CAdvButton::SetNormal()
{
	EnableWindow( TRUE );
	m_nState = NORMAL;
	Invalidate();
}