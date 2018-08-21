// ReceiveFilesSocket.cpp : implementation file
//

#include "stdafx.h"
#include "instantmessaging.h"
#include "ReceiveFilesSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "SendFilesClientThread.h"

/////////////////////////////////////////////////////////////////////////////
// CReceiveFilesSocket

CReceiveFilesSocket::CReceiveFilesSocket()
{
}

CReceiveFilesSocket::~CReceiveFilesSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CReceiveFilesSocket, CSocket)
	//{{AFX_MSG_MAP(CReceiveFilesSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CReceiveFilesSocket member functions

void CReceiveFilesSocket::OnReceive(int nErrorCode) 
{
	m_pSFCThead->OnReceive();
	CSocket::OnReceive(nErrorCode);
}

void CReceiveFilesSocket::OnClose(int nErrorCode) 
{
	m_pSFCThead->OnClose();
	CSocket::OnClose(nErrorCode);
}
