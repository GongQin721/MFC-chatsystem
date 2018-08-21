// ChatRoomServerSocket.cpp : implementation file
//

#include "stdafx.h"
#include "instantmessaging.h"
#include "ChatRoomServerSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChatRoomServerSocket

CChatRoomServerSocket::CChatRoomServerSocket()
{
}

CChatRoomServerSocket::CChatRoomServerSocket( CChatRoomServerDlg * pCRServerDlg )
{
	m_pCRServerDlg = pCRServerDlg;
}

CChatRoomServerSocket::~CChatRoomServerSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CChatRoomServerSocket, CSocket)
	//{{AFX_MSG_MAP(CChatRoomServerSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CChatRoomServerSocket member functions

void CChatRoomServerSocket::OnReceive(int nErrorCode) 
{	
	if( m_pCRServerDlg )
	{
		m_pCRServerDlg->OnReceive();
	}
	CSocket::OnReceive(nErrorCode);
}
