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
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
	END_MESSAGE_MAP()

CMainWindow::CMainWindow() : m_bMouseOver{ false }
{
	Create(NULL, L"THE HELLO APPLICATION",WS_OVERLAPPEDWINDOW,
		rectDefault, NULL, MAKEINTRESOURCE(IDR_MAINFRAME));
}

void CMainWindow::OnPaint()
{
	CRect rect;
	CFont font;
	GetClientRect(&rect);
	font.CreatePointFont(720, _T("Arial"));

	CPaintDC dc(this); // on the stack deletes itself, well pops off the stack. 

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

void CMainWindow::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!m_bMouseOver) {
		TRACE(_T("Mouse enter\n"));
		m_bMouseOver = TRUE;
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.dwFlags = TME_HOVER | TME_LEAVE;
		tme.hwndTrack = m_hWnd;
		tme.dwHoverTime = HOVER_DEFAULT;
		::TrackMouseEvent(&tme);
	}
}

LRESULT CMainWindow::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	TRACE(_T("Mouse leave\n"));
	m_bMouseOver = FALSE;

	return 0;
}

LRESULT CMainWindow::OnMouseHover(WPARAM wParam, LPARAM lParam)
{
	TRACE(_T("Mouse hover (x=%d, y=%d)\n"),
		LOWORD(lParam), HIWORD(lParam));
	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(tme);
	tme.dwFlags = TME_HOVER | TME_LEAVE;
	tme.hwndTrack = m_hWnd;
	tme.dwHoverTime = HOVER_DEFAULT;
	::TrackMouseEvent(&tme);
	
	return 0;
}
