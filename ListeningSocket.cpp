// ListeningSocket.cpp : implementation file
//

#include "stdafx.h"
#include "instantmessaging.h"
#include "ListeningSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListeningSocket

CListeningSocket::CListeningSocket()
{
}

CListeningSocket::CListeningSocket( CInstantMessagingDlg * pMainDlg )
{
	m_pMainDlg = pMainDlg;
}

CListeningSocket::~CListeningSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CListeningSocket, CSocket)
	//{{AFX_MSG_MAP(CListeningSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CListeningSocket member functions

void CListeningSocket::OnReceive(int nErrorCode) 
{
	if( m_pMainDlg )
	{
		m_pMainDlg->OnListeningReceive();
	}
	CSocket::OnReceive(nErrorCode);
}
