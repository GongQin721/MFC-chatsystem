// ChatRoomClientSocket.cpp : implementation file
//

#include "stdafx.h"
#include "instantmessaging.h"
#include "ChatRoomClientSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChatRoomClientSocket

CChatRoomClientSocket::CChatRoomClientSocket()
{
}

CChatRoomClientSocket::CChatRoomClientSocket( CChatRoomClientDlg * pCRClientDlg )
{
	m_pCRClientDlg = pCRClientDlg;
}

CChatRoomClientSocket::~CChatRoomClientSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CChatRoomClientSocket, CSocket)
	//{{AFX_MSG_MAP(CChatRoomClientSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CChatRoomClientSocket member functions

void CChatRoomClientSocket::OnReceive(int nErrorCode) 
{	
	if( m_pCRClientDlg )
	{
		m_pCRClientDlg->OnReceive();
	}
	CSocket::OnReceive(nErrorCode);
}
