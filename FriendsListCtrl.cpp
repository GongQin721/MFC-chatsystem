
#include "stdafx.h"
#include "instantmessaging.h"
#include "FriendsListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "InstantMessagingDlg.h"

static BOOL bTrackLeave = FALSE;

CFriendsListCtrl::CFriendsListCtrl()
{
	m_nCamera	= -1;
	m_nDelIcon	= -1;
	m_nCurSel	= -1;
	m_imageList.Create( 32, 32, ILC_MASK | ILC_COLOR24, 0, 0 );
	CBitmap bitmap;
	for( int nIndex = 0; nIndex < MAXFACES; nIndex++ )
	{
		bitmap.LoadBitmap( IDB_BITMAP1 + nIndex );
		m_imageList.Add( &bitmap, FACEBGCOLOR );
		bitmap.DeleteObject();
	}
}

CFriendsListCtrl::~CFriendsListCtrl()
{
	m_imageList.DeleteImageList();
}


BEGIN_MESSAGE_MAP(CFriendsListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CFriendsListCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE( WM_MOUSELEAVE, OnMouseLeave )
	ON_WM_ERASEBKGND()
	ON_WM_MEASUREITEM_REFLECT()
	ON_COMMAND(IDM_DELETEUSER, OnDeleteuser)
	ON_COMMAND(IDM_SENDMESSAGE, OnSendmessage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFriendsListCtrl message handlers

void CFriendsListCtrl::PreSubclassWindow() 
{
	/// 设置列表框的风格
	ModifyStyle( 0, LVS_OWNERDRAWFIXED );

	/// 设置用户列表的高度
	CRect rect;
	GetWindowRect( &rect );
	WINDOWPOS wp;
	wp.hwnd		= m_hWnd;
	wp.cx		= rect.Width();
	wp.cy		= rect.Height();
	wp.flags	= SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;
	SendMessage( WM_WINDOWPOSCHANGED, 0, ( LPARAM )&wp );

	CListCtrl::PreSubclassWindow();
}

void CFriendsListCtrl::MeasureItem( LPMEASUREITEMSTRUCT lpMeasureItemStruct )
{	
	lpMeasureItemStruct->itemHeight = DEFAULT_FRIENDSLIST_HEIGHT;
}


void CFriendsListCtrl::DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct ) 
{
	/// 得到项的附加数据
	USER *pUser;
	pUser = ( USER * )lpDrawItemStruct->itemData;

	
	int nItem=lpDrawItemStruct->itemID;
	CRect rect = lpDrawItemStruct->rcItem;
	CRect rectTemp1( rect );

	/// 得到CDC并保存　
	CDC* pDC=CDC::FromHandle(lpDrawItemStruct->hDC);

	CDC dcMem;
	dcMem.CreateCompatibleDC( pDC );
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap( pDC, rect.Width(),  DEFAULT_FRIENDSLIST_HEIGHT);
	dcMem.SelectObject( &bitmap );
	CFont font;
	font.CreatePointFont( DEFAULT_FRIENDSLIST_FONT, "宋体" );
	dcMem.SelectObject( &font );

	rect.top = 0;
	rect.bottom = DEFAULT_FRIENDSLIST_HEIGHT;

	LVITEM item;
	item.iItem = nItem;
	item.iSubItem = 0;
	item.mask = LVIF_IMAGE|LVIF_STATE;
	item.stateMask = 0XFFFF;
	GetItem(&item);

	if( item.state & LVIS_SELECTED )
	{
		CBrush br( DEFAULT_FRIENDSLIST_SELCOLOR );
		dcMem.FillRect( rect, &br );
		m_nCurSel = nItem;
	}
	else if( item.state & LVIS_FOCUSED )
	{
		CBrush br( DEFAULT_FRIENDSLIST_HOVERCOLOR );
		dcMem.FillRect( rect, &br );
	}
	else
	{
		CBrush br( DEFAULT_FRIENDSLIST_NORMALCOLOR );
		dcMem.FillRect( rect, &br );
	}
	
	CPoint pt;
	pt.x = rect.left + 5;
	pt.y = rect.top + 5;
	m_imageList.Draw( &dcMem, pUser->nFace, pt, ILD_TRANSPARENT );
	
	dcMem.SetBkMode( TRANSPARENT );
	dcMem.SetTextColor( DEFALUT_FRIENDSLIST_NAMECOLOR );
	CRect rectTemp;
	rectTemp.left = rect.left + 5 + 32 + 5;
  	rectTemp.top = rect.top + 5;
	rectTemp.right = rect.right;
	rectTemp.bottom = rectTemp.top + ( rect.Height() - 5 * 2 ) / 2;
	dcMem.DrawText( pUser->strName, rectTemp, DT_VCENTER | DT_SINGLELINE | DT_LEFT | DT_END_ELLIPSIS );

	dcMem.SetTextColor( DEFALUT_FRIENDSLIST_IPCOLOR );
	rectTemp.right -= 16 + 5 + 5 + 16;
	rectTemp.top = rectTemp.bottom;
	rectTemp.bottom = rectTemp.top + ( rect.Height() - 5 * 2 ) / 2;
	dcMem.DrawText( pUser->strIP, rectTemp, DT_VCENTER | DT_SINGLELINE | DT_LEFT | DT_END_ELLIPSIS );

	/// 画删除按钮
	CBitmap bitmap1;
	bitmap1.LoadBitmap( IDB_DELETE );
	CDC dcMem1;
	dcMem1.CreateCompatibleDC( pDC );
	dcMem1.SelectObject( &bitmap1 );

	rectTemp.left = rectTemp.right;
	rectTemp.right = rectTemp.left + 16;
	
	TransparentBlt( dcMem.m_hDC, 
		rectTemp.left, rectTemp.top, 16, 16,
		dcMem1.m_hDC, 
		0, 0, 16, 16,
		FACEBGCOLOR );

	dcMem1.DeleteDC();
	
	if( nItem == m_nDelIcon )
	{
		CBrush br( RGB( 128, 128, 128 ) );
		dcMem.FrameRect( rectTemp, &br );
	}

	if( pUser->bHasCamera )
	{
		rectTemp.left = rectTemp.right + 5;
		rectTemp.right = rect.right - 5;
		
		CBitmap bitmap1;
		bitmap1.LoadBitmap( IDB_CAMERA );
		CDC dcMem1;
		dcMem1.CreateCompatibleDC( pDC );
		dcMem1.SelectObject( &bitmap1 );
		
		TransparentBlt( dcMem.m_hDC, 
			rectTemp.left, rectTemp.top, 16, 16,
			dcMem1.m_hDC, 
			0, 0, 16, 16,
			FACEBGCOLOR );

		if( nItem == m_nCamera )
		{
			CBrush br( RGB( 128, 128, 128 ) );
			dcMem.FrameRect( rectTemp, &br );
		}
		
		dcMem1.DeleteDC();
	}

	pDC->BitBlt( 0, rectTemp1.top, rectTemp1.Width(), rectTemp1.Height(),
		&dcMem,
		0, 0,
		SRCCOPY );

	dcMem.DeleteDC();
}

/// 单击左键
void CFriendsListCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if( -1 != m_nDelIcon )
	{
		m_pMainDlg->DeleteFriend( m_nDelIcon );
		m_nDelIcon	= -1;
	}
	CListCtrl::OnLButtonDown(nFlags, point);
}

