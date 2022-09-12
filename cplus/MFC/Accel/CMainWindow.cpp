#include "CMainWindow.h"

BEGIN_MESSAGE_MAP(CMainWindow,CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

CMainWindow::CMainWindow()
{
	Create(NULL, _T("Accel"),	WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL);
}

void CMainWindow::OnPaint()
{
	CPaintDC dc(this);

	dc.SetWindowOrg(m_nHScrollPos, m_nVScrollPos);

	CPen apen(PS_SOLID, 0, RGB(192, 192, 192));
	CPen* oldPen = dc.SelectObject(&apen);

	// 99 Horizontal lines 
	for (int i = 0; i < 99; i++) 
	{
		int y = i * m_nCellHeight + m_nCellHeight;
		dc.MoveTo(0, y);
		dc.LineTo(m_nViewWidth, y);
	}

	// 26 vertical lines
	for (int i = 0; i < 26; i++) 
	{
		int x = (i * m_nCellWidth) + m_nRibbonWidth;
		dc.MoveTo(x, 0);
		dc.LineTo(x, m_nViewHeight);
	}

	dc.SelectObject(oldPen);

	CBrush brush;

	brush.CreateStockObject(LTGRAY_BRUSH);
	
	CRect rcTop(0, 0, m_nViewWidth, m_nCellHeight);
	dc.FillRect(rcTop, &brush);
	CRect rcLeft(0, 0, m_nRibbonWidth, m_nViewHeight);
	dc.FillRect(rcLeft, &brush);
	dc.MoveTo(0, m_nCellHeight);
	dc.LineTo(m_nViewWidth, m_nCellHeight);
	dc.MoveTo(m_nRibbonWidth, 0);
	dc.LineTo(m_nRibbonWidth, m_nViewHeight);

	dc.SetBkMode(TRANSPARENT);

	for (int i = 0; i < 99; i++) {
		int y = (i * m_nCellHeight) + m_nCellHeight;
		dc.MoveTo(0, y);
		dc.LineTo(m_nRibbonWidth, y);
		CString string;
		string.Format(_T("%d"), i + 1);
		CRect rect(0, y, m_nRibbonWidth, y + m_nCellHeight);
		dc.DrawText(string, &rect, DT_SINGLELINE |
			DT_CENTER | DT_VCENTER);
		rect.top++;
		dc.Draw3dRect(rect, RGB(255, 255, 255),
			RGB(128, 128, 128));
	}
}

int CMainWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

	CClientDC dc(this);
	
	m_nCellWidth = dc.GetDeviceCaps(LOGPIXELSX);
	m_nCellHeight = dc.GetDeviceCaps(LOGPIXELSY) / 4;
	m_nRibbonWidth = m_nCellWidth / 2;
	m_nViewWidth = (26 * m_nCellWidth) + m_nRibbonWidth;
	m_nViewHeight = m_nCellHeight * 100;
	
	return 0;
}

void CMainWindow::OnSize(UINT type, int cx, int cy)
{
	CFrameWnd::OnSize(type, cx, cy);

	int nHScrollMax = 0;
	m_nHScrollPos = m_nHPageSize = 0;
	
	if (cx < m_nViewWidth) {
		nHScrollMax = m_nViewWidth - 1;
		m_nHPageSize = cx;
		m_nHScrollPos = min(m_nHScrollPos, m_nViewWidth -m_nHPageSize - 1);
	}
	
	SCROLLINFO si{};

	si.fMask = SIF_PAGE | SIF_RANGE | SIF_POS;
	si.nMin = 0;
	si.nMax = nHScrollMax;
	si.nPos = m_nHScrollPos;
	si.nPage = m_nHPageSize;
	SetScrollInfo(SB_HORZ, &si, TRUE);

	int nVScrollMax = 0;
	
	m_nVScrollPos = m_nVPageSize = 0;
	
	if (cy < m_nViewHeight) {
		nVScrollMax = m_nViewHeight - 1;
		m_nVPageSize = cy;
		m_nVScrollPos = min(m_nVScrollPos, m_nViewHeight - m_nVPageSize - 1);
	}
	
	si.fMask = SIF_PAGE | SIF_RANGE | SIF_POS;
	si.nMin = 0;
	si.nMax = nVScrollMax;
	si.nPos = m_nVScrollPos;
	si.nPage = m_nVPageSize;

	SetScrollInfo(SB_VERT, &si, TRUE);
}

