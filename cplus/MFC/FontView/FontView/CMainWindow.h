#pragma once
#include <afxwin.h>

constexpr auto IDC_PRINT = 100;
constexpr auto IDC_CHECKBOX = 101;
constexpr auto IDC_LISTBOX = 102;
constexpr auto IDC_SAMPLE = 103;

class CMainWindow : public CWnd
{
public:
	CMainWindow();
	static int CALLBACK EnumFontFamProc(ENUMLOGFONT* lpelf,
		NEWTEXTMETRIC* lpntm, int nFontType, LPARAM lParam);
protected:
	int m_cxChar;
	int m_cyChar;
	CFont m_fontMain;
	CFont m_fontSample;
	CStatic m_wndLBTitle;
	CListBox m_wndListBox;
	CButton m_wndCheckBox;
	CButton m_wndGroupBox;
	CStatic m_wndSampleText;
	CButton m_wndPushButton;
	
protected:
	void FillListBox();
	virtual void PostNcDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpcs);
	afx_msg void OnPushButtonClicked();
	afx_msg void OnCheckBoxClicked();
	afx_msg void OnSelChange();
	DECLARE_MESSAGE_MAP()
};

