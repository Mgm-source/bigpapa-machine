
// ChildView.cpp : implementation of the CFileView class
//

#include "pch.h"
#include "framework.h"
#include "WinDir.h"
#include "FileView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFileView

IMPLEMENT_DYNCREATE(CFileView, CListView)

CFileView::CFileView()
{
}

CFileView::~CFileView()
{
}

BEGIN_MESSAGE_MAP(CFileView, CListView)
	ON_WM_DESTROY()
	ON_NOTIFY_REFLECT(LVN_GETDISPINFO, OnGetDispInfo)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnClick)
	ON_COMMAND(ID_VIEW_LARGE_ICONS, OnViewLargeIcons)
	ON_COMMAND(ID_VIEW_SMALL_ICONS, OnViewSmallIcons)
	ON_COMMAND(ID_VIEW_LIST, OnViewList)
	ON_COMMAND(ID_VIEW_DETAILS, OnViewDetails)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LARGE_ICONS, OnUpdateViewLargeIcons)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SMALL_ICONS, OnUpdateViewSmallIcons)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LIST, OnUpdateViewList)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DETAILS, OnUpdateViewDetails)
	ON_COMMAND(ID_FILE_NEW_DIR, OnFileNewDirectory)
END_MESSAGE_MAP()

void CFileView::OnDestroy()
{
	FreeItemMemory();
	CListView::OnDestroy();
}

void CFileView::FreeItemMemory()
{
	GetListCtrl().DeleteAllItems();
	int a = GetListCtrl().GetItemCount();
}

void CFileView::OnViewLargeIcons()
{
	ModifyStyle(LVS_TYPEMASK, LVS_ICON);
}

void CFileView::OnViewSmallIcons()
{
	ModifyStyle(LVS_TYPEMASK, LVS_SMALLICON);
}

void CFileView::OnViewList()
{
	ModifyStyle(LVS_TYPEMASK, LVS_LIST);
}

void CFileView::OnViewDetails()
{
	ModifyStyle(LVS_TYPEMASK, LVS_REPORT);
}

void CFileView::OnUpdateViewLargeIcons(CCmdUI* pCmdUI)
{
	DWORD dwCurrentStyle = GetStyle() & LVS_TYPEMASK;
	pCmdUI->SetRadio(dwCurrentStyle == LVS_ICON);
}

void CFileView::OnUpdateViewSmallIcons(CCmdUI* pCmdUI)
{
	DWORD dwCurrentStyle = GetStyle() & LVS_TYPEMASK;
	pCmdUI->SetRadio(dwCurrentStyle == LVS_SMALLICON);
}

void CFileView::OnUpdateViewList(CCmdUI* pCmdUI)
{
	DWORD dwCurrentStyle = GetStyle() & LVS_TYPEMASK;
	pCmdUI->SetRadio(dwCurrentStyle == LVS_LIST);
}

void CFileView::OnUpdateViewDetails(CCmdUI* pCmdUI)
{
	DWORD dwCurrentStyle = GetStyle() & LVS_TYPEMASK;
	pCmdUI->SetRadio(dwCurrentStyle == LVS_REPORT);
}

void CFileView::OnFileNewDirectory()
{
	Refresh(L"C:\\Development\\Mgm-source\\bigpapa-machine");
}


// CFileView message handlers

int CFileView::CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	ITEMINFO* pItem1 = (ITEMINFO*)lParam1;
	ITEMINFO* pItem2 = (ITEMINFO*)lParam2;
	int nResult = 0;
	switch (lParamSort) {
	case 0: // File name. 
		nResult = pItem1->strFileName.CompareNoCase(pItem2->strFileName);
		break;
	case 1: // File size. 
		nResult = pItem1->nFileSizeLow - pItem2->nFileSizeLow;
		break;
	case 2: // Date and datetime. 
		nResult = ::CompareFileTime(&pItem1->ftLastWriteTime, &pItem2->ftLastWriteTime);
		break;
	}
	return nResult;
}

void CFileView::OnDraw(CDC* pDC)
{
}

