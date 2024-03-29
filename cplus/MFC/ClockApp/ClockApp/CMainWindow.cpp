#include "CMainWindow.h"
#include "resource.h"

BEGIN_MESSAGE_MAP(CMainWindow, CFrameWnd)
    ON_WM_CREATE()
    ON_WM_PAINT()
    ON_WM_TIMER()
    ON_WM_GETMINMAXINFO()
    ON_WM_NCHITTEST()
    ON_WM_SYSCOMMAND()
    ON_WM_CONTEXTMENU()
    ON_WM_ENDSESSION()
    ON_WM_CLOSE()
END_MESSAGE_MAP()

const CPoint CMainWindow::clockface[12] = {
 CPoint(0, 450), // 12 o'clock 
 CPoint(225, 390), // 1 o'clock 
 CPoint(390, 225), // 2 o'clock 
 CPoint(450, 0), // 3 o'clock 
 CPoint(390, -225), // 4 o'clock 
 CPoint(225, -390), // 5 o'clock 
 CPoint(0, -450), // 6 o'clock 
 CPoint(-225, -390), // 7 o'clock
 CPoint(-390, -225), // 8 o'clock 
 CPoint(-450, 0), // 9 o'clock 
 CPoint(-390, 225), // 10 o'clock 
 CPoint(-225, 390), // 11 o'clock 
};

void CMainWindow::DrawClockFace(CDC* pDC)
{

    pDC->SelectStockObject(NULL_BRUSH);
    for (int i = 0; i < 12; i++)
        pDC->Rectangle(clockface[i].x - SQUARESIZE,
            clockface[i].y + SQUARESIZE, clockface[i].x + SQUARESIZE,
            clockface[i].y - SQUARESIZE);
}

void CMainWindow::DrawSecondHand(CDC* pDC, int nLength, int nScale, int nDegrees, COLORREF clrColor)
{
    CPoint point[2];
    double nRadians = (double)nDegrees * 0.017453292;
    point[0].x = (int)(nLength * sin(nRadians));
    point[0].y = (int)(nLength * cos(nRadians));
    point[1].x = -point[0].x / nScale;
    point[1].y = -point[0].y / nScale;
    CPen pen(PS_SOLID, 0, clrColor);
    CPen* pOldPen = pDC->SelectObject(&pen);
    pDC->MoveTo(point[0]);
    pDC->LineTo(point[1]);
    pDC->SelectObject(pOldPen);
}

void CMainWindow::DrawHand(CDC* pDC, int nLength, int nScale, int nDegrees, COLORREF clrColor)
{
    CPoint point[4];
    double nRadians = (double)nDegrees * 0.017453292;
    point[0].x = (int)(nLength * sin(nRadians));
    point[0].y = (int)(nLength * cos(nRadians));
    point[2].x = -point[0].x / nScale;
    point[2].y = -point[0].y / nScale;
    point[1].x = -point[2].y;
    point[1].y = point[2].x;
    point[3].x = -point[1].x;
    point[3].y = -point[1].y;
    CPen pen(PS_SOLID, 0, clrColor);
    CPen* pOldPen = pDC->SelectObject(&pen);
    pDC->MoveTo(point[0]);
    pDC->LineTo(point[1]);
    pDC->LineTo(point[2]);
    pDC->LineTo(point[3]);
    pDC->LineTo(point[0]);
    pDC->SelectObject(pOldPen);
}

void CMainWindow::SetTitleBarState()
{
    CMenu* pMenu = GetSystemMenu(FALSE);
    if (fullWindow) {
        ModifyStyle(WS_CAPTION, 0);
        pMenu->ModifyMenu(ID_SYSMENU_FULLSCREEN,
            MF_STRING,
            ID_SYSMENU_FULLSCREEN, _T("Restore &Title"));
    }
    else {
        ModifyStyle(0, WS_CAPTION);
        pMenu->ModifyMenu(ID_SYSMENU_FULLSCREEN,
            MF_STRING,
            ID_SYSMENU_FULLSCREEN, _T("Remove &Title"));
    }
    SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE |
        SWP_NOZORDER | SWP_DRAWFRAME);
}