/// 双击鼠标
void CFriendsListCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	int nIndex = this->HitTest( point );
	if( -1 == nIndex )
	{
		return ;
	}
	m_pMainDlg->OnChat( nIndex );
	CListCtrl::OnLButtonDblClk(nFlags, point);
}

/// 单击右键时弹出菜单
void CFriendsListCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CListCtrl::OnRButtonDown(nFlags, point);
	
	int nIndex = this->HitTest( point );
	if( -1 == nIndex )
	{
		return ;
	}
	
	CMenu menu;
	menu.LoadMenu( IDR_MENU2 );
	CMenu *pSubMenu;
	pSubMenu = menu.GetSubMenu( 0 );
	ClientToScreen( &point );
	SetForegroundWindow();
	USER *pUser;
	pUser = ( USER * )this->GetItemData( nIndex );
	if( !pUser->bHasCamera )
	{
		pSubMenu->RemoveMenu( IDM_VIDEOCHAT, MF_BYCOMMAND );
	}
	pSubMenu->TrackPopupMenu( 0, point.x, point.y, this );
}

/// 鼠标滑过时改变
void CFriendsListCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	CListCtrl::OnMouseMove(nFlags, point);

	if( !bTrackLeave )
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof( TRACKMOUSEEVENT );
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE;
		::_TrackMouseEvent( &tme );
		bTrackLeave = TRUE;
	}
	int nIndex = this->HitTest( point );
	if( -1 == nIndex )
	{
		return ;
	}

	CRect rect;
	this->GetItemRect( nIndex, &rect, LVIR_BOUNDS );
	rect.right	= rect.right - 5;
	rect.left	= rect.right - 16;
	rect.bottom = rect.bottom - 5;
	rect.top	= rect.bottom - 16;

	CRect rectDel( rect );
	rectDel.right	= rect.left - 5;
	rectDel.left	= rectDel.right - 16;

	USER *pUser;
	pUser = ( USER * )this->GetItemData( nIndex );

	/// 判断删除按钮是否有焦点
	if( m_nDelIcon != nIndex && rectDel.PtInRect( point ) )
	{
		m_nDelIcon	= nIndex;
		SetItemState( nIndex, ~LVIS_FOCUSED, LVIS_FOCUSED );
	}
	else if( -1 != m_nDelIcon && !rectDel.PtInRect( point ) )
	{
		m_nDelIcon = -1;
		SetItemState( nIndex, ~LVIS_FOCUSED, LVIS_FOCUSED );
	}
	SetItemState( nIndex, LVIS_FOCUSED, LVIS_FOCUSED );
}

