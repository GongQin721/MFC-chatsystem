// SendFilesReceiveUsersDlg.cpp : implementation file
//

#include "stdafx.h"
#include "instantmessaging.h"
#include "SendFilesReceiveUsersDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSendFilesReceiveUsersDlg dialog

#include "InstantMessagingDlg.h"

CSendFilesReceiveUsersDlg::CSendFilesReceiveUsersDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSendFilesReceiveUsersDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSendFilesReceiveUsersDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	/// 加载图像列表，并将32*32的图像缩小为16*16
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
}


void CSendFilesReceiveUsersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSendFilesReceiveUsersDlg)
	DDX_Control(pDX, IDC_LIST_USER, m_listCtrlUser);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSendFilesReceiveUsersDlg, CDialog)
	//{{AFX_MSG_MAP(CSendFilesReceiveUsersDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSendFilesReceiveUsersDlg message handlers

BOOL CSendFilesReceiveUsersDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	///	初始化
	Init();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

///	初始化
void CSendFilesReceiveUsersDlg::Init()
{
	/// 获取主对话框
	m_pMainDlg = ( CInstantMessagingDlg * )::AfxGetMainWnd();

	/// 设置用户列表框的图像
	m_listCtrlUser.SetImageList( &m_imageList, LVSIL_SMALL );
	m_listCtrlUser.SetExtendedStyle( m_listCtrlUser.GetExtendedStyle() | 
		LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES );
	m_listCtrlUser.InsertColumn( 0, "" );

	/// 把所有好友添加进列表
	m_pMainDlg->GetFriendsArray( m_arrFriends );
	for( int nIndex = 0; nIndex < m_arrFriends.GetSize(); nIndex++ )
	{
		CString strText;
		strText.Format( "%s(%s)",
			m_arrFriends.GetAt( nIndex ).strName,
			m_arrFriends.GetAt( nIndex ).strIP );
		m_listCtrlUser.InsertItem( nIndex, strText, m_arrFriends.GetAt( nIndex ).nFace );
		m_listCtrlUser.SetColumnWidth( 0, LVSCW_AUTOSIZE_USEHEADER );
	}
}

void CSendFilesReceiveUsersDlg::OnOK() 
{
	/// 得到要发送的USER
	CArray< USER, USER > arrFriends;
	for( int nIndex = 0; nIndex < m_listCtrlUser.GetItemCount(); nIndex++ )
	{
		if( m_listCtrlUser.GetCheck( nIndex ) )
		{
			arrFriends.Add( m_arrFriends.GetAt( nIndex ) );
		}
	}
	m_pSFSDlg->SetReceivedUser( arrFriends );
	CDialog::OnOK();
}

void CSendFilesReceiveUsersDlg::OnCancel() 
{	
	CDialog::OnCancel();
}