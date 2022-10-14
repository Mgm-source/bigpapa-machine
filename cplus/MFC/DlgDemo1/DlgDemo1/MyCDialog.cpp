// MyCDialog.cpp : implementation file
//

#include "pch.h"
#include "DlgDemo1.h"
#include "MyCDialog.h"


// MyCDialog dialog

IMPLEMENT_DYNAMIC(MyCDialog, CDialog)

MyCDialog::MyCDialog(CWnd* pParent /*=nullptr*/) : _width{ 0 }, _height{ 0 }, _unit{ -1 },
CDialog(MyCDialog::IDD, pParent)
{

}

MyCDialog::~MyCDialog()
{
}

void MyCDialog::OnOK()
{
	UpdateData(TRUE);
	RECTPROP rp;
	rp.nWidth = _width;
	rp.nHeight = _height;
	rp.nUnits = _unit;

	AfxGetMainWnd()->SendMessage(WM_USER_APPLY, 0, (LPARAM)&rp);
}

void MyCDialog::OnCancel()
{
	DestroyWindow();
}

void MyCDialog::PostNcDestroy()
{
	CDialog::PostNcDestroy();
	AfxGetMainWnd()->SendMessage (WM_USER_DIALOG_DESTROYED, 0, 0);
	delete this;
}

void MyCDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, _width);
	DDV_MinMaxInt(pDX, _width, 1, 128);
	DDX_Text(pDX, IDC_EDIT2, _height);
	DDX_Radio(pDX, IDC_RADIO1, _unit);

}


BEGIN_MESSAGE_MAP(MyCDialog, CDialog)
	ON_BN_CLICKED(IDC_RESET_BUTTON, &MyCDialog::OnReset)
END_MESSAGE_MAP()


// MyCDialog message handlers


void MyCDialog::OnReset()
{
	_width = 4;
	_height = 2;
	_unit = 0;
	UpdateData(FALSE);
}
