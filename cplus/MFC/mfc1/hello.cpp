#include <afxwin.h>
#include "hello.h"

CMyApp myApp;

constexpr auto SEGMENTS = 600 ;
constexpr auto PI = 3.1415926 ;

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
	CRect rect;
	CFont font;
	GetClientRect(&rect);
	font.CreatePointFont(720, _T("Arial"));
	CPaintDC dc(this);
	dc.SelectObject(&font);
	dc.SetBkMode(TRANSPARENT);
	CString string = _T("Hello, MFC");
	//rect.OffsetRect(160, 16);
	dc.SetTextColor(RGB(192, 192, 192));
	dc.DrawText(string, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	rect.OffsetRect(-160, -16);
	dc.SetTextColor(RGB(0, 0, 0));
	dc.DrawText(string, &rect, DT_SINGLELINE |
		DT_CENTER | DT_VCENTER);
}

