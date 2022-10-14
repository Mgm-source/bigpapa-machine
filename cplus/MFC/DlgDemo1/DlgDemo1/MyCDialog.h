#pragma once
#include "afxdialogex.h"
#include "resource.h"  

// MyCDialog dialog

class MyCDialog : public CDialog
{
	DECLARE_DYNAMIC(MyCDialog)

public:
	MyCDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~MyCDialog();
	virtual void OnOK();
	virtual void OnCancel();
	virtual void PostNcDestroy();
// Data members
public:
	enum { IDD = IDD_OPTIONS };

	int _unit;
	int _height;
	int _width;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnReset();
};