void CMainWindow::SetTopMostState()
{
    CMenu* pMenu = GetSystemMenu(FALSE);
    if (stayOnTop) {
        SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE |
            SWP_NOSIZE);
        pMenu->CheckMenuItem(ID_SYSMENU_STAYONTOP,
            MF_CHECKED);
    }
    else {
        SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE |
            SWP_NOSIZE);
        pMenu->CheckMenuItem(ID_SYSMENU_STAYONTOP,
            MF_UNCHECKED);
    }
}

void CMainWindow::SaveWindowState()
{
    CString version = _T("Version 1.0");
    AfxGetApp()->WriteProfileInt(version, _T("FullWindow"), fullWindow);
    AfxGetApp()->WriteProfileInt(version, _T("StayOnTop"), stayOnTop);
    WINDOWPLACEMENT wp;
    wp.length = sizeof(WINDOWPLACEMENT);
    GetWindowPlacement(&wp);
    AfxGetApp()->WriteProfileInt(version, _T("flags"), wp.flags);
    AfxGetApp()->WriteProfileInt(version, _T("showCmd"), wp.showCmd);
    AfxGetApp()->WriteProfileInt(version, _T("x1"), wp.rcNormalPosition.left);
    AfxGetApp()->WriteProfileInt(version, _T("y1"), wp.rcNormalPosition.top);
    AfxGetApp()->WriteProfileInt(version, _T("x2"), wp.rcNormalPosition.right);
    AfxGetApp()->WriteProfileInt(version, _T("y2"), wp.rcNormalPosition.bottom);
}

void CMainWindow::UpdateSystemMenu(CMenu* pMenu)
{
    static UINT nState[2][5] = { { MFS_GRAYED, MFS_ENABLED, MFS_ENABLED, MFS_ENABLED, MFS_DEFAULT },
                                 { MFS_DEFAULT, MFS_GRAYED, MFS_GRAYED, MFS_ENABLED, MFS_GRAYED } };
    if (IsIconic()) // Shouldn't happen, but let's be safe
        return;

    int i = 0;
    if (IsZoomed())
        i = 1;
    CString strMenuText;
    pMenu->GetMenuString(SC_RESTORE, strMenuText,
        MF_BYCOMMAND);
    pMenu->ModifyMenu(SC_RESTORE, MF_STRING | nState[i][0],
        SC_RESTORE,
        strMenuText);
    pMenu->GetMenuString(SC_MOVE, strMenuText,
        MF_BYCOMMAND);
    pMenu->ModifyMenu(SC_MOVE, MF_STRING | nState[i][1],
        SC_MOVE,
        strMenuText);
    pMenu->GetMenuString(SC_SIZE, strMenuText, MF_BYCOMMAND);
    pMenu->ModifyMenu(SC_SIZE, MF_STRING | nState[i][2], SC_SIZE,
        strMenuText);
    pMenu->GetMenuString(SC_MINIMIZE, strMenuText,
        MF_BYCOMMAND);
    pMenu->ModifyMenu(SC_MINIMIZE, MF_STRING | nState[i][3],
        SC_MINIMIZE,
        strMenuText);
    pMenu->GetMenuString(SC_MAXIMIZE, strMenuText,
        MF_BYCOMMAND);
    pMenu->ModifyMenu(SC_MAXIMIZE, MF_STRING | nState[i][4],
        SC_MAXIMIZE,
        strMenuText);
    SetMenuDefaultItem(pMenu->m_hMenu, i ? SC_RESTORE :SC_MAXIMIZE, FALSE);
}

CMainWindow::CMainWindow() : fullWindow { FALSE }, stayOnTop { FALSE }
{
    m_bAutoMenuEnable = FALSE;
    CTime time = CTime::GetCurrentTime();
    m_nPrevSecond = time.GetSecond();
    m_nPrevMinute = time.GetMinute();
    m_nPrevHour = time.GetHour() % 12;

    CString strWndClass = AfxRegisterWndClass( CS_HREDRAW | CS_VREDRAW, AfxGetApp()->LoadStandardCursor(IDC_ARROW),
        (HBRUSH)(COLOR_3DFACE + 1), AfxGetApp()->LoadIcon(IDI_APPLICATION));

    Create(strWndClass, _T("Clock"));
}

