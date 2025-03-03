#include "stdafx.h"
#ifndef SHARED_HANDLERS // SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail and search filter handlers and allows sharing of document code with that project.
	#include "app.h"
#endif
#include "doc.h"
#include "viewRight.h"
#include "functions.h"
using mtqcMFC::functions::stringToWstring;
using mtqcMFC::functions::wstringToString;
#include "editConstant.h"
#include "enumerators.h"
using mtqcMFC::enmSubItems;
using std::string;
using std::wstring;
#include "viewLeft.h"
using boost::property_tree::ptree;

#ifdef _DEBUG
	#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(viewRight, CListView)

BEGIN_MESSAGE_MAP(viewRight, CListView)
	ON_WM_STYLECHANGED()
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(NM_DBLCLK, &viewRight::OnNMDblclk)
	ON_NOTIFY_REFLECT(LVN_KEYDOWN, &viewRight::OnLvnKeydown)
END_MESSAGE_MAP()

viewRight::viewRight() { /*TODO: add construction code here*/ }

viewRight::~viewRight() {}

BOOL viewRight::PreCreateWindow(CREATESTRUCT& cs) { return CListView::PreCreateWindow(cs); } // TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs

void viewRight::OnInitialUpdate() {
	CListView::OnInitialUpdate(); // TODO: You may populate your ListView with items by directly accessing its list control through a call to GetListCtrl().
	CListCtrl& objViewRight = this->GetListCtrl(); //Windows Explorer Application - 46. To make this exercise again simpler, we will mostly care only for the Report View Access the OnInitialUpdate() event of the CRightView class and change it as follows. @ http://www.functionx.com/visualc/applications/explorer.htm
	objViewRight.ModifyStyle(NULL, LVS_REPORT);
	objViewRight.SetExtendedStyle(LVS_EX_FULLROWSELECT /*ORIG | LVS_EX_GRIDLINES*/);	
}

#ifdef _DEBUG // viewRight diagnostics
	void viewRight::AssertValid() const { CListView::AssertValid(); }
	void viewRight::Dump(CDumpContext& dc) const { CListView::Dump(dc); }

	doc* viewRight::GetDocument() const { // non-debug version is inline
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(doc)));
		return (doc*)m_pDocument;
	}
#endif

void viewRight::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct) { // viewRight message handlers
	CListView::OnStyleChanged(nStyleType, lpStyleStruct); //TODO: add code to react to the user changing the view style of your window
}

void viewRight::setImageList() {
	CListCtrl& objViewRight = GetListCtrl();
	listImages.Create(IDB_TREE_BMP, 16, 1, RGB(255, 255, 255));
	objViewRight.SetImageList(&listImages, LVSIL_SMALL);
}

void viewRight::resetConstants() { //Windows Explorer Application - 34. When an item is selected in the tree, whether by the user or else, you can specify what should happen in another view, such as the right frame for our example. First of all, we need a mechanism to erase the list view every time it must be updated, otherwise, the items to display would just be added to the existing ones. In the Class View, right-click the CRightView class -> Add Member Function... @ http://www.functionx.com/visualc/applications/explorer.htm
	CListCtrl& objViewRight = GetListCtrl();
	objViewRight.DeleteAllItems();
	while (objViewRight.DeleteColumn(0))	; //An empty while command.
	UpdateWindow();
}

void viewRight::displayRoot(const CString& strRoot) { //Windows Explorer Application - When the root node is selected in the left frame, we will display a list of leagues. In the Class View, right-click the CRightView class -> Add Member Function... @ http://www.functionx.com/visualc/applications/explorer.htm
	CListCtrl& ctlViewRight = this->GetListCtrl();
	resetConstants();
	ctlViewRight.InsertColumn((int)enmSubItems::name, strRoot, LVCFMT_LEFT, cintColWidth);
	ctlViewRight.InsertItem((int)enmSubItems::name, strRoot);
}

