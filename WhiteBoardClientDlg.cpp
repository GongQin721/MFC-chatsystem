#include "stdafx.h"
#include "instantmessaging.h"
#include "WhiteBoardClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "InstantMessagingDlg.h"
#include "WhiteBoardClientSocket.h"

IMPLEMENT_DYNAMIC( CWhiteBoardClientDlg, CDialog )

CWhiteBoardClientDlg::CWhiteBoardClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWhiteBoardClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWhiteBoardClientDlg)
	//}}AFX_DATA_INIT
	
	m_imageList.Create( 16, 16, ILC_MASK | ILC_COLOR24, 0, 0 );
	CBitmap bitmap32;
	CBitmap bitmap16;
	HBITMAP hBitmap;
	for( int nIndex = 0; nIndex < MAXFACES; nIndex++ )
	{
		bitmap32.LoadBitmap( IDB_BITMAP1 + nIndex );
		hBitmap = ( HBITMAP )::CopyImage( ( HBITMAP )bitmap32, IMAGE_BITMAP, 16, 16, LR_COPYDELETEORG );
		bitmap16.Attach( hBitmap );
		m_imageList.Add( &bitmap16, FACEBGCOLOR );
		bitmap16.DeleteObject();
		bitmap32.DeleteObject();
		::DeleteObject( hBitmap );
	}
	m_emTool		= PENCIL;     //画笔
	m_nWidth		= WHITEBOARD_WIDTH_1;//线宽
	m_clDrawColor	= DEFAULT_WHITEBOARD_TOOL_COLOR;//颜色
}


void CWhiteBoardClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWhiteBoardClientDlg)
	DDX_Control(pDX, IDS_COLOR, m_staticColor);
	DDX_Control(pDX, IDS_CANVAS, m_staticCanvas);
	DDX_Control(pDX, IDB_WIDTH_4, m_btnWidth4);
	DDX_Control(pDX, IDB_WIDTH_3, m_btnWidth3);
	DDX_Control(pDX, IDB_WIDTH_2, m_btnWidth2);
	DDX_Control(pDX, IDB_WIDTH_1, m_btnWidth1);
	DDX_Control(pDX, IDB_RECTANGLE_EMPTY, m_btnRectangleEmpty);
	DDX_Control(pDX, IDB_RECTANGLE, m_btnRectangle);
	DDX_Control(pDX, IDB_PENCIL, m_btnPencil);
	DDX_Control(pDX, IDB_LINE, m_btnLine);
	DDX_Control(pDX, IDB_ERASER, m_btnEraser);
	DDX_Control(pDX, IDB_ELLIPSE_EMPTY, m_btnEllipseEmpty);
	DDX_Control(pDX, IDB_ELLIPSE, m_btnEllipse);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWhiteBoardClientDlg, CDialog)
	//{{AFX_MSG_MAP(CWhiteBoardClientDlg)
	ON_BN_CLICKED(IDOK, OnOk)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDB_ERASER, OnEraser)
	ON_BN_CLICKED(IDB_PENCIL, OnPencil)
	ON_BN_CLICKED(IDB_LINE, OnLine)
	ON_BN_CLICKED(IDB_RECTANGLE_EMPTY, OnRectangleEmpty)
	ON_BN_CLICKED(IDB_RECTANGLE, OnRectangle)
	ON_BN_CLICKED(IDB_ELLIPSE_EMPTY, OnEllipseEmpty)
	ON_BN_CLICKED(IDB_ELLIPSE, OnEllipse)
	ON_BN_CLICKED(IDS_COLOR, OnColor)
	ON_BN_CLICKED(IDB_WIDTH_1, OnWidth1)
	ON_BN_CLICKED(IDB_WIDTH_2, OnWidth2)
	ON_BN_CLICKED(IDB_WIDTH_3, OnWidth3)
	ON_BN_CLICKED(IDB_WIDTH_4, OnWidth4)
	ON_WM_SIZING()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



void CWhiteBoardClientDlg::OnOk() 
{	
}

