// Debug.cpp: implementation of the CDebug class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "instantmessaging.h"
#include "Debug.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDebug::CDebug()
{
}

CDebug::CDebug( CString strMessage )
{
	m_strMessage = strMessage;
	CString strTrace;
	strTrace = "run in  : " + m_strMessage + "\n";
	TRACE( strTrace );
}

CDebug::~CDebug()
{
	CString strTrace;
	strTrace = "run out : " + m_strMessage + "\n";
	TRACE( strTrace );
}