int CFileView::Refresh(LPCTSTR pszPath)
{
	CString strPath = pszPath;
	if (strPath.Right(1) != _T("\\"))
		strPath += _T("\\");
	strPath += _T("*.*");
	HANDLE hFind;
	WIN32_FIND_DATA fd;
	int nCount = 0;
	if ((hFind = ::FindFirstFile(strPath, &fd)) !=
		INVALID_HANDLE_VALUE) {
		// 
		// Delete existing items (if any). 
		// 
		GetListCtrl().DeleteAllItems();

		// 
		// Show the path name in the frame window's title bar. 
		// 
		TCHAR szFullPath[MAX_PATH];
		::GetFullPathName(pszPath, sizeof(szFullPath) / sizeof(TCHAR),
			szFullPath, NULL);
		m_strPath = szFullPath;
		CString strTitle = _T("WinDir - ");
		strTitle += szFullPath;
		AfxGetMainWnd()->SetWindowText(strTitle);
		// 
		// Add items representing files to the list view. 
		if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			AddItem(nCount++, &fd);
		while (::FindNextFile(hFind, &fd)) {
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				if (!AddItem(nCount++, &fd))
					break;
		}
		::FindClose(hFind);
	}
	return nCount;
}


BOOL CFileView::AddItem(int nIndex, WIN32_FIND_DATA* pfd)
{
	// 
	 // Allocate a new ITEMINFO structure and initialize it with information 
	 // about the item. 
	 // 
	ITEMINFO* pItem;
	try {
		pItem = new ITEMINFO;
	}

	catch (CMemoryException* e) {
		e->Delete();
		return FALSE;
	}
	pItem->strFileName = pfd->cFileName;
	pItem->nFileSizeLow = pfd->nFileSizeLow;
	pItem->ftLastWriteTime = pfd->ftLastWriteTime;
	// 
	// Add the item to the list view. 
	// 
	LV_ITEM lvi;
	lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
	lvi.iItem = nIndex;
	lvi.iSubItem = 0;
	lvi.iImage = 0;
	lvi.pszText = LPSTR_TEXTCALLBACK;
	lvi.lParam = (LPARAM)pItem;
	if (GetListCtrl().InsertItem(&lvi) == -1)
		return FALSE;
	return TRUE;
}

void CFileView::OnGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult)
{
	CString string;
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	if (pDispInfo->item.mask & LVIF_TEXT) {
		ITEMINFO* pItem = (ITEMINFO*)pDispInfo->item.lParam;
		switch (pDispInfo->item.iSubItem) {
		case 0: // File name. 
			::lstrcpy(pDispInfo->item.pszText, pItem->strFileName);
			break;
		case 1: // File size. 
			string.Format(_T("%u"), pItem->nFileSizeLow);
			::lstrcpy(pDispInfo->item.pszText, string);
			break;
		case 2: // Date and datetime. 
			CTime time(pItem->ftLastWriteTime);
			BOOL pm = FALSE;
			int nHour = time.GetHour();
			if (nHour == 0)
				nHour = 12;
			else if (nHour == 12)
				pm = TRUE;
			else if (nHour > 12) {
				nHour -= 12;
				pm = TRUE;
			}
			string.Format(_T("%d/%0.2d/%0.2d (%d:%0.2d%c)"),
				time.GetMonth(), time.GetDay(), time.GetYear() % 100,
				nHour, time.GetMinute(), pm ? __T('p') : __T('a'));
			::lstrcpy(pDispInfo->item.pszText, string);
			break;
		}
	}
	*pResult = 0;
}

void CFileView::OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	GetListCtrl().SortItems(CompareFunc, pNMListView->iSubItem);
	*pResult = 0;

}

void CFileView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();
	// 
	// Initialize the image list. 
	// 
	m_ilLarge.Create(IDB_LARGEDOC, 32, 1, RGB(255, 0, 255));
	m_ilSmall.Create(IDB_SMALLDOC, 16, 1, RGB(255, 0, 255));
	GetListCtrl().SetImageList(&m_ilLarge, LVSIL_NORMAL);
	GetListCtrl().SetImageList(&m_ilSmall, LVSIL_SMALL);
	// 
	// Add columns to the list view. 
	// 
	GetListCtrl().InsertColumn(0, _T("File Name"), LVCFMT_LEFT, 192);
	GetListCtrl().InsertColumn(1, _T("Size"), LVCFMT_RIGHT, 96);
	GetListCtrl().InsertColumn(2, _T("Last Modified"), LVCFMT_CENTER, 128);

	TCHAR szPath[MAX_PATH];
	::GetCurrentDirectory(sizeof(szPath) / sizeof(TCHAR), szPath);
	Refresh(szPath);
}

BOOL CFileView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CListView::PreCreateWindow(cs))
		return FALSE;
	cs.style &= ~LVS_TYPEMASK;
	cs.style |= LVS_REPORT;
	return TRUE;
}