void CWhiteBoardClientDlg::OnCancel() 
{
	if( IDOK == MessageBox( "你要抛弃画板了吗？", "不要你了", MB_OKCANCEL | MB_ICONINFORMATION | MB_DEFBUTTON2 ) )
	{	
		USER userSelf;
		userSelf.nFace		= m_pMainDlg->GetFace();
		memcpy( userSelf.strName, m_pMainDlg->GetNickName().GetBuffer( MAXNICKNAMELENGTH + 1 ), MAXNICKNAMELENGTH + 1 );
		
		SendUserCommandToIP( WHITEBOARD_CLIENT_COLSED, m_strServerIP, WHITEBOARD_SERVER_PORT, &userSelf );

	
		m_pWBCSocket->Close();
		delete [] m_pWBCSocket;
		m_pWBCSocket = NULL;

		ResetTools();
		ResetWidth();
		m_emTool		= PENCIL;
		m_nWidth		= WHITEBOARD_WIDTH_1;
		m_clDrawColor	= DEFAULT_WHITEBOARD_TOOL_COLOR;

		m_staticCanvas.ClearCanvas();
		DestroyWindow();
	}
}

BOOL CWhiteBoardClientDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	/// 初始化
	Init();
	
	return TRUE;  
	             
}


/// 添加服务器和自己到用户列表框
void CWhiteBoardClientDlg::AcceptAddRequest(  const USER userServer )
{
	/// 设置服务器IP
	m_strServerIP = userServer.strIP;

	/// 自己的USER
	USER userSelf;
	userSelf.bHasCamera	= m_pMainDlg->HasCamera();
	userSelf.nFace		= m_pMainDlg->GetFace();
	memcpy( userSelf.strName, m_pMainDlg->GetNickName().GetBuffer( MAXNICKNAMELENGTH + 1 ), MAXNICKNAMELENGTH + 1 );

	/// 接受请求加入白板
	SendUserCommandToIP( WHITEBOARD_ADDREQUEST_ALLOW, m_strServerIP, WHITEBOARD_SERVER_PORT, &userSelf );
}

/// 被踢出白板
void CWhiteBoardClientDlg::Kicked()
{
	/// 关闭UDP套接字
	m_pWBCSocket->Close();

	/// 提示
	MessageBox( "你被踢出来了白板！", "白板" );

	/// 清除画布
	m_staticCanvas.ClearCanvas();
	
	/// 设置默认
	ResetTools();
	ResetWidth();
	m_emTool		= PENCIL;
	m_nWidth		= WHITEBOARD_WIDTH_1;
	m_clDrawColor	= DEFAULT_WHITEBOARD_TOOL_COLOR;

	/// 关闭对话框
	DestroyWindow();
}

/// 服务器关闭
void CWhiteBoardClientDlg::ServerClosed()
{
	/// 关闭UDP套接字
	m_pWBCSocket->Close();

	/// 提示
	MessageBox( "关闭了白板！", "白板" );

	/// 清除画布
	m_staticCanvas.ClearCanvas();
	
	/// 设置默认
	ResetTools();
	ResetWidth();
	m_emTool		= PENCIL;
	m_nWidth		= WHITEBOARD_WIDTH_1;
	m_clDrawColor	= DEFAULT_WHITEBOARD_TOOL_COLOR;
	
	/// 关闭对话框
	DestroyWindow();
}

/// 接收屏幕数据
void CWhiteBoardClientDlg::ReceiveDrawData( char *pReceivedData )
{
	DRAWINFO drawInfo;
	memcpy( &drawInfo, pReceivedData + sizeof( DATAPACKET ), sizeof( DRAWINFO ) );
	m_staticCanvas.Draw( drawInfo );
}

void CWhiteBoardClientDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CDC *pDC = m_staticColor.GetDC();
	CRect rect;
	m_staticColor.GetClientRect( &rect );
	rect.DeflateRect( 1, 1 );
	pDC->FillSolidRect( rect, m_clDrawColor );
	m_staticColor.ReleaseDC( pDC );	
	m_staticCanvas.Invalidate();	
}

