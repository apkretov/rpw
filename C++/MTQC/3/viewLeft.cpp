#include "stdafx.h"
#include "app.h"
#include "doc.h"
#include "viewLeft.h"
#include "viewRight.h"
using boost::property_tree::ptree;
#include "functions.h"
using mtqcMFC::functions::stringToWstring;
using mtqcMFC::functions::wstringToString;
using std::string;

#ifdef _DEBUG
	#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(viewLeft, CTreeView)

BEGIN_MESSAGE_MAP(viewLeft, CTreeView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &viewLeft::OnTvnSelchanged)
	ON_NOTIFY_REFLECT(TVN_KEYDOWN, &viewLeft::OnTvnKeydown)
END_MESSAGE_MAP()

viewLeft::viewLeft() {}

viewLeft::~viewLeft() {}

BOOL viewLeft::PreCreateWindow(CREATESTRUCT& cs) { return CTreeView::PreCreateWindow(cs); } // TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs

void viewLeft::OnInitialUpdate() { 
	GetTreeCtrl().ModifyStyle(NULL, TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT); //Windows Explorer Application - 30. To add the options to the tree list, access the OnInitialUpdate() event and type the following line that sets the style. @ http://www.functionx.com/visualc/applications/explorer.htm
	CTreeView::OnInitialUpdate(); // TODO: You may populate your TreeView with items by directly accessing its tree control through a call to GetTreeCtrl().
}

#ifdef _DEBUG // viewLeft diagnostics
	void viewLeft::AssertValid() const { CTreeView::AssertValid(); }
	void viewLeft::Dump(CDumpContext& dc) const { CTreeView::Dump(dc); }

	doc* viewLeft::GetDocument() const { // non-debug version is inline
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(doc)));
		return (doc*)m_pDocument;
	}
#endif

int viewLeft::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CTreeView::OnCreate(lpCreateStruct) == -1) return -1;
	GetDocument()->setViewLeft(this); //Windows Explorer Application - 15. Whenever a view goes through the document class to access the right view, you need to communicate to the document view what object is being called. @ http://www.functionx.com/visualc/applications/explorer.htm 
	return 0;
}

void viewLeft::createConstants() { //Windows Explorer Application - 23. To create some items for the tree, in Class View, right-click CLeftView -> Add Member Function... 24. Set the return type to void. @ http://www.functionx.com/visualc/applications/explorer.htm 
	GetTreeCtrl().DeleteAllItems(); // If there is anything in the tree, remove it
	CTreeCtrl& ctlViewLeft = this->GetTreeCtrl();
	treeImages.Create(IDB_TREE_BMP, 16, 1, RGB(255, 255, 255));
	ctlViewLeft.SetImageList(&treeImages, TVSIL_NORMAL);	
	ptree ptreeRoot = GetDocument()->getPtreeConstants()->get_child("");
	for (const auto& pairRoot : ptreeRoot) { //Get the root item in a sigle loop operation. I used the loop because I didn't know how to get an key of the pair another way w/o using the for loop.
		HTREEITEM hndRoot = ctlViewLeft.InsertItem(stringToWstring(pairRoot.first).c_str(), 0, 1); //Use ptree in a loop.
		ptree ptreeLevel1 = ptreeRoot.get_child(pairRoot.first);
		for (const auto& pairLevel1 : ptreeLevel1) ctlViewLeft.InsertItem(stringToWstring(pairLevel1.first).c_str(), 2, 3, hndRoot);
		ctlViewLeft.Expand(hndRoot, TVE_EXPAND);
}	}

CString viewLeft::getSelectedPath(bool* const ptrBlnHasParent) const { //bool* const ptrBlnHasParent is redundant and can be just an ordinary bool bool* const blnHasParent but has been left for practice. //Resume
	CTreeCtrl& ctlViewLeft = this->GetTreeCtrl(); // Get a reference to the tree control
	HTREEITEM nodSelected = ctlViewLeft.GetSelectedItem(); // Find out what item is selected in the tree
	HTREEITEM nodSelectedParent = ctlViewLeft.GetParentItem(nodSelected); // Find out what item is selected in the tree
	
	CString strSelectedPath = ctlViewLeft.GetItemText(nodSelected);	
	if (nodSelectedParent == nullptr) { //Is there no a parent?
		if (ptrBlnHasParent != nullptr) *ptrBlnHasParent = false; //Set the optional flag, if the caller has provided it. 
	} else {
		if (ptrBlnHasParent != nullptr) *ptrBlnHasParent = true; //Set the optional flag, if the caller has provided it.
		strSelectedPath = ctlViewLeft.GetItemText(nodSelectedParent) + "." + strSelectedPath; 
	}
	return strSelectedPath;
}

void viewLeft::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult) { //Windows Explorer Application - 47. Now that we have the necessary functions we can react when a node changes in the tree view. Using either the ClassWizard, the Messages section of the Properties, or whatever, generate a TVN_SELCHANGED message for the CLeftView class. @ http://www.functionx.com/visualc/applications/explorer.htm
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR); // TODO: Add your control notification handler code here

	doc* ptrDoc = GetDocument();
	viewRight* ptrViewRight = const_cast<viewRight*>(ptrDoc->getViewRight()); //Despite the constness is redundant, cast it away for practice. // 1) Type conversions - const_cast @ http://www.cplusplus.com/doc/tutorial/typecasting/ // 2) const_cast conversion @ http://en.cppreference.com/w/cpp/language/const_cast //Resume

	bool blnHasParent{};
	CString strSelectedPath = getSelectedPath(&blnHasParent);
	if (!blnHasParent) ptrViewRight->displayRoot(strSelectedPath); //No parent? This is a root item. 
	else ptrViewRight->displayGroup( ptrDoc->getPtreeConstants()->get_child(wstringToString(strSelectedPath.GetString())) );

	*pResult = 0;
}

void viewLeft::OnTvnKeydown(NMHDR* pNMHDR, LRESULT* pResult) {
	LPNMTVKEYDOWN pTVKeyDown = reinterpret_cast<LPNMTVKEYDOWN>(pNMHDR); // TODO: Add your control notification handler code here
	
	if (pTVKeyDown->wVKey == VK_TAB)	{ //Focus the right view on a Tab key strike.
		viewRight* ptrViewRight = const_cast<viewRight*>(GetDocument()->getViewRight());
		ptrViewRight->/*KTB GetListCtrl().*/SetFocus();
	}	
	
	*pResult = 1; //Beep in Tree Control - I replaced *pResult = 0; with *pResult = 1; in my TVN_KEYDOWN handler and the beep went away. @ http://www.verycomputer.com/418_fb03fe809dcf0462_1.htm
}
