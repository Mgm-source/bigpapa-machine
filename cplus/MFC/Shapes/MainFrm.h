
// MainFrm.h : interface of the CMainFrame class
//

#pragma once
#include "ChildView.h"

class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame() noexcept;
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
	BOOL PreCreateWindow(CREATESTRUCT& cs) override;
	BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) override;

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar    m_wndStatusBar;
	CChildView    m_wndView;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnMeasureItem(int ctrlID, LPMEASUREITEMSTRUCT lpms);
	afx_msg void OnDrawItem(int ctrlID, LPDRAWITEMSTRUCT lpds);
	DECLARE_MESSAGE_MAP()

};


