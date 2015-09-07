// SM630 PC Demo.h : main header file for the SM630 PC DEMO application
//

#if !defined(AFX_SM630PCDEMO_H__A825A19F_BE95_43D7_86BF_81D167837FAE__INCLUDED_)
#define AFX_SM630PCDEMO_H__A825A19F_BE95_43D7_86BF_81D167837FAE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSM630PCDemoApp:
// See SM630 PC Demo.cpp for the implementation of this class
//

class CSM630PCDemoApp : public CWinApp
{
public:
	CSM630PCDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSM630PCDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSM630PCDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SM630PCDEMO_H__A825A19F_BE95_43D7_86BF_81D167837FAE__INCLUDED_)
