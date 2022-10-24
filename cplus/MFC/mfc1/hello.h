#pragma once
#include "COwnerDrawList.h"

class CMyApp : public CWinApp {
public:
	BOOL InitInstance() override;
};

class CMainWindow : public CFrameWnd {
	int m_cxChar;
	int m_cyChar;
	CFont m_font;
	CRect m_rcImage;
	CButton m_wndGroupBox;
	COwnerDrawList m_wndDrawListBox;
	CStatic m_wndLabel;
	CPalette palette;
public: 
	CMainWindow();
	void DoGradientFill(CDC* pdc, LPRECT rect);
	void DoDrawText(CDC* pdc, LPRECT rect);
protected:
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
	afx_msg int OnCreate(LPCREATESTRUCT);
	afx_msg void OnSetFocus(CWnd* pWnd);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnSelChange();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	DECLARE_MESSAGE_MAP();
private:
	bool m_bMouseOver;
};