#pragma once
#include <afxwin.h>

constexpr int LINESIZE = 8;

class CMainWindow : public CFrameWnd
{
protected:
	int m_nCellWidth; // Cell width in pixels 
	int m_nCellHeight; // Cell height in pixels 

	int m_nRibbonWidth; // Ribbon width in pixels 
	int m_nHPageSize; // Horizontal page size 
	int m_nVPageSize; // Vertical page size
	int m_nViewWidth; // Workspace width in pixels 
	int m_nViewHeight; // Workspace height in pixels 

	int m_nHScrollPos; // Horizontal scroll position 
	int m_nVScrollPos; // Vertical scroll position 
public:
	CMainWindow();
protected:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT type, int cx, int cy);
	afx_msg void OnHScroll(UINT type, UINT pos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT type, UINT pos, CScrollBar* pScrollBar);
	DECLARE_MESSAGE_MAP();
};