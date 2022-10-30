#pragma once
#include <afxwin.h>
class MaskedBitmap : public CBitmap
{
public:
	void DrawTransparent(CDC* pDC, int x, int y,
		COLORREF clrTransparency);
	void Draw(CDC* pDC, int x, int y);
};

