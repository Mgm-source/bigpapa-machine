#include <afxwin.h>
#include "hello.h"

CMyApp myApp;

constexpr auto SEGMENTS = 600;
constexpr auto PI = 3.1415926;
constexpr auto IDC_LISTBOX = 100;

BOOL CMyApp::InitInstance()
{

	m_pMainWnd = new CMainWindow;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

BEGIN_MESSAGE_MAP(CMainWindow,CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
	ON_WM_SETFOCUS()
	ON_WM_DROPFILES()
	ON_LBN_SELCHANGE(IDC_LISTBOX, OnSelChange)
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	ON_WM_ERASEBKGND()
	END_MESSAGE_MAP()

CMainWindow::CMainWindow() : m_bMouseOver{ false } , m_cxChar{0}, m_cyChar{0}
{
	Create(NULL, L"THE HELLO APPLICATION");
}

void CMainWindow::DoGradientFill(CDC* pdc, LPRECT _rect)
{
	CBrush* pBrush[64];
	for (int i = 0; i < 64; i++)
		pBrush[i] = new CBrush(RGB(255 - (i * 4),0 ,0 ));
	int nWidth = _rect->right - _rect->left;
	int nHeight = _rect->bottom - _rect->top;
	CRect rect;
	for (int i = 0; i < nHeight; i++) {
		rect.SetRect(0, i, nWidth, i + 1);
		pdc->FillRect(&rect, pBrush[(i * 63) / nHeight]);
	}
	for (int i = 0; i < 64; i++)
		delete pBrush[i];
}

void CMainWindow::DoDrawText(CDC* pdc, LPRECT rect)
{
	CFont font;
	font.CreatePointFont(720, _T("Comic Sans MS"));
	pdc->SetBkMode(TRANSPARENT);
	pdc->SetTextColor(RGB(255, 255, 255));
	CFont* pOldFont = pdc->SelectObject(&font);
	pdc->DrawText(_T("Hello, MFC"), -1, rect, DT_SINGLELINE |
		DT_CENTER | DT_VCENTER);
	pdc->SelectObject(pOldFont);
}

void CMainWindow::OnPaint()
{
	CRect rect;
	CFont font;
	GetClientRect(&rect);
	font.CreatePointFont(720, _T("Arial"));

	CPaintDC dc(this); // on the stack deletes itself, well pops off the stack. 

	m_wndDrawListBox.projectImage(&dc, m_rcImage,
		::GetSysColor(COLOR_3DFACE));

	DoDrawText(&dc, &rect);
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

int CMainWindow::OnCreate(LPCREATESTRUCT lpcs)
{
	if (CWnd::OnCreate(lpcs) == -1)
		return -1;
	m_font.CreatePointFont(80, _T("MS Sans Serif"));
	CClientDC dc(this);
	CFont* pOldFont = dc.SelectObject(&m_font);
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);

	m_cxChar = tm.tmAveCharWidth;
	m_cyChar = tm.tmHeight + tm.tmExternalLeading;
	dc.SelectObject(pOldFont);
	m_rcImage.SetRect(m_cxChar * 4, m_cyChar * 3, m_cxChar * 46,
		m_cyChar * 19);

	m_wndGroupBox.Create(_T("Detail"), WS_CHILD | WS_VISIBLE |
		BS_GROUPBOX,
		CRect(m_cxChar * 2, m_cyChar, m_cxChar * 48, m_cyChar * 20),
		this, (UINT)-1);
	m_wndLabel.Create(_T("Icons"), WS_CHILD | WS_VISIBLE |
		SS_LEFT,
		CRect(m_cxChar * 50, m_cyChar, m_cxChar * 82, m_cyChar * 2),
		this);
	m_wndDrawListBox.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL
		|
		WS_BORDER | LBS_NOTIFY | LBS_NOINTEGRALHEIGHT,
		CRect(m_cxChar * 50, m_cyChar * 2, m_cxChar * 82, m_cyChar *
			20),
		this, IDC_LISTBOX);
	m_wndGroupBox.SetFont(&m_font);
	m_wndLabel.SetFont(&m_font);
	DragAcceptFiles();

	if (dc.GetDeviceCaps(RASTERCAPS) & RC_PALETTE) 
	{
		struct {
			LOGPALETTE lp;
			PALETTEENTRY ape[63];
		} pal;

		LOGPALETTE* pLP = (LOGPALETTE*)&pal;
		pLP->palVersion = 0x300;
		pLP->palNumEntries = 64;

		for (int i = 0; i < 64; i++) {
			pLP->palPalEntry[i].peRed = 0;
			pLP->palPalEntry[i].peGreen = 0;
			pLP->palPalEntry[i].peBlue = 255 - (i * 4);
			pLP->palPalEntry[i].peFlags = 0;
		}
		palette.CreatePalette(pLP);
	}

	return 0;
}

void CMainWindow::OnSetFocus(CWnd* pWnd)
{
	m_wndDrawListBox.SetFocus();
}

void CMainWindow::OnDropFiles(HDROP hDropInfo)
{
	int nCount = ::DragQueryFile(hDropInfo, (UINT)-1, NULL, 0);
	if (nCount == 1) { 
		m_wndDrawListBox.ResetContent();
		// 
// Extract the file's icons and add them to the list box. 
// 
		wchar_t szFile[MAX_PATH];
		::DragQueryFile(hDropInfo, 0, szFile, sizeof(szFile));
		int nIcons = (int) ::ExtractIcon(NULL, szFile, (UINT)-1);
		if (nIcons) {
			HICON hIcon;
			for (int i = 0; i < nIcons; i++) {
				hIcon = ::ExtractIcon(AfxGetInstanceHandle(),
					szFile, i);
				m_wndDrawListBox.AddIcon(hIcon);
			}
		}
		// 
		// Put the file name in the main window's title bar. 
		// 
		CString strWndTitle = szFile;
		strWndTitle += _T(" - IconView");
		SetWindowText(strWndTitle);
		// 
		// Select item number 0. 
		// 
		CClientDC dc(this);
		m_wndDrawListBox.SetCurSel(0);
		m_wndDrawListBox.projectImage(&dc, m_rcImage,
			::GetSysColor(COLOR_3DFACE));
	}
	::DragFinish(hDropInfo);

}

void CMainWindow::OnSelChange()
{
	CClientDC dc(this);
	m_wndDrawListBox.projectImage(&dc, m_rcImage,
		::GetSysColor(COLOR_3DFACE));
}

BOOL CMainWindow::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);
	CPalette* pOldPalette = nullptr;

	if ((HPALETTE)palette != NULL) {

		pOldPalette = pDC->SelectPalette(&palette, FALSE);
		pDC->RealizePalette();

	}

	DoGradientFill(pDC, &rect);

	if ((HPALETTE)palette != NULL)
		pDC->SelectPalette(pOldPalette, FALSE);


	return TRUE;
}

BOOL CMainWindow::OnQueryNewPalette()
{
	if ((HPALETTE)palette == NULL) // Shouldn't happen, but 
		return 0; // let's be sure. 
	CClientDC dc(this);
	CPalette* pOldPalette = dc.SelectPalette(&palette, FALSE);
	UINT nCount;
	if (nCount = dc.RealizePalette())
		Invalidate();
	dc.SelectPalette(pOldPalette, FALSE);
	return nCount;
}

void CMainWindow::OnPaletteChanged(CWnd* pFocusWnd)
{
	if ((HPALETTE)palette == NULL) // Shouldn't happen, but 
		return; // let's be sure. 
	if (pFocusWnd != this) {
		CClientDC dc(this);
		CPalette* pOldPalette = dc.SelectPalette(&palette, FALSE);
		if (dc.RealizePalette())
			Invalidate();
		dc.SelectPalette(pOldPalette, FALSE);
	}
}
