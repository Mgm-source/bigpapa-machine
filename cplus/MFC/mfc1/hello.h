#pragma once

class CMyApp : public CWinApp {
public:
	BOOL InitInstance() override;
};

class CMainWindow : public CFrameWnd {

public: 
	CMainWindow();
protected:
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP();
private:
	bool m_bMouseOver;
};