/// 初始化
void CWhiteBoardClientDlg::Init()
{
	/// 获取主对话框
	m_pMainDlg = ( CInstantMessagingDlg * )::AfxGetMainWnd();
	
	/// 设置橡皮檫的图标
	m_btnEraser.setBmp(	IDB_WHITEBOARD_ERASE_NORMAL,
		IDB_WHITEBOARD_ERASE_HOVER,
		IDB_WHITEBOARD_ERASE_DOWN,
		IDB_WHITEBOARD_ERASE_DISABLE );

	/// 设置画笔的图标
	m_btnPencil.setBmp(	IDB_WHITEBOARD_PENCIL_NORMAL,
		IDB_WHITEBOARD_PENCIL_HOVER,
		IDB_WHITEBOARD_PENCIL_DOWN,
		IDB_WHITEBOARD_PENCIL_DISABLE );

	/// 设置直线的图标
	m_btnLine.setBmp( IDB_WHITEBOARD_LINE_NORMAL,
		IDB_WHITEBOARD_LINE_HOVER,
		IDB_WHITEBOARD_LINE_DOWN,
		IDB_WHITEBOARD_LINE_DISABLE );

	/// 设置空心矩形的图标
	m_btnRectangleEmpty.setBmp(	IDB_WHITEBOARD_RECTANGLE_EMPTY_NORMAL,
		IDB_WHITEBOARD_RECTANGLE_EMPTY_HOVER,
		IDB_WHITEBOARD_RECTANGLE_EMPTY_DOWN,
		IDB_WHITEBOARD_RECTANGLE_EMPTY_DISABLE );

	/// 设置实心矩形的图标
	m_btnRectangle.setBmp( IDB_WHITEBOARD_RECTANGLE_NORMAL,
		IDB_WHITEBOARD_RECTANGLE_HOVER,
		IDB_WHITEBOARD_RECTANGLE_DOWN,
		IDB_WHITEBOARD_RECTANGLE_DISABLE );

	/// 设置空心椭圆的图标
	m_btnEllipseEmpty.setBmp( IDB_WHITEBOARD_ELLIPSE_EMPTY_NORMAL,
		IDB_WHITEBOARD_ELLIPSE_EMPTY_HOVER,
		IDB_WHITEBOARD_ELLIPSE_EMPTY_DOWN,
		IDB_WHITEBOARD_ELLIPSE_EMPTY_DISABLE );

	/// 设置实心椭圆的图标
	m_btnEllipse.setBmp( IDB_WHITEBOARD_ELLIPSE_NORMAL,
		IDB_WHITEBOARD_ELLIPSE_HOVER,
		IDB_WHITEBOARD_ELLIPSE_DOWN,
		IDB_WHITEBOARD_ELLIPSE_DISABLE );



	/// 设置线宽一的图标
	m_btnWidth1.setBmp( IDB_WHITEBOARD_WIDTH_1_NORMAL,
		IDB_WHITEBOARD_WIDTH_1_HOVER,
		IDB_WHITEBOARD_WIDTH_1_DOWN,
		IDB_WHITEBOARD_WIDTH_1_DISABLE );

	/// 设置线宽二的图标
	m_btnWidth2.setBmp( IDB_WHITEBOARD_WIDTH_2_NORMAL,
		IDB_WHITEBOARD_WIDTH_2_HOVER,
		IDB_WHITEBOARD_WIDTH_2_DOWN,
		IDB_WHITEBOARD_WIDTH_2_DISABLE );

	/// 设置线宽三的图标
	m_btnWidth3.setBmp( IDB_WHITEBOARD_WIDTH_3_NORMAL,
		IDB_WHITEBOARD_WIDTH_3_HOVER,
		IDB_WHITEBOARD_WIDTH_3_DOWN,
		IDB_WHITEBOARD_WIDTH_3_DISABLE );

	/// 设置线宽四的图标
	m_btnWidth4.setBmp( IDB_WHITEBOARD_WIDTH_4_NORMAL,
		IDB_WHITEBOARD_WIDTH_4_HOVER,
		IDB_WHITEBOARD_WIDTH_4_DOWN,
		IDB_WHITEBOARD_WIDTH_4_DISABLE );

	/// 设置选中的工具和线宽
	m_btnPencil.EnableWindow( FALSE );
	m_btnWidth1.EnableWindow( FALSE );
	
	// 初始化UDP套接字
	m_pWBCSocket = new CWhiteBoardClientSocket( this );
	m_pWBCSocket->Create( WHITEBOARD_CLIENT_PORT, SOCK_DGRAM );

	/// 调整各控件的位置
	SetPosition();

	/// 设置画布的初始状态
	m_staticCanvas.SetTool( m_emTool );
	m_staticCanvas.SetWidth( m_nWidth );
	m_staticCanvas.SetColor( m_clDrawColor );
}

