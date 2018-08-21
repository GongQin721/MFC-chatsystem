// WhiteBoardClientSocket.cpp : implementation file
//

#include "stdafx.h"
#include "instantmessaging.h"
#include "WhiteBoardClientSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWhiteBoardClientSocket

CWhiteBoardClientSocket::CWhiteBoardClientSocket()
{
}

CWhiteBoardClientSocket::CWhiteBoardClientSocket( CWhiteBoardClientDlg * pWBClientDlg )
{
	m_pWBClientDlg = pWBClientDlg;
}

CWhiteBoardClientSocket::~CWhiteBoardClientSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CWhiteBoardClientSocket, CSocket)
	//{{AFX_MSG_MAP(CWhiteBoardClientSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CWhiteBoardClientSocket member functions

void CWhiteBoardClientSocket::OnReceive(int nErrorCode) 
{
	m_pWBClientDlg->OnReceive();
	CSocket::OnReceive(nErrorCode);
}
