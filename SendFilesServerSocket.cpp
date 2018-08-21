// SendFilesServerSocket.cpp : implementation file
//

#include "stdafx.h"
#include "instantmessaging.h"
#include "SendFilesServerSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSendFilesServerSocket

CSendFilesServerSocket::CSendFilesServerSocket()
{
}

CSendFilesServerSocket::~CSendFilesServerSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CSendFilesServerSocket, CSocket)
	//{{AFX_MSG_MAP(CSendFilesServerSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CSendFilesServerSocket member functions

void CSendFilesServerSocket::OnAccept(int nErrorCode) 
{
	m_pSFSDlg->OnAccept();
	CSocket::OnAccept(nErrorCode);
}