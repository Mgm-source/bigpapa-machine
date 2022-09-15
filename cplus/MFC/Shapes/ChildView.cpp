
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

CChildView::CChildView() : m_shapes{ shape::Circle }
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_SHAPES_CIRCLE,OnCircle)
	ON_UPDATE_COMMAND_UI(ID_SHAPES_CIRCLE,OnUpdateCircle)
	ON_COMMAND(ID_SHAPES_SQUARE,OnSquare)
	ON_UPDATE_COMMAND_UI(ID_SHAPES_SQUARE, OnUpdateSquare)
	ON_COMMAND(ID_SHAPES_TRIANGLE,OnTriangle)
	ON_UPDATE_COMMAND_UI(ID_SHAPES_TRIANGLE, OnUpdateTriangle)
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

void CChildView::OnPaint() 
{
	CPoint point[3];
	
	CPaintDC dc(this); // device context for painting

	CRect rClient;
	GetClientRect(&rClient);

	int cx = rClient.Width() / 2;
	int cy = rClient.Height() / 2;
	int sSize = 405;

	CRect rShape(cx - sSize, cy - sSize, cx + sSize, cy + sSize);

	CBrush brush(RGB(255, 0, 0));
	CBrush* oldbrush = dc.SelectObject(&brush);

	switch (m_shapes)
	{
	case shape::Circle:
		dc.Ellipse(rShape);
		break;
	case shape::Triangle:
		point[0] = {cx-sSize,cy+sSize};
		point[1] = {cx,cy-sSize};
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