void CFriendsListCtrl::OnMouseLeave( WPARAM wParam, LPARAM lParam )
{
	bTrackLeave = FALSE;
	int nIndex = this->GetNextItem( -1, LVNI_FOCUSED );
	if( -1 == nIndex )
	{
		return ;
	}

	m_nCamera	= -1;
	m_nDelIcon	= -1;
	SetItemState( nIndex, ~LVIS_FOCUSED, LVIS_FOCUSED );
}

/// 向列表中添加用户
int CFriendsListCtrl::AddUser( const USER user )
{
	int nReturn = -1;

	/// 为用户列表添加新的附加数据
	USER *pUser			= new USER();
	pUser->nFace		= user.nFace;
	memcpy( pUser->strIP, user.strIP, 16 );
	memcpy( pUser->strName, user.strName, MAXNICKNAMELENGTH + 1 );
	pUser->bHasCamera	= user.bHasCamera;

	nReturn = InsertItem( LVIF_PARAM,
		this->GetItemCount(),
		"",
		0,
		0,
		0,
		( LPARAM )pUser );

	/// 插入后调整第0列的宽度
	this->SetColumnWidth( 0, LVSCW_AUTOSIZE_USEHEADER );

	return nReturn;
}

/// 删除指定用户
void CFriendsListCtrl::DeleteUser( int nIndex )
{
	int nCount = GetItemCount();

	/// nIndex合法性的判断
	if( nIndex < 0 || nIndex >= nCount )
	{
		return;
	}

	/// 删除分配的附加数据空间
	USER *pUser = ( USER * )GetItemData( nIndex );
	delete pUser;
	DeleteItem( nIndex );

	/// 删除后调整第0列的宽度
	this->SetColumnWidth( 0, LVSCW_AUTOSIZE_USEHEADER );
}

BOOL CFriendsListCtrl::OnEraseBkgnd( CDC* pDC ) 
{
	return CListCtrl::OnEraseBkgnd( pDC );
}

void CFriendsListCtrl::SetMainDlg( CInstantMessagingDlg *pMainDlg )
{
	m_pMainDlg = pMainDlg;
}

void CFriendsListCtrl::OnDeleteuser() 
{
	if( -1 == m_nCurSel )
	{
		return ;
	}
	m_pMainDlg->DeleteFriend( m_nCurSel );
}

void CFriendsListCtrl::OnSendmessage() 
{
	if( -1 == m_nCurSel )
	{
		return ;
	}
	m_pMainDlg->OnChat( m_nCurSel );
}

void CFriendsListCtrl::DeleteAllUsers()
{
	for( int nIndex = 0; nIndex < GetItemCount(); nIndex++ )
	{
		/// 删除分配的附加数据空间
		USER *pUser = ( USER * )GetItemData( nIndex );
		delete pUser;
	}
}