// MyClip.h: interface for the CMyClip class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYCLIP_H__3F50824B_6C97_11D5_B617_D466F313FE46__INCLUDED_)
#define AFX_MYCLIP_H__3F50824B_6C97_11D5_B617_D466F313FE46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "afxwin.h"

class CMyClip  
{
public:
	CMyClip();
	virtual ~CMyClip();
	void CopyText(CString test);
	CString GetText();
};

#endif // !defined(AFX_MYCLIP_H__3F50824B_6C97_11D5_B617_D466F313FE46__INCLUDED_)
