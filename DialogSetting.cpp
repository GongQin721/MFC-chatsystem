// DialogSetting.cpp : implementation file
//

#include "stdafx.h"
#include "instantmessaging.h"
#include "DialogSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogSetting dialog

#include "InstantMessagingDlg.h"

CDialogSetting::CDialogSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogSetting)
	//}}AFX_DATA_INIT
}


void CDialogSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogSetting)
	DDX_Control(pDX, IDC_CHECK_AUTOADDFRIENDS, m_btnAutoAddFriends);
	DDX_Control(pDX, IDC_COMBOBOXEX_FACE, m_comboxExFace);
	DDX_Control(pDX, IDC_HOTKEY, m_hotKey);
	DDX_Control(pDX, IDC_EDIT_NICKNAME, m_editNickName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogSetting, CDialog)
	//{{AFX_MSG_MAP(CDialogSetting)
	ON_BN_CLICKED(IDB_SAVE, OnSave)
	ON_BN_CLICKED(IDB_CANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogSetting message handlers
void CDialogSetting::OnCancel() 
{
	CDialog::OnCancel();
}

void CDialogSetting::OnOK() 
{
}

/// 保存设置
void CDialogSetting::OnSave() 
{
	UpdateData( TRUE );
	CString strNickName;
	m_editNickName.GetWindowText( strNickName );
	if( strNickName.GetLength() > MAXNICKNAMELENGTH )
	{
		strNickName = strNickName.Left( MAXNICKNAMELENGTH );
	}
	m_dlgMain->SetNickName( strNickName );
	m_dlgMain->SetFace( m_comboxExFace.GetCurSel() );
	m_dlgMain->SetAutoAddFriends( m_btnAutoAddFriends.GetCheck() );
	WORD wVirtualKeyCode;
	WORD wModifiers;
	m_hotKey.GetHotKey( wVirtualKeyCode, wModifiers );
	m_dlgMain->SetHotKey( wVirtualKeyCode, wModifiers );
	OnCancel();
}

void CDialogSetting::SetMainDlg( CInstantMessagingDlg *dlg )
{
	m_dlgMain = dlg;
}

BOOL CDialogSetting::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	/// 设置对话框的初始化
	m_editNickName.SetWindowText( m_dlgMain->GetNickName() );
	m_hotKey.SetHotKey( m_dlgMain->GetVirtualKeyCode(), m_dlgMain->GetModifiers() );
	m_btnAutoAddFriends.SetCheck( m_dlgMain->GetAutoAddFriends() );
	
	/// 创建头像列表显示框
	m_imageList.Create( 32, 32, ILC_MASK | ILC_COLOR24, 0, 0 );
	CBitmap bitmap;
	for( int nIndex = 0; nIndex < MAXFACES; nIndex++ )
	{
		bitmap.LoadBitmap( IDB_BITMAP1 + nIndex );
		m_imageList.Add( &bitmap, FACEBGCOLOR );
		bitmap.DeleteObject();
	}
	m_comboxExFace.SetImageList( &m_imageList );

	COMBOBOXEXITEM insItem;
	insItem.mask	= CBEIF_TEXT | CBEIF_IMAGE | CBEIF_SELECTEDIMAGE | CBEIF_OVERLAY;
	insItem.pszText	= "";

	/// 向头像列表框中添加头像
	for( nIndex = 0; nIndex < MAXFACES; nIndex++ )
	{
		insItem.iItem			= nIndex;
		insItem.iImage			= nIndex;
		insItem.iSelectedImage	= nIndex;
		m_comboxExFace.InsertItem(&insItem);
	}
	m_comboxExFace.SetCurSel( m_dlgMain->GetFace() );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