/// 从UDP中接收数据
void CWhiteBoardClientDlg::OnReceive()
{
	/// 接收数据
	CString strIP;
	UINT uPort;
	char szReceive[ MAXDATAPACKETLENGTH ];
	m_pWBCSocket->ReceiveFrom( szReceive, MAXDATAPACKETLENGTH, strIP, uPort );
	
	/// 装配数据包
	DATAPACKET dataPacket;
	memcpy( &dataPacket, szReceive, sizeof( DATAPACKET ) );
	
	switch( dataPacket.command )
	{
	case WHITEBOARD_SERVER_CLOSED:							/// 白板服务器关闭
		ServerClosed();
		break;
	case WHITEBOARD_CLIENT_KICKED:							/// 客户端被踢
		Kicked();
		break;
	case WHITEBOARD_DRAWINFO:						    	///	白板服务器的画图数据
		ReceiveDrawData( szReceive );
		break;
	default:
		break;
	}
}

/// 调整各控件的位置
void CWhiteBoardClientDlg::SetPosition()
{
	/// 控件未创建不调整
	if( !m_staticCanvas )
	{
		return ;
	}
	CRect rect;
	GetClientRect( &rect );

	CRect rectCanvas;
	m_staticCanvas.GetWindowRect( &rectCanvas );
	ScreenToClient( &rectCanvas );

	rectCanvas.right	= rect.right - 8;
	rectCanvas.bottom	= rect.bottom - 8;
	m_staticCanvas.MoveWindow( rectCanvas );
}	

void CWhiteBoardClientDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	SetPosition();
}

void CWhiteBoardClientDlg::OnColor() 
{
	/// 弹出颜色获对话框
	CColorDialog clDlg;
	clDlg.m_cc.Flags |= CC_FULLOPEN | CC_RGBINIT;
	clDlg.m_cc.rgbResult = m_clDrawColor;
	if( IDCANCEL == clDlg.DoModal() )
	{
		return ;
	}

	/// 设置并画出
	m_clDrawColor = clDlg.GetColor();
	CDC *pDC = m_staticColor.GetDC();
	CRect rect;
	m_staticColor.GetClientRect( &rect );
	rect.DeflateRect( 1, 1 );
	pDC->FillSolidRect( rect, m_clDrawColor );
	m_staticColor.ReleaseDC( pDC );
	m_staticCanvas.SetColor( m_clDrawColor );
}

void CWhiteBoardClientDlg::OnEraser() 
{
	ResetTools();
	m_emTool = ERASER;
	m_btnEraser.EnableWindow( FALSE );
	m_staticCanvas.SetTool( m_emTool );
}

void CWhiteBoardClientDlg::OnPencil() 
{
	ResetTools();
	m_emTool = PENCIL;
	m_btnPencil.EnableWindow( FALSE );
	m_staticCanvas.SetTool( m_emTool );
}

void CWhiteBoardClientDlg::OnLine() 
{
	ResetTools();
	m_emTool = LINE;
	m_btnLine.EnableWindow( FALSE );
	m_staticCanvas.SetTool( m_emTool );
}

