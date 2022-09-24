
// ChildView.h : interface of the CChildView class
//


#pragma once


// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:
	static const COLORREF m_colourTable[3];
protected:
	enum class shape 
	{
		Circle,
		Square,
		Triangle
	} m_shapes;

	int m_colour;
	int sSize;
// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	afx_msg void OnCircle();
	afx_msg void OnTriangle();
	afx_msg void OnSquare();
	afx_msg void OnColour(UINT iD);
	afx_msg void OnUpdateCircle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTriangle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSquare(CCmdUI* pCmdUI);
	afx_msg void OnUpdateColour(CCmdUI* pCmdUI);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

