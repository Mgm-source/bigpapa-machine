
// ScrollApp.h : main header file for the ScrollApp application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CScrollAppApp:
// See ScrollApp.cpp for the implementation of this class
//

class CScrollAppApp : public CWinApp
{
public:
	CScrollAppApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CScrollAppApp theApp;
