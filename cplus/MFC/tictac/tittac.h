#pragma once
#include "afxwin.h"

constexpr int EX = 1;
constexpr int OH = 2;

class tittac : public CWinApp
{
	BOOL InitInstance();
};

class CMainWindow : public CWnd
{
protected:
	static const CRect m_tittacsquares[9];
	int m_GameGrid[9];
	int m_nNextChar; // Next character (EX or OH) 

protected:
	int GetRectID(CPoint point);
	void DrawBoard(CDC* pDC);
	void DrawX(CDC* pDC, int nPos);
	void DrawO(CDC* pDC, int nPos);
	void ResetGame();
	void CheckForGameOver();
	int IsWinner();
	BOOL IsDraw();
public:
	CMainWindow();
protected:
	virtual void PostNcDestroy();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
};