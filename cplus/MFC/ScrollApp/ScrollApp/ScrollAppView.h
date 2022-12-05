
// ScrollAppView.h : interface of the CScrollAppView class
//

#pragma once


class CScrollAppView : public CScrollView
{
protected: // create from serialization only
	CScrollAppView() noexcept;
	DECLARE_DYNCREATE(CScrollAppView)

// Attributes
public:
	CScrollAppDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
protected:

// Implementation
public:
	virtual ~CScrollAppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	BOOL m_bSmooth;
	void GetCellRect(int row, int col, LPRECT pRect);
	void DrawAddress(CDC* pDC, int row, int col);
	void DrawPointer(CDC* pDC, int row, int col, BOOL bHighlight);
	CFont m_font;
	int m_nCurrentCol;
	int m_nCurrentRow;
	int m_nRibbonWidth;
	int m_nCellHeight;
	int m_nCellWidth;
// Generated message map functions
protected:
	afx_msg void OnLButtonDown(UINT flags, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ScrollAppView.cpp
inline CScrollAppDoc* CScrollAppView::GetDocument() const
   { return reinterpret_cast<CScrollAppDoc*>(m_pDocument); }
#endif