void CWhiteBoardClientDlg::OnRectangle() 
{
	ResetTools();
	m_emTool = RECTANGLE;
	m_btnRectangle.EnableWindow( FALSE );
	m_staticCanvas.SetTool( m_emTool );
}

void CWhiteBoardClientDlg::OnRectangleEmpty() 
{
	ResetTools();
	m_emTool = RECTANGLE_EMPTY;
	m_btnRectangleEmpty.EnableWindow( FALSE );
	m_staticCanvas.SetTool( m_emTool );
}

void CWhiteBoardClientDlg::OnEllipseEmpty() 
{
	ResetTools();
	m_emTool = ELLIPSE_EMPTY;
	m_btnEllipseEmpty.EnableWindow( FALSE );
	m_staticCanvas.SetTool( m_emTool );
}

void CWhiteBoardClientDlg::OnEllipse()
{
	ResetTools();
	m_emTool = ELLIPSE;
	m_btnEllipse.EnableWindow( FALSE );
	m_staticCanvas.SetTool( m_emTool );
}

void CWhiteBoardClientDlg::OnWidth1() 
{
	ResetWidth();
	m_nWidth = WHITEBOARD_WIDTH_1;
	m_btnWidth1.EnableWindow( FALSE );
	m_staticCanvas.SetWidth( m_nWidth );
}

void CWhiteBoardClientDlg::OnWidth2() 
{	
	ResetWidth();
	m_nWidth = WHITEBOARD_WIDTH_2;
	m_btnWidth2.EnableWindow( FALSE );
	m_staticCanvas.SetWidth( m_nWidth );
}

void CWhiteBoardClientDlg::OnWidth3() 
{
	ResetWidth();
	m_nWidth = WHITEBOARD_WIDTH_3;
	m_btnWidth3.EnableWindow( FALSE );
	m_staticCanvas.SetWidth( m_nWidth );
}

void CWhiteBoardClientDlg::OnWidth4() 
{	
	ResetWidth();
	m_nWidth = WHITEBOARD_WIDTH_4;
	m_btnWidth4.EnableWindow( FALSE );
	m_staticCanvas.SetWidth( m_nWidth );
}

/// 恢复工具的状态
void CWhiteBoardClientDlg::ResetTools()
{
	switch( m_emTool )
	{
	case ERASER:
		m_btnEraser.SetNormal();
		break;
	case PENCIL:
		m_btnPencil.SetNormal();
		break;
	case LINE:
		m_btnLine.SetNormal();
		break;
	case RECTANGLE_EMPTY:
		m_btnRectangleEmpty.SetNormal();
		break;
	case RECTANGLE:
		m_btnRectangle.SetNormal();
		break;
	case ELLIPSE_EMPTY:
		m_btnEllipseEmpty.SetNormal();
		break;
	case ELLIPSE:
		m_btnEllipse.SetNormal();
		break;
	default:
		break;
	}
}

///	恢复线宽
void CWhiteBoardClientDlg::ResetWidth()
{
	switch( m_nWidth )
	{
	case WHITEBOARD_WIDTH_1:
		m_btnWidth1.SetNormal();
		break;
	case WHITEBOARD_WIDTH_2:
		m_btnWidth2.SetNormal();
		break;
	case WHITEBOARD_WIDTH_3:
		m_btnWidth3.SetNormal();
		break;
	case WHITEBOARD_WIDTH_4:
		m_btnWidth4.SetNormal();
		break;
	default:
		break;
	}
}

