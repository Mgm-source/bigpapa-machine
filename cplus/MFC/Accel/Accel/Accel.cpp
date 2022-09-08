#include "Accel.h"
#include "CMainWindow.h"

Accel myApp;

BOOL Accel::InitInstance()
{
	m_pMainWnd = new CMainWindow;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}
