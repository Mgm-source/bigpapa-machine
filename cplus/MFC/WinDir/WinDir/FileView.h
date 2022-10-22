
// ChildView.h : interface of the CFileView class
//


#pragma once

// CFileView window

typedef struct tagITEMINFO {
	CString strFileName;
	DWORD nFileSizeLow;
	FILETIME ftLastWriteTime;
} ITEMINFO;

class CFileView : public CListView
{
// Construction
public:
	CFileView();
	DECLARE_DYNCREATE(CFileView)

// Attributes
public:

// Operations
public:
	static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2,
		LPARAM lParamSort);
	virtual void OnDraw(CDC* pDC); // overridden to draw this view 
	virtual void OnInitialUpdate(); // called first datetime after construc

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	int Refresh(LPCTSTR pszPath);
	virtual ~CFileView();
	CString m_strPath;
	void FreeItemMemory();
	BOOL AddItem(int nIndex, WIN32_FIND_DATA* pfd);
	CImageList m_ilSmall;
	CImageList m_ilLarge;

	// Generated message map functions
protected:
	afx_msg void OnDestroy();
	afx_msg void OnGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnViewLargeIcons();
	afx_msg void OnViewSmallIcons();
	afx_msg void OnViewList();
	afx_msg void OnViewDetails();
	afx_msg void OnUpdateViewLargeIcons(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewSmallIcons(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewList(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewDetails(CCmdUI* pCmdUI);
	afx_msg void OnFileNewDirectory();
	DECLARE_MESSAGE_MAP()
};