BOOL CMainWindow::PreCreateWindow(CREATESTRUCT& cs)
{
    if (!CFrameWnd::PreCreateWindow(cs))
        return FALSE;
    cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
    return TRUE;
}

BOOL CMainWindow::RestoreWindowState()
{
    CString version = _T("Version 1.0");
    fullWindow = AfxGetApp()->GetProfileInt(version, _T("FullWindow"), 0);
    SetTitleBarState();
    stayOnTop = AfxGetApp()->GetProfileInt(version, _T("StayOnTop"), 0);
    SetTopMostState();
    WINDOWPLACEMENT wp;
    wp.length = sizeof(WINDOWPLACEMENT);

    GetWindowPlacement(&wp);
    if (((wp.flags =
        AfxGetApp()->GetProfileInt(version, _T("flags"), -1)) != -1) &&
        ((wp.showCmd =
            AfxGetApp()->GetProfileInt(version, _T("showCmd"), -1)) != -1) &&
        ((wp.rcNormalPosition.left =
            AfxGetApp()->GetProfileInt(version, _T("x1"), -1)) != -1) &&
        ((wp.rcNormalPosition.top =
            AfxGetApp()->GetProfileInt(version, _T("y1"), -1)) != -1) &&
        ((wp.rcNormalPosition.right =
            AfxGetApp()->GetProfileInt(version, _T("x2"), -1)) != -1) &&
        ((wp.rcNormalPosition.bottom =
            AfxGetApp()->GetProfileInt(version, _T("y2"), -1)) != -1)) {
        wp.rcNormalPosition.left = min(wp.rcNormalPosition.left,
            ::GetSystemMetrics(SM_CXSCREEN) -
            ::GetSystemMetrics(SM_CXICON));
        wp.rcNormalPosition.top = min(wp.rcNormalPosition.top,
            ::GetSystemMetrics(SM_CYSCREEN) -
            ::GetSystemMetrics(SM_CYICON));
        SetWindowPlacement(&wp);
        return TRUE;
    }
    return FALSE;
}

int CMainWindow::OnCreate(LPCREATESTRUCT lpcs)
{
    if (CFrameWnd::OnCreate(lpcs) == -1)
        return -1;

    // Set a timer to fire at 1-second intervals.

    if (!SetTimer(ID_TIMER_CLOCK, 1000, NULL)) {
        MessageBox(_T("SetTimer failed"), _T("Error"),
            MB_ICONSTOP | MB_OK);
        return -1;
    }

    CMenu* pMenu = GetSystemMenu(FALSE);
    pMenu->AppendMenu(MF_SEPARATOR);
    pMenu->AppendMenu(MF_STRING,
        ID_SYSMENU_FULLSCREEN,
        _T("Remove &Title"));
    pMenu->AppendMenu(MF_STRING,
        ID_SYSMENU_STAYONTOP,
        _T("Stay on To&p"));

    return 0;
}

void CMainWindow::OnGetMinMaxInfo(MINMAXINFO* pMMI)
{
    pMMI->ptMinTrackSize.x = 120;
    pMMI->ptMinTrackSize.y = 120;
}

