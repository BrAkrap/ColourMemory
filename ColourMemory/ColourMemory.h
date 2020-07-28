
// ColourMemory.h : main header file for the ColourMemory application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CColourMemoryApp:
// See ColourMemory.cpp for the implementation of this class
//

class CColourMemoryApp : public CWinApp
{
public:
	CColourMemoryApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CColourMemoryApp theApp;
