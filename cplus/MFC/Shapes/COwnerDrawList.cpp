#include "pch.h"
#include "COwnerDrawList.h"

BOOL COwnerDrawList::PreCreateWindow(CREATESTRUCT&cs)
{
	if (!CListBox::PreCreateWindow(cs))
		return FALSE;

	cs.style &= ~(LBS_OWNERDRAWVARIABLE | LBS_SORT);
	cs.style |= LBS_OWNERDRAWFIXED;
	return TRUE;
}

void COwnerDrawList::MeasureItem(LPMEASUREITEMSTRUCT lpmis)
{
	lpmis->itemHeight = 36;
}

void COwnerDrawList::DrawItem(LPDRAWITEMSTRUCT lpdis)
{
	CDC deviceContext;
	deviceContext.Attach(lpdis->hDC);
	CRect rect = lpdis->rcItem;
	UINT index = lpdis->itemID;
	
	CBrush* pBrush = new CBrush(::GetSysColor((lpdis->itemState & ODS_SELECTED) ? COLOR_HIGHLIGHT : COLOR_WINDOW));
	deviceContext.FillRect(rect, pBrush);
	
	delete pBrush;

	if (lpdis->itemState * ODS_FOCUS)
		deviceContext.DrawFocusRect(rect);
	if (index != (UINT)-1)
	{
		deviceContext.DrawIcon(rect.left + 4, rect.top + 2,
			(HICON)GetItemData(index));
	}
	deviceContext.Detach();
}

int COwnerDrawList::AddIcon(HICON hIcon)
{
	int nIndex = AddString(_T(""));
	if ((nIndex != LB_ERR) && (nIndex != LB_ERRSPACE))
		SetItemData(nIndex, (DWORD)hIcon);
	return nIndex;
}

void COwnerDrawList::projectImage(CDC* pdc, LPRECT pRect, COLORREF bckgndclr)
{
	CDC dcMem;
	dcMem.CreateCompatibleDC(pdc);
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(pdc, 32, 32);
	CBitmap* pOldBitmap = dcMem.SelectObject(&bitmap);
	CBrush* pBrush = new CBrush(bckgndclr);
	dcMem.FillRect(CRect(0, 0, 32, 32), pBrush);
	delete pBrush;
	int nIndex = GetCurSel();
	if (nIndex != LB_ERR)
		dcMem.DrawIcon(0, 0, (HICON)GetItemData(nIndex));
	pdc->StretchBlt(pRect->left, pRect->top, pRect->right - pRect->left,
		pRect->bottom - pRect->top, &dcMem, 0, 0, 32, 32, SRCCOPY);
	dcMem.SelectObject(pOldBitmap);
}
