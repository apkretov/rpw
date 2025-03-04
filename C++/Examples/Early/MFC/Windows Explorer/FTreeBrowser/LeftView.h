#pragma once
#include "afxwin.h"

class CFTreeBrowserDoc;

class CLeftView : public CTreeView {
	 HANDLE m_hStopEvent; //Creating a Simple Drives Explorer Program - ... must be inserted at the end of the class definition in the LeftView.h file. @ https://www.codeproject.com/Articles/13366/Creating-a-Simple-Drives-Explorer-Program#_articleTop
protected: // create from serialization only
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

// Attributes
public:
	CFTreeBrowserDoc* GetDocument();

// Operations
public:

// Overrides
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CImageList m_TreeImages; //Creating a Simple Drives Explorer Program - Once you have made your icons, you make them accessible to your tree control. The first step in this process is declaring a CImageList variable. Open up ClassView. Right click over CLeftView and click on 'Add Member Variable'. Declare your variable type as CImageList, variable Name as m_TreeImages and access as Public. @ https://www.codeproject.com/Articles/13366/Creating-a-Simple-Drives-Explorer-Program#_articleTop
	void CreateRoots();
	void OpenFolder(CString CStrPath);
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
	void OnRightViewFolderSelected(CString strPath, UINT index);
};

#ifndef _DEBUG  // debug version in LeftView.cpp
inline CFTreeBrowserDoc* CLeftView::GetDocument()
   { return reinterpret_cast<CFTreeBrowserDoc*>(m_pDocument); }
#endif
