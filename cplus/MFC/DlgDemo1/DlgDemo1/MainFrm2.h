#pragma once
#include <afxwin.h>
#include "ChildView.h"
class CMainFrame2 : public CFrameWnd
{
public:
	CMainFrame2() noexcept;
protected:
	DECLARE_DYNAMIC(CMainFrame2)

		// Attributes
public:

	// Operations
public:

	// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

	// Implementation
public:
	virtual ~CMainFrame2();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	CChildView    m_wndView;

	// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg LRESULT OnApply(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDialogDestroyed(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