void CMainWindow::OnHScroll(UINT type, UINT pos, CScrollBar* pScrollBar)
{

	int nDelta = 0;

	switch (type) {
	case SB_LINELEFT:
		nDelta = -LINESIZE;
		break;
	case SB_PAGELEFT:
		nDelta = -m_nHPageSize;
		break;
	case SB_THUMBTRACK:
		nDelta = (int)pos - m_nHScrollPos;
		break;
	case SB_PAGERIGHT:
		nDelta = m_nHPageSize;
		break;
	case SB_LINERIGHT:
		nDelta = LINESIZE;
		break;
	default: // Ignore other scroll bar messages 
		return;
	}

	int nScrollPos = m_nHScrollPos + nDelta;
	int nMaxPos = m_nViewWidth - m_nHPageSize;

	if (nScrollPos < 0)
		nDelta = -m_nHScrollPos;
	else if (nScrollPos > nMaxPos)
	{
		nDelta = nMaxPos - m_nHScrollPos;
	}
	if (nDelta != 0) 
	{
		m_nHScrollPos += nDelta;
		SetScrollPos(SB_HORZ, m_nHScrollPos, TRUE);
		ScrollWindow(-nDelta, 0);
	}
}

void CMainWindow::OnVScroll(UINT type, UINT pos, CScrollBar* pScrollBar)
{
	int nDelta = 0;

	switch (type) {
	case SB_LINEUP:
		nDelta = -LINESIZE;
		break;
	case SB_PAGEUP:
		nDelta = -m_nVPageSize;
		break;
	case SB_THUMBTRACK:
		nDelta = (int)pos - m_nVScrollPos;
		break;
	case SB_PAGEDOWN:
		nDelta = m_nVPageSize;
		break;
	case SB_LINEDOWN:
		nDelta = LINESIZE;
		break;
	default: // Ignore other scroll bar messages 
		return;
	}
	int nScrollPos = m_nVScrollPos + nDelta;
	int nMaxPos = m_nViewHeight - m_nVPageSize;
	if (nScrollPos < 0)
		nDelta = -m_nVScrollPos;
	else if (nScrollPos > nMaxPos) 
	{
		nDelta = nMaxPos - m_nVScrollPos;
	}
	if (nDelta != 0)
	{
		m_nVScrollPos += nDelta;
		SetScrollPos(SB_VERT, m_nVScrollPos, TRUE);
		ScrollWindow(0, -nDelta);
	}
}

BOOL CMainWindow::OnMouseWheel(UINT nFlags, short zDelta, CPoint point)
{
	BOOL bUp = TRUE;
	int nDelta = zDelta;
	if (zDelta < 0) {
		bUp = FALSE;
		nDelta = -nDelta;
	}
	UINT nWheelScrollLines = 0;

		::SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0,
			&nWheelScrollLines, 0);
	if (nWheelScrollLines == WHEEL_PAGESCROLL) {
		SendMessage(WM_VSCROLL,
			MAKEWPARAM(bUp ? SB_PAGEUP : SB_PAGEDOWN, 0),
			0);
	}
	else {
		int nLines = (nDelta * nWheelScrollLines) / WHEEL_DELTA;
		while (nLines--)
			SendMessage(WM_VSCROLL,
				MAKEWPARAM(bUp ? SB_LINEUP : SB_LINEDOWN,
					0), 0);
	}
	return TRUE;
}
