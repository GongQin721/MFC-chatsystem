// Debug.h: interface for the CDebug class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEBUG_H__D230D620_F131_42E3_A2F0_6C1E1E095962__INCLUDED_)
#define AFX_DEBUG_H__D230D620_F131_42E3_A2F0_6C1E1E095962__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDebug  
{
private:
	CString					m_strMessage;			/// пео╒
public:
	CDebug();
	CDebug( CString strMessage );
	virtual ~CDebug();

};

#endif // !defined(AFX_DEBUG_H__D230D620_F131_42E3_A2F0_6C1E1E095962__INCLUDED_)
