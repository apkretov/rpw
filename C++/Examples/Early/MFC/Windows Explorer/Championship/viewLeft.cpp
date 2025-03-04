#include "stdafx.h"
#include "app.h"
#include "doc.h"
#include "viewLeft.h"
#include "viewRight.h"

#ifdef _DEBUG
	#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(viewLeft, CTreeView)

BEGIN_MESSAGE_MAP(viewLeft, CTreeView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &viewLeft::OnTvnSelchanged)
END_MESSAGE_MAP()

viewLeft::viewLeft() {}

viewLeft::~viewLeft() {}

BOOL viewLeft::PreCreateWindow(CREATESTRUCT& cs) { 
	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs
	return CTreeView::PreCreateWindow(cs); 
}

void viewLeft::OnInitialUpdate() { 
	GetTreeCtrl().ModifyStyle(NULL, TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT); //Windows Explorer Application - 30. To add the options to the tree list, access the OnInitialUpdate() event and type the following line that sets the style. @ http://www.functionx.com/visualc/applications/explorer.htm
	CTreeView::OnInitialUpdate(); 
	// TODO: You may populate your TreeView with items by directly accessing its tree control through a call to GetTreeCtrl().
}

#ifdef _DEBUG // viewLeft diagnostics
	void viewLeft::AssertValid() const { CTreeView::AssertValid(); }
	void viewLeft::Dump(CDumpContext& dc) const { CTreeView::Dump(dc); }

	doc* viewLeft::GetDocument() { // non-debug version is inline
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(doc)));
		return (doc*)m_pDocument;
	}
#endif

int viewLeft::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CTreeView::OnCreate(lpCreateStruct) == -1) return -1;
	GetDocument()->ptrViewLeft = this; //Windows Explorer Application - 15. Whenever a view goes through the document class to access the right view, you need to communicate to the document view what object is being called. @ http://www.functionx.com/visualc/applications/explorer.htm 
	return 0;
}

void viewLeft::createConstants() { //Windows Explorer Application - 23. To create some items for the tree, in Class View, right-click CLeftView -> Add Member Function... 24. Set the return type to void. @ http://www.functionx.com/visualc/applications/explorer.htm 
	GetTreeCtrl().DeleteAllItems(); // If there is anything in the tree, remove it
	CTreeCtrl& ctlConstants = this->GetTreeCtrl();
	treeImages.Create(IDB_TREE_BMP, 16, 1, RGB(255, 255, 255));
	ctlConstants.SetImageList(&treeImages, TVSIL_NORMAL);
	
	HTREEITEM hRoot;
	HTREEITEM hSeason;
	hRoot = ctlConstants.InsertItem(_T("World Football Championships"), 0, 1);
	hSeason = ctlConstants.InsertItem(L"English Premier League", 2, 3, hRoot);
	ctlConstants.InsertItem(_T("2004-2005"), 4, 5, hSeason);
	ctlConstants.InsertItem(_T("2003-2004"), 4, 5, hSeason);
	ctlConstants.InsertItem(_T("2002-2001"), 4, 5, hSeason);
	ctlConstants.InsertItem(_T("2000-2001"), 4, 5, hSeason);
	ctlConstants.InsertItem(_T("1999-2000"), 4, 5, hSeason);
	ctlConstants.Expand(hRoot, TVE_EXPAND);
}

void viewLeft::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult) { //Windows Explorer Application - 47. Now that we have the necessary functions we can react when a node changes in the tree view. Using either the ClassWizard, the Messages section of the Properties, or whatever, generate a TVN_SELCHANGED message for the CLeftView class. @ http://www.functionx.com/visualc/applications/explorer.htm
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR); // TODO: Add your control notification handler code here
	*pResult = 0;
	doc *ptrDoc = GetDocument();
	CTreeCtrl &objViewLeft = this->GetTreeCtrl(); // Get a reference to the tree control
	HTREEITEM nodSelected = objViewLeft.GetSelectedItem(); // Find out what item is selected in the tree
	CString strSelected = objViewLeft.GetItemText(nodSelected); // Get the string of the selected node
	HTREEITEM nodParentConstant = objViewLeft.GetParentItem(nodSelected); // Just in case the selected node as a parent, get that parent
	CString strParentConstant = objViewLeft.GetItemText(nodParentConstant); // Find the string of the parent of the selected node, if it has a parent
	if (strSelected == "2004-2005") { // Now you can react depending on the selected node
		if (strParentConstant == "English Premier League") ptrDoc->ptrViewRight->displayConstants(L"English Premier League", L"2004-2005");
		else if (strParentConstant == "Lega Nazionale Professionisti")	ptrDoc->ptrViewRight->displayConstants(L"Lega Nazionale Professionisti", L"2004-2005");
	} else if (strSelected == "2003-2004") {
		if (strParentConstant == "English Premier League")	ptrDoc->ptrViewRight->displayConstants(L"English Premier League", L"2003-2004");
	}
	else if (strSelected == "English Premier League") ptrDoc->ptrViewRight->displayConstants(L"English Premier League");
	else if (strSelected == "Lega Nazionale Professionisti")	ptrDoc->ptrViewRight->displayConstants(L"Lega Nazionale Professionisti");
	else ptrDoc->ptrViewRight->displayConstants();
}
