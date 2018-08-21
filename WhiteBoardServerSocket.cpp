
#include "stdafx.h"
#include "instantmessaging.h"
#include "WhiteBoardServerSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CWhiteBoardServerSocket::CWhiteBoardServerSocket()
{
}

CWhiteBoardServerSocket::CWhiteBoardServerSocket( CWhiteBoardServerDlg * pWBServerDlg )
{
	m_pWBServerDlg = pWBServerDlg;
}

CWhiteBoardServerSocket::~CWhiteBoardServerSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CWhiteBoardServerSocket, CSocket)
	//{{AFX_MSG_MAP(CWhiteBoardServerSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CWhiteBoardServerSocket member functions

void CWhiteBoardServerSocket::OnReceive(int nErrorCode) 
{
	m_pWBServerDlg->OnReceive();
	CSocket::OnReceive(nErrorCode);
}
