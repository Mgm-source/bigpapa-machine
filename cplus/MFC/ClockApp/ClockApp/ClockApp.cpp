#include "ClockApp.h"
#include "CMainWindow.h"

ClockApp theApp;

BOOL ClockApp::InitInstance()
{
	SetRegistryKey(_T("Programming Windows with MFC"));
	m_pMainWnd = new CMainWindow;
	if (!((CMainWindow*)m_pMainWnd)->RestoreWindowState())
		m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}
