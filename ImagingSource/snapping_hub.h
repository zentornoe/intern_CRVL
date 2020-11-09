// snapping_hub.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// Csnapping_hubApp:
// See snapping_hub.cpp for the implementation of this class.
//

class Csnapping_hubApp : public CWinApp
{
public:
	Csnapping_hubApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Csnapping_hubApp theApp;