void CMainWindow::OnTimer(UINT_PTR nTimerID)
{
    // 
// Do nothing if the window is minimized. 
// 
    if (IsIconic())
        return;
    // 
    // Get the current time and do nothing if it hasn't changed. 
    // 
    CTime time = CTime::GetCurrentTime();
    int nSecond = time.GetSecond();
    int nMinute = time.GetMinute();
    int nHour = time.GetHour() % 12;
    if ((nSecond == m_nPrevSecond) &&
        (nMinute == m_nPrevMinute) &&
        (nHour == m_nPrevHour))
        return;
    // 
    // Center the origin and switch to the MM_ISOTROPIC mapping mode. 
    // 
    CRect rect;
    GetClientRect(&rect);
    CClientDC dc(this);
    dc.SetMapMode(MM_ISOTROPIC);
    dc.SetWindowExt(1000, 1000);
    dc.SetViewportExt(rect.Width(), -rect.Height());
    dc.SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
    // 
 // If minutes have changed, erase the hour and minute hands. 
 // 
    COLORREF clrColor = ::GetSysColor(COLOR_3DFACE);
    if (nMinute != m_nPrevMinute) {
        DrawHand(&dc, 200, 4, (m_nPrevHour * 30) + (m_nPrevMinute / 2),
            clrColor);
        DrawHand(&dc, 400, 8, m_nPrevMinute * 6, clrColor);
        m_nPrevMinute = nMinute;
        m_nPrevHour = nHour;
    }
    // 
    // If seconds have changed, erase the second hand and redraw all hands. 
    // 
    if (nSecond != m_nPrevSecond) {
        DrawSecondHand(&dc, 400, 8, m_nPrevSecond * 6, clrColor);
        DrawSecondHand(&dc, 400, 8, nSecond * 6, RGB(0, 0, 0));
        DrawHand(&dc, 200, 4, (nHour * 30) + (nMinute / 2),
            RGB(0, 0, 0));
        DrawHand(&dc, 400, 8, nMinute * 6, RGB(0, 0, 0));
        m_nPrevSecond = nSecond;
    }

}

void CMainWindow::OnPaint()
{
    CRect rect;
    GetClientRect(&rect);
    CPaintDC dc(this);
    dc.SetMapMode(MM_ISOTROPIC);
    dc.SetWindowExt(1000, 1000);
    dc.SetViewportExt(rect.Width(), -rect.Height());
    dc.SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
    DrawClockFace(&dc);
    DrawHand(&dc, 200, 4, (m_nPrevHour * 30) +
        (m_nPrevMinute / 2), RGB(0, 0, 0));
    DrawHand(&dc, 400, 8, m_nPrevMinute * 6, RGB(0, 0, 0));
    DrawSecondHand(&dc, 400, 8, m_nPrevSecond * 6, RGB(0, 0, 0));
}

LRESULT CMainWindow::OnNcHitTest(CPoint point)
{
    LRESULT nHitTest = CFrameWnd::OnNcHitTest(point);
    if ((nHitTest == HTCLIENT) && (::GetAsyncKeyState(MK_LBUTTON) < 0))
        nHitTest = HTCAPTION;
    return nHitTest;
}

void CMainWindow::OnSysCommand(UINT nID, LPARAM lParam)
{

    if (nID == ID_SYSMENU_FULLSCREEN) {
        fullWindow = fullWindow ? 0 : 1;
        SetTitleBarState();
        return;
    }
    else if (nID == ID_SYSMENU_STAYONTOP) {
        stayOnTop = stayOnTop ? 0 : 1;
        SetTopMostState();
        return;
    }

    CFrameWnd::OnSysCommand(nID, lParam);
}

void CMainWindow::OnContextMenu(CWnd* pWnd, CPoint point)
{
    CRect rect;
    GetClientRect(&rect);
    ClientToScreen(&rect);
    if (rect.PtInRect(point)) {
        CMenu* pMenu = GetSystemMenu(FALSE);
        UpdateSystemMenu(pMenu);
        int nID = (int)pMenu->TrackPopupMenu(TPM_LEFTALIGN |
            TPM_LEFTBUTTON | TPM_RIGHTBUTTON | TPM_RETURNCMD,
            point.x,
            point.y, this);
        if (nID > 0)
            SendMessage(WM_SYSCOMMAND, nID, 0);
        return;
    }
    CFrameWnd::OnContextMenu(pWnd, point);
}

void CMainWindow::OnEndSession(BOOL bEnding)
{
    if (bEnding)
        SaveWindowState();
    CFrameWnd::OnEndSession(bEnding);
}

void CMainWindow::OnClose()
{
    SaveWindowState();
    KillTimer(ID_TIMER_CLOCK);
    CFrameWnd::OnClose();
}
