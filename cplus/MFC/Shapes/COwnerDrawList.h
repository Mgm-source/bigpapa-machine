#pragma once
#include <afxwin.h>
class COwnerDrawList : public CListBox
{
public:
	BOOL PreCreateWindow(CREATESTRUCT&) override;
	void MeasureItem(LPMEASUREITEMSTRUCT) override;
	void DrawItem(LPDRAWITEMSTRUCT) override;
	int AddIcon(HICON hIcon);
	void projectImage(CDC* pdc, LPRECT pRect, COLORREF bckgndclr);
};

