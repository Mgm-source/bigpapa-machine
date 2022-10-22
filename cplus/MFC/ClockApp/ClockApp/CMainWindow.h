#pragma once
#include <afxwin.h>

constexpr auto SQUARESIZE = 20;
constexpr auto ID_TIMER_CLOCK = 1;

class CMainWindow : public CFrameWnd
{
protected:
	BOOL fullWindow;
	BOOL stayOnTop;
	int m_nPrevSecond;
	int m_nPrevMinute;
	int m_nPrevHour;
	void DrawClockFace(CDC* pDC);
	void DrawSecondHand(CDC* pDC, int nLength, int nScale, int nDegrees, COLORREF clrColor);
	void DrawHand(CDC* pDC, int nLength, int nScale, int nDegrees,
		COLORREF clrColor);
	void SetTitleBarState();
	void SetTopMostState();
	void SaveWindowState();
	void UpdateSystemMenu(CMenu* pMenu);
	const static CPoint clockface[];
public:
	CMainWindow();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	BOOL RestoreWindowState();
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpcs);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* pMMI);
	afx_msg void OnTimer(UINT_PTR nTimerID);
	afx_msg void OnPaint();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEndSession(BOOL bEnding);
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
};

