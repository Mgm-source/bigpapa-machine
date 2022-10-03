#include "FontView.h"
#include "CMainWindow.h"

FontView MyApp;

BOOL FontView::InitInstance()
{
	m_pMainWnd = new CMainWindow;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}
