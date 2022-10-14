#include "pch.h"
#include "MainFrm2.h"

IMPLEMENT_DYNAMIC(CMainFrame2, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame2, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_MESSAGE(WM_USER_APPLY, OnApply)
	ON_MESSAGE(WM_USER_DIALOG_DESTROYED, OnDialogDestroyed)
END_MESSAGE_MAP()

CMainFrame2::CMainFrame2() noexcept
{
}

BOOL CMainFrame2::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

BOOL CMainFrame2::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

CMainFrame2::~CMainFrame2()
{
}

void CMainFrame2::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame2::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

int CMainFrame2::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
		return -1;
	return 0;
}

void CMainFrame2::OnSetFocus(CWnd* pOldWnd)
{
	// forward focus to the view window 
	m_wndView.SetFocus();
}

LRESULT CMainFrame2::OnApply(WPARAM wParam, LPARAM lParam)
{
	m_wndView.SendMessage(WM_USER_APPLY, wParam, lParam);
	return 0;
}

LRESULT CMainFrame2::OnDialogDestroyed(WPARAM wParam, LPARAM lParam)
{
	m_wndView.SendMessage(WM_USER_DIALOG_DESTROYED, wParam, lParam);
	return 0;
}