void viewRight::displayGroup(const boost::property_tree::ptree& ptreeGroup) {
	CListCtrl& ctlViewRight = this->GetListCtrl();
	resetConstants();
	ctlViewRight.InsertColumn((int)enmSubItems::name, L"Constant name", LVCFMT_LEFT, cintColWidth);
	ctlViewRight.InsertColumn((int)enmSubItems::value, L"Constant value", LVCFMT_LEFT, cintColWidth / 2);
	for (const auto& pairItem : ptreeGroup) {
		int intItem = ctlViewRight.InsertItem((int)enmSubItems::name, (stringToWstring(pairItem.first)).c_str());
		ctlViewRight.SetItemText(intItem, (int)enmSubItems::value, (stringToWstring(pairItem.second.get_value<string>())).c_str());
}	}

int viewRight::OnCreate(LPCREATESTRUCT lpCreateStruct) { //The original description (Windows Explorer Application @ http://www.functionx.com/visualc/applications/explorer.htm) misses this step described here: Creating a Simple Drives Explorer Program - Repeat the last few steps from 'Open up the ClassWizard' but this time select CRightView in the 'Class name' list and CRightView in the 'Object IDs' list. Next you will need to add the line GetDocument()->pRightView = this; to the CRightView::OnCreate function as follows: @ https://www.codeproject.com/Articles/13366/Creating-a-Simple-Drives-Explorer-Program
	if (CListView::OnCreate(lpCreateStruct) == -1) return -1;
	GetDocument()->setViewRight(this); // TODO: Add your specialized creation code here
	return 0;
}

void viewRight::editSelectedConstant() {
	CListCtrl &ctlRightView = this->GetListCtrl();
	int intSelected = ctlRightView.GetSelectionMark();
	CString strSelectedName = ctlRightView.GetItemText(intSelected, (int)enmSubItems::name);
	
	editConstant dlgEditConstant;
	dlgEditConstant.setName(strSelectedName);
	dlgEditConstant.setValue(ctlRightView.GetItemText(intSelected, (int)enmSubItems::value));

	doc* ptrDoc = GetDocument(); //Save the value in the property tree.
	bool blnHasParent{};
	CString strSelectedPath = ptrDoc->getViewLeft()->getSelectedPath(&blnHasParent);
	
	if (blnHasParent)	{ //Skip the root item.
		if (dlgEditConstant.DoModal() == IDOK)	{ //Has a value changed?
			CListCtrl& ctlViewRight = this->GetListCtrl(); //Set the value on the dialogue.
			ctlViewRight.SetItemText(intSelected, (int)enmSubItems::value, dlgEditConstant.getValue());

			CString strPath = strSelectedPath + "." +  dlgEditConstant.getName();
			ptree* ptreeConstants = const_cast<ptree*>(ptrDoc->getPtreeConstants()); //Despite the constness is redundant, cast it away for practice. // 1) Type conversions - const_cast @ http://www.cplusplus.com/doc/tutorial/typecasting/ // 2) const_cast conversion @ http://en.cppreference.com/w/cpp/language/const_cast //Resume
			ptreeConstants->put(wstringToString(strPath.GetString()), wstringToString(dlgEditConstant.getValue().GetString()));
			ptrDoc->setConstantsChanged(true);
}	}	}

void viewRight::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult) {
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR); // TODO: Add your control notification handler code here
	editSelectedConstant();
	*pResult = 0;
}

void viewRight::OnLvnKeydown(NMHDR *pNMHDR, LRESULT *pResult) {
	LPNMLVKEYDOWN pLVKeyDown = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR); // TODO: Add your control notification handler code here
	switch (pLVKeyDown->wVKey)	{
	case VK_TAB: {
		viewLeft* ptrViewLeft = const_cast<viewLeft*>(GetDocument()->getViewLeft());
		ptrViewLeft->SetFocus();
		*pResult = 1; //Beep in Tree Control - I replaced *pResult = 0; with *pResult = 1; in my TVN_KEYDOWN handler and the beep went away. @ http://www.verycomputer.com/418_fb03fe809dcf0462_1.htm
		break;
	} case VK_RETURN: 
		editSelectedConstant();
	default:	
		this->SetFocus();
		*pResult = 0;
}	}