void CWhiteBoardClientDlg::OnSizing(UINT fwSide, LPRECT pRect) 
{
	CDialog::OnSizing(fwSide, pRect);
	
	/// 限制窗口的最小
	switch( fwSide )
	{
	case 1:
		pRect->left = pRect->right - pRect->left < WHITEBOARD_MIN_WIDTH ? pRect->right - WHITEBOARD_MIN_WIDTH : pRect->left;
		break;
	case 2:
		pRect->right = pRect->right - pRect->left < WHITEBOARD_MIN_WIDTH ? pRect->left + WHITEBOARD_MIN_WIDTH : pRect->right;
		break;
	case 3:
		pRect->top = pRect->bottom - pRect->top < WHITEBOARD_MIN_HEIGHT ? pRect->bottom - WHITEBOARD_MIN_HEIGHT : pRect->top;
		break;
	case 4:
		pRect->left = pRect->right - pRect->left < WHITEBOARD_MIN_WIDTH ? pRect->right - WHITEBOARD_MIN_WIDTH : pRect->left;
		pRect->top = pRect->bottom - pRect->top < WHITEBOARD_MIN_HEIGHT ? pRect->bottom - WHITEBOARD_MIN_HEIGHT : pRect->top;
		break;
	case 5:
		pRect->right = pRect->right - pRect->left < WHITEBOARD_MIN_WIDTH ? pRect->left + WHITEBOARD_MIN_WIDTH : pRect->right;
		pRect->top = pRect->bottom - pRect->top < WHITEBOARD_MIN_HEIGHT ? pRect->bottom - WHITEBOARD_MIN_HEIGHT : pRect->top;
		break;
	case 6:
		pRect->bottom = pRect->bottom - pRect->top < WHITEBOARD_MIN_HEIGHT ? pRect->top + WHITEBOARD_MIN_HEIGHT : pRect->bottom;
		break;
	case 7:
		pRect->left = pRect->right - pRect->left < WHITEBOARD_MIN_WIDTH ? pRect->right - WHITEBOARD_MIN_WIDTH : pRect->left;
		pRect->bottom = pRect->bottom - pRect->top < WHITEBOARD_MIN_HEIGHT ? pRect->top + WHITEBOARD_MIN_HEIGHT : pRect->bottom;
		break;
	case 8:
		pRect->right = pRect->right - pRect->left < WHITEBOARD_MIN_WIDTH ? pRect->left + WHITEBOARD_MIN_WIDTH : pRect->right;
		pRect->bottom = pRect->bottom - pRect->top < WHITEBOARD_MIN_HEIGHT ? pRect->top + WHITEBOARD_MIN_HEIGHT : pRect->bottom;
		break;
	default:
		break;
	}	
}

/// 向指定IP、PORT发送指定数据
void CWhiteBoardClientDlg::SendUserCommandToIP( CONTROLCOMMAND command, LPCSTR szIP, UINT uPort, const USER *pUser )
{
	DATAPACKET dataPacket;
	dataPacket.command	= command;
	
	/// 分配空间
	UINT uDataLength = sizeof( DATAPACKET );
	if( pUser )
	{
		uDataLength += sizeof( USER );
	}
	BYTE *pSendData = new BYTE[ uDataLength ];
	memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
	if( pUser )
	{
		memcpy( pSendData + sizeof( DATAPACKET ), pUser, sizeof( USER ) );
	}
	
	/// 发送数据
	m_pWBCSocket->SendTo( pSendData, uDataLength, uPort, szIP );
	
	delete pSendData;
}

/// 将画图信息发送到服务器
void CWhiteBoardClientDlg::SendDrawInfoToServer(  const CPoint ptStart, const CPoint ptEnd )
{
	DRAWINFO drawInfo;
	drawInfo.color		= m_clDrawColor;
	drawInfo.nWidth		= m_nWidth;
	drawInfo.tool		= m_emTool;
	drawInfo.ptStart	= ptStart;
	drawInfo.ptEnd		= ptEnd;

	DATAPACKET dataPacket;
	dataPacket.command	= WHITEBOARD_DRAWINFO;

	UINT uDataLength	= sizeof( dataPacket ) + sizeof( DRAWINFO );
	BYTE *pSendData		= new BYTE[ uDataLength ];

	memcpy( pSendData, &dataPacket, sizeof( DATAPACKET ) );
	memcpy( pSendData + sizeof( DATAPACKET ), &drawInfo, sizeof( DRAWINFO ) );
	
	/// 发送数据
	m_pWBCSocket->SendTo( pSendData, uDataLength, WHITEBOARD_SERVER_PORT, m_strServerIP );
	
	delete [] pSendData;
}
