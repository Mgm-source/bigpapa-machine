#include <afxwin.h>
#include "hello.h"

CMyApp myApp;

BOOL CMyApp::InitInstance()
{
	m_pMainWnd = new CMainWindow;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

BEGIN_MESSAGE_MAP(CMainWindow,CFrameWnd)
	ON_WM_PAINT()
	END_MESSAGE_MAP()

CMainWindow::CMainWindow()
{
	Create(NULL, L"THE HELLO APPLICATION");
}

void CMainWindow::OnPaint()
{
	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);

	dc.DrawText(L"Hello, MFC", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}

