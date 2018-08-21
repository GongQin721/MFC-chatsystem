// InstantMessaging.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "InstantMessaging.h"
#include "InstantMessagingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInstantMessagingApp

BEGIN_MESSAGE_MAP(CInstantMessagingApp, CWinApp)
	//{{AFX_MSG_MAP(CInstantMessagingApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInstantMessagingApp construction

CInstantMessagingApp::CInstantMessagingApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CInstantMessagingApp object

CInstantMessagingApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CInstantMessagingApp initialization

BOOL CInstantMessagingApp::InitInstance()
{
	/// 保证只有唯一实例在运行
	HANDLE hEvent = ::CreateEvent( NULL, FALSE, FALSE, "InstantMessaging" );
	if( hEvent )
	{
		if( ERROR_ALREADY_EXISTS == GetLastError() )
		{
			return FALSE;
		}
	}

	/// 初始化WinSocket
	WSADATA wsaData;
	if (!AfxSocketInit( &wsaData ))
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	/// 初始化RickEdit
	AfxInitRichEdit();

	AfxEnableControlContainer();

	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	/// 不在任务显示程序图标
	CDialog dlgParent;
	dlgParent.Create( IDD_DIALOG_BG );
	dlgParent.ShowWindow( SW_HIDE );

	CInstantMessagingDlg dlg( &dlgParent );
	m_pMainWnd = &dlg;

	/// 设置UDP支持的最大数据包长度
	dlg.SetMaxUDPDG( wsaData.iMaxUdpDg );

	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
