
// ScrollAppView.cpp : implementation of the CScrollAppView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ScrollApp.h"
#endif

#include "ScrollAppDoc.h"
#include "ScrollAppView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CScrollAppView

IMPLEMENT_DYNCREATE(CScrollAppView, CScrollView)

BEGIN_MESSAGE_MAP(CScrollAppView, CScrollView)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CScrollAppView construction/destruction

CScrollAppView::CScrollAppView() noexcept
{
	m_font.CreatePointFont(80, L"MS Sans Serif");

}

CScrollAppView::~CScrollAppView()
{
}

BOOL CScrollAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CScrollView::PreCreateWindow(cs);
}

void CScrollAppView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	m_nCurrentRow = 0;
	m_nCurrentCol = 0;
	m_bSmooth = FALSE;
	CClientDC dc(this);
	m_nCellWidth = dc.GetDeviceCaps(LOGPIXELSX);
	m_nCellHeight = dc.GetDeviceCaps(LOGPIXELSY) / 4;
	m_nRibbonWidth = m_nCellWidth / 2;
	int nWidth = (26 * m_nCellWidth) + m_nRibbonWidth;
	int nHeight = m_nCellHeight * 100;
	SetScrollSizes(MM_TEXT, CSize(nWidth, nHeight));
}

// CScrollAppView drawing

void CScrollAppView::OnDraw(CDC* pdc)
{
	CScrollAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CSize size = GetTotalSize();

	CPen aPen(PS_SOLID, 0, RGB(192, 192, 192));
	CPen* oldPen = pdc->SelectObject(&aPen);

	for (int i = 0; i < 99; i++)
	{
		int y = i * m_nCellHeight + m_nCellHeight;
		pdc->MoveTo(0, y);
		pdc->LineTo(size.cx, y);
	}

	for (int j = 0; j < 26; j++)
	{
		int x = j * m_nCellWidth + m_nRibbonWidth;
		pdc->MoveTo(x, 0);
		pdc->LineTo(x, size.cy);

	}

	pdc->SelectObject(oldPen);

	CBrush aBrush;
	aBrush.CreateStockObject(LTGRAY_BRUSH);

	CRect rcTop(0, 0, size.cx, m_nCellHeight);
	pdc->FillRect(rcTop, &aBrush);

	CRect rcLeft(0, 0, m_nRibbonWidth, size.cy);
	pdc->FillRect(rcLeft, &aBrush);

	pdc->MoveTo(0, m_nCellHeight);
	pdc->LineTo(size.cx, m_nCellHeight);
	pdc->MoveTo(m_nRibbonWidth, 0);
	pdc->LineTo(m_nRibbonWidth, size.cy);
	pdc->SetBkMode(TRANSPARENT);
	// TODO: add draw code for native data here

	for (int i = 0; i < 99; i++) {
		int y = (i * m_nCellHeight) + m_nCellHeight;
		pdc->MoveTo(0, y);
		pdc->LineTo(m_nRibbonWidth, y);
		CString string;
		string.Format(_T("%d"), i + 1);
		CRect rect(0, y, m_nRibbonWidth, y + m_nCellHeight);
		pdc->DrawText(string, &rect, DT_SINGLELINE |
			DT_CENTER | DT_VCENTER);
		rect.top++;
		pdc->Draw3dRect(rect, RGB(255, 255, 255),
			RGB(128, 128, 128));
	}

	for (int j = 0; j < 26; j++) {
		int x = (j * m_nCellWidth) + m_nRibbonWidth;
		pdc->MoveTo(x, 0);
		pdc->LineTo(x, m_nCellHeight);
		CString string;
		string.Format(_T("%c"), j + L'A');
		CRect rect(x, 0, x + m_nCellWidth, m_nCellHeight);
		pdc->DrawText(string, &rect, DT_SINGLELINE |
			DT_CENTER | DT_VCENTER);
		rect.left++;
		pdc->Draw3dRect(rect, RGB(255, 255, 255),
			RGB(128, 128, 128));
	}

	CRect rect;
	pdc->GetClipBox(&rect);
	int nStartRow = max(0, (rect.top - m_nCellHeight) / m_nCellHeight);
	int nEndRow = min(98, (rect.bottom - 1) / m_nCellHeight);
	int nStartCol = max(0, (rect.left - m_nRibbonWidth) / m_nCellWidth);
	int nEndCol = min(25, ((rect.right + m_nCellWidth - 1) -
		m_nRibbonWidth) / m_nCellWidth);
	for (int i = nStartRow; i <= nEndRow; i++)
		for (int j = nStartCol; j <= nEndCol; j++)
			//for (int i = 0; i < 99; i++)
			//	for (int j = 0; j < 26; j++)
			DrawAddress(pdc, i, j);

	DrawPointer(pdc, m_nCurrentRow, m_nCurrentCol, TRUE);
}


// CScrollAppView diagnostics

#ifdef _DEBUG
void CScrollAppView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CScrollAppView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

void CScrollAppView::GetCellRect(int row, int col, LPRECT pRect)
{
	pRect->left = m_nRibbonWidth + (col * m_nCellWidth) + 1;
	pRect->top = m_nCellHeight + (row * m_nCellHeight) + 1;
	pRect->right = pRect->left + m_nCellWidth - 1;
	pRect->bottom = pRect->top + m_nCellHeight - 1;
}

void CScrollAppView::DrawAddress(CDC* pDC, int row, int col)
{
	CRect rect;
	GetCellRect(row, col, &rect);
	CString string;
	string.Format(_T("%c%d"), col + _T('A'), row + 1);
	pDC->SetBkMode(TRANSPARENT);
	CFont * pOldFont = pDC->SelectObject(&m_font);
	pDC->DrawText(string, rect, DT_SINGLELINE | DT_CENTER |
		DT_VCENTER);
	pDC->SelectObject(pOldFont);
}

void CScrollAppView::DrawPointer(CDC* pDC, int row, int col, BOOL bHighlight)
{
	CRect rect;
	GetCellRect(row, col, &rect);
	CBrush brush(bHighlight ? RGB(0, 255, 255) :
		::GetSysColor(COLOR_WINDOW));
	pDC->FillRect(rect, &brush);
	DrawAddress(pDC, row, col);
}

void CScrollAppView::OnLButtonDown(UINT flags, CPoint point)
{
	CScrollView::OnLButtonDown(flags, point);

	CPoint pos = point;
	CClientDC dc(this);
	OnPrepareDC(&dc);
	dc.DPtoLP(&pos);

	CSize size = GetTotalSize();
	if (pos.x > m_nRibbonWidth && pos.x < size.cx &&
		pos.y > m_nCellHeight && pos.y < size.cy) {
		int row = (pos.y - m_nCellHeight) / m_nCellHeight;
		int col = (pos.x - m_nRibbonWidth) / m_nCellWidth;
		ASSERT(row >= 0 && row <= 98 && col >= 0 && col <= 25);
		DrawPointer(&dc, m_nCurrentRow, m_nCurrentCol, FALSE);
		m_nCurrentRow = row;
		m_nCurrentCol = col;
		DrawPointer(&dc, m_nCurrentRow, m_nCurrentCol, TRUE);
	}
}

CScrollAppDoc* CScrollAppView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScrollAppDoc)));
	return (CScrollAppDoc*)m_pDocument;
}
#endif //_DEBUG


// CScrollAppView message handlers
