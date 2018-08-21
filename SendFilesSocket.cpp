// SendFilesSocket.cpp : implementation file
//

#include "stdafx.h"
#include "instantmessaging.h"
#include "SendFilesSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "SendFilesServerDlg.h"
#include "SendFilesServerThread.h"

/////////////////////////////////////////////////////////////////////////////
// CSendFilesSocket

CSendFilesSocket::CSendFilesSocket()
{
}

CSendFilesSocket::~CSendFilesSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CSendFilesSocket, CSocket)
	//{{AFX_MSG_MAP(CSendFilesSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CSendFilesSocket member functions

void CSendFilesSocket::OnReceive(int nErrorCode) 
{
	m_pSFSThead->OnReceive();
	CSocket::OnReceive(nErrorCode);
}

void CSendFilesSocket::OnClose(int nErrorCode) 
{
	m_pSFSThead->OnClose();
	CSocket::OnClose(nErrorCode);
}
