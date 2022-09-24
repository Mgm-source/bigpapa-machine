
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "framework.h"
#include "Shapes.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView
const COLORREF CChildView::m_colourTable[3] =
{
	RGB(255,0,0),//Red
	RGB(0,0,255), //Blue
	RGB(0,255,0)//Green
};

CChildView::CChildView() : m_shapes{ shape::Circle } , m_colour {0}, sSize {45}
{
}

CChildView::~CChildView()
{
}

BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_SHAPES_CIRCLE, OnCircle)
	ON_UPDATE_COMMAND_UI(ID_SHAPES_CIRCLE, OnUpdateCircle)
	ON_COMMAND(ID_SHAPES_SQUARE, OnSquare)
	ON_UPDATE_COMMAND_UI(ID_SHAPES_SQUARE, OnUpdateSquare)
	ON_COMMAND(ID_SHAPES_TRIANGLE, OnTriangle)
	ON_UPDATE_COMMAND_UI(ID_SHAPES_TRIANGLE, OnUpdateTriangle)
	ON_COMMAND_RANGE(ID_COLOURS_RED,ID_COLOURS_GREEN, OnColour)
	ON_UPDATE_COMMAND_UI_RANGE(ID_COLOURS_RED, ID_COLOURS_GREEN, OnUpdateColour)
END_MESSAGE_MAP()

// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+2), nullptr);

	return TRUE;
}

void CChildView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rcClient;
	GetClientRect(&rcClient);
	int cx = rcClient.Width() / 2;
	int cy = rcClient.Height() / 2;
	CRect rcShape(cx - sSize, cy - sSize, cx + sSize, cy + sSize);

	CPoint pos = point;
	ScreenToClient(&pos);
	CPoint points[3];
	BOOL bShapeClicked = FALSE;
	int dx, dy;
	// 
	// Hit test the shape. 
	// 
	switch (m_shapes)
	{
	case shape::Circle:
		dx = pos.x - cx;
		dy = pos.y - cy;
		if ((dx * dx) + (dy * dy) <= (sSize * sSize))
		{
			bShapeClicked = TRUE;
		}
		break;
	case shape::Triangle:
		if (rcShape.PtInRect(pos)) {
			dx = min(pos.x - rcShape.left, rcShape.right - pos.x);

			if ((rcShape.bottom - pos.y) < (2 * dx))
			{
				bShapeClicked = TRUE;
			}
		}
		break;
	case shape::Square:
		if (rcShape.PtInRect(pos))
		{
			bShapeClicked = TRUE;
		}
		break;
	}

	// 
	// Display a context menu if the shape was clicked. 
	// 
	if (bShapeClicked) {
		CMenu menu;
		menu.LoadMenu(IDR_CONTEXTMENU);
		CMenu* pContextMenu = menu.GetSubMenu(0);
		for (int i = 0; i < 3; i++)
		{
			pContextMenu->ModifyMenu(ID_COLOURS_RED + i, MF_BYCOMMAND | MF_OWNERDRAW, ID_COLOURS_RED + i);
		}
			
		pContextMenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_LEFTBUTTON | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
		return;
	}
	// 
	// Call the base class if the shape was not clicked. 
	// 
	CWnd::OnContextMenu(pWnd, point);
}

void CChildView::OnPaint() 
{
	CPoint point[3];
	
	CPaintDC dc(this); // device context for painting

	CRect rClient;
	GetClientRect(&rClient);

	int cx = rClient.Width() / 2;
	int cy = rClient.Height() / 2;

	CRect rShape(cx - sSize, cy - sSize, cx + sSize, cy + sSize);
	CBrush brush(m_colourTable[m_colour]);
	CBrush* oldbrush = dc.SelectObject(&brush);

	switch (m_shapes)
	{
	case shape::Circle:
		dc.Ellipse(rShape);
		break;
	case shape::Triangle:
		point[0] = {cx,cy-sSize};
		point[1] = {cx-sSize,cy+sSize};
		point[2] = {cx+sSize,cy+sSize};
		dc.Polygon(point, 3);
		break;
	case shape::Square:
		dc.Rectangle(rShape);
		break;
	}
	dc.SelectObject(oldbrush);
}

void CChildView::OnCircle()
{
	m_shapes = shape::Circle;
	Invalidate();
}

void CChildView::OnTriangle()
{
	m_shapes = shape::Triangle;
	Invalidate();
}

void CChildView::OnSquare()
{
	m_shapes = shape::Square;
	Invalidate();
}

void CChildView::OnUpdateCircle(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_shapes == shape::Circle);
}

void CChildView::OnUpdateTriangle(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_shapes == shape::Triangle);
}

void CChildView::OnUpdateSquare(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_shapes == shape::Square);
}

void CChildView::OnUpdateColour(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck((int)pCmdUI->m_nID - ID_COLOURS_RED == m_colour);
}

void CChildView::OnColour(UINT iD)
{
	m_colour = iD - ID_COLOURS_RED;
	Invalidate();
}

