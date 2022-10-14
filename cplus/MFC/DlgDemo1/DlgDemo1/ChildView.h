
// ChildView.h : interface of the CChildView class
//


#pragma once
#include "MyCDialog.h"

// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:
protected:
	MyCDialog* _pDlg;
	int _unit; 
	int _height;
	int _width;

// Overrides
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	afx_msg void OnFileOptions();
	afx_msg LRESULT OnApply(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDialogDestroyed(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

