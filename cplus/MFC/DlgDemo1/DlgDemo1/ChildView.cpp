
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "framework.h"
#include "DlgDemo1.h"
#include "ChildView.h"
#include "MyCDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView() : _width{ 4 }, _height{ 2 }, _unit{ 0 }, _pDlg{nullptr}
{

}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_FILE_OPTIONS,OnFileOptions)
	ON_MESSAGE(WM_USER_APPLY, OnApply)
	ON_MESSAGE(WM_USER_DIALOG_DESTROYED, OnDialogDestroyed)
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CBrush brush(RGB(255, 0, 255));
	CBrush* pOldBrush = dc.SelectObject(&brush);
	switch (_unit) {
	case 0: // Inches. 
		dc.SetMapMode(MM_LOENGLISH);
		dc.Rectangle(0, 0, _width * 100, -_height * 100);
		break;
	case 1: // Centimeters. 
		dc.SetMapMode(MM_LOMETRIC);
		dc.Rectangle(0, 0, _width * 100, -_height * 100);
		break;
	case 2: // Pixels. 
		dc.SetMapMode(MM_TEXT);
		dc.Rectangle(0, 0, _width, _height);
		break;
	}
	dc.SelectObject(pOldBrush);
}

void CChildView::OnFileOptions()
{
	
	if (_pDlg)
	{
		_pDlg->SetFocus();
	}
	else 
	{
		_pDlg = new MyCDialog;
		_pDlg->_width;
		_pDlg->_height;
		_pDlg->_unit;
		_pDlg->Create(IDD_OPTIONS);
		_pDlg->ShowWindow(SW_SHOW);
	}

	//MyCDialog dlg;

	//if (dlg.DoModal() == IDOK)
	//{
	//	_unit = dlg._unit;
	//	_width = dlg._width;
	//	_height = dlg._height;
	//	Invalidate();
	//}

}

LRESULT CChildView::OnApply(WPARAM wParam, LPARAM lParam)
{
	RECTPROP* prp = (RECTPROP*)lParam;
	_width = prp->nWidth;
	_height = prp->nHeight;
	_unit = prp->nUnits;
	Invalidate();
	return 0;
}

LRESULT CChildView::OnDialogDestroyed(WPARAM wParam, LPARAM lParam)
{
	_pDlg = NULL;
	return 0;
}
