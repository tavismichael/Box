// box.h : main header file for the BOX application
//

#if !defined(AFX_BOX_H__E25E7B09_5840_4169_BF86_63346232BDFE__INCLUDED_)
#define AFX_BOX_H__E25E7B09_5840_4169_BF86_63346232BDFE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBoxApp:
// See box.cpp for the implementation of this class
//

class CBoxApp : public CWinApp
{
public:
	CBoxApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBoxApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBoxApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BOX_H__E25E7B09_5840_4169_BF86_63346232BDFE__INCLUDED_)
