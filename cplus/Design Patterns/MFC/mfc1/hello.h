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
	DECLARE_MESSAGE_MAP();
};