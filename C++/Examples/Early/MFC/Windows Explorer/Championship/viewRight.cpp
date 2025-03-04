#include "stdafx.h"
#ifndef SHARED_HANDLERS // SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail and search filter handlers and allows sharing of document code with that project.
#include "app.h"
#endif
#include "doc.h"
#include "viewRight.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(viewRight, CListView)

BEGIN_MESSAGE_MAP(viewRight, CListView)
	ON_WM_STYLECHANGED()
	ON_WM_CREATE()
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

void viewRight::setImageList() { //TEST
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

void viewRight::displayConstants() { //Windows Explorer Application - When the root node is selected in the left frame, we will display a list of leagues. In the Class View, right-click the CRightView class -> Add Member Function... @ http://www.functionx.com/visualc/applications/explorer.htm
	CListCtrl& objViewRight = this->GetListCtrl();

	resetConstants();

	objViewRight.InsertColumn(0, _T("Country"), LVCFMT_LEFT, 80);
	objViewRight.InsertColumn(1, _T("League Name"), LVCFMT_LEFT, 160);
	objViewRight.InsertColumn(2, _T("Address"), LVCFMT_LEFT, 180);
	objViewRight.InsertColumn(3, _T("Web Site"), LVCFMT_LEFT, 200);

	int nItem;
	nItem = objViewRight.InsertItem(0, L"England");
	objViewRight.SetItemText(nItem, 1, L"English Premier League");
	objViewRight.SetItemText(nItem, 2, L"Don't Know");
	objViewRight.SetItemText(nItem, 3, L"http://www.premierleague.com");
}

void viewRight::displayConstants(CString strConstant) { //Windows Explorer Application - 40. In the same way, when an item is selected in the list, we will find out what its string is, pass that string to the list view and then update the list view accordingly. In the Class View, right-click the CRightView class -> Add Member Function... @ http://www.functionx.com/visualc/applications/explorer.htm
	CListCtrl &objViewRight = this->GetListCtrl();
	resetConstants();

	objViewRight.InsertColumn(0,  _T("Season"), LVCFMT_LEFT,   80);
	objViewRight.InsertColumn(1,  _T("Rank"),   LVCFMT_LEFT,   50);
	objViewRight.InsertColumn(2,  _T("Team"),   LVCFMT_LEFT,  100);
	objViewRight.InsertColumn(3,  _T("P"),      LVCFMT_RIGHT,  30);
	objViewRight.InsertColumn(4,  _T("W"),      LVCFMT_RIGHT,  30);
	objViewRight.InsertColumn(5,  _T("D"),      LVCFMT_RIGHT,  30);
	objViewRight.InsertColumn(6,  _T("L"),      LVCFMT_RIGHT,  30);
	objViewRight.InsertColumn(7,  _T("F"),      LVCFMT_RIGHT,  30);
	objViewRight.InsertColumn(8,  _T("A"),      LVCFMT_RIGHT,  30);
	objViewRight.InsertColumn(9,  _T("GD"),     LVCFMT_RIGHT,  30);
	objViewRight.InsertColumn(10, _T("Pts"),    LVCFMT_RIGHT,  30);

	int nItem;
	if (strConstant == "English Premier League") {
		nItem = objViewRight.InsertItem(0,  L"2004-2005");
		objViewRight.SetItemText(nItem, 1,  L"6");
		objViewRight.SetItemText(nItem, 2,  L"Aston Villa");
		objViewRight.SetItemText(nItem, 3,  L"16");
		objViewRight.SetItemText(nItem, 4,  L"6");
		objViewRight.SetItemText(nItem, 5,  L"7");
		objViewRight.SetItemText(nItem, 6,  L"3");
		objViewRight.SetItemText(nItem, 7,  L"21");
		objViewRight.SetItemText(nItem, 8,  L"17");
		objViewRight.SetItemText(nItem, 9,  L"4");
		objViewRight.SetItemText(nItem, 10, L"25");

		nItem = objViewRight.InsertItem(0,  L"2004-2005");
		objViewRight.SetItemText(nItem, 1,  L"5");
		objViewRight.SetItemText(nItem, 2,  L"Middlesbro");
		objViewRight.SetItemText(nItem, 3,  L"16");
		objViewRight.SetItemText(nItem, 4,  L"8");
		objViewRight.SetItemText(nItem, 5,  L"4");
		objViewRight.SetItemText(nItem, 6,  L"4");
		objViewRight.SetItemText(nItem, 7,  L"27");
		objViewRight.SetItemText(nItem, 8,  L"20");
		objViewRight.SetItemText(nItem, 9,  L"7");
		objViewRight.SetItemText(nItem, 10, L"28");
	} else if (strConstant == "Lega Nazionale Professionisti") {
		nItem = objViewRight.InsertItem(0,  L"2004-2005");
		objViewRight.SetItemText(nItem, 1,  L"2");
		objViewRight.SetItemText(nItem, 2,  L"Milan");
		objViewRight.SetItemText(nItem, 3,  L"28");
		objViewRight.SetItemText(nItem, 4,  L"13");
		objViewRight.SetItemText(nItem, 5,  L"8");
		objViewRight.SetItemText(nItem, 6,  L"4");
		objViewRight.SetItemText(nItem, 7,  L"1");
		objViewRight.SetItemText(nItem, 8,  L"19");
		objViewRight.SetItemText(nItem, 9,  L"8");
		objViewRight.SetItemText(nItem, 10, L"11");

		nItem = objViewRight.InsertItem(0,  L"2004-2005");
		objViewRight.SetItemText(nItem, 1,  L"1");
		objViewRight.SetItemText(nItem, 2,  L"Juventus");
		objViewRight.SetItemText(nItem, 3,  L"32");
		objViewRight.SetItemText(nItem, 4,  L"13");
		objViewRight.SetItemText(nItem, 5,  L"10");
		objViewRight.SetItemText(nItem, 6,  L"2");
		objViewRight.SetItemText(nItem, 7,  L"1");
		objViewRight.SetItemText(nItem, 8,  L"25");
		objViewRight.SetItemText(nItem, 9,  L"6");
		objViewRight.SetItemText(nItem, 10, L"19");
}	}

void viewRight::displayConstants(CString strConstant, CString strSeason) { //Windows Explorer Application - 43. In the Class View, right-click the CRightView class -> Add Member Function...  @ http://www.functionx.com/visualc/applications/explorer.htm
	CListCtrl &ctlRightView = this->GetListCtrl();
	resetConstants();

	ctlRightView.InsertColumn(1, _T("Rank"), LVCFMT_RIGHT, 50);
	ctlRightView.InsertColumn(2, _T("Team"), LVCFMT_LEFT, 100);
	ctlRightView.InsertColumn(3, _T("P"), LVCFMT_RIGHT, 30);
	ctlRightView.InsertColumn(4, _T("W"), LVCFMT_RIGHT, 30);
	ctlRightView.InsertColumn(5, _T("D"), LVCFMT_RIGHT, 30);
	ctlRightView.InsertColumn(6, _T("L"), LVCFMT_RIGHT, 30);
	ctlRightView.InsertColumn(7, _T("F"), LVCFMT_RIGHT, 30);
	ctlRightView.InsertColumn(8, _T("A"), LVCFMT_RIGHT, 30);
	ctlRightView.InsertColumn(9, _T("GD"), LVCFMT_RIGHT, 30);
	ctlRightView.InsertColumn(10, _T("Pts"), LVCFMT_RIGHT, 30);

	if (strConstant == "English Premier League") {
		if (strSeason == "2004-2005") {
			int nItem;
			nItem = ctlRightView.InsertItem(0, L"4");
			ctlRightView.SetItemText(nItem, 1, L"Man Utd");
			ctlRightView.SetItemText(nItem, 2, L"16");
			ctlRightView.SetItemText(nItem, 3, L"8");
			ctlRightView.SetItemText(nItem, 4, L"6");
			ctlRightView.SetItemText(nItem, 5, L"2");
			ctlRightView.SetItemText(nItem, 6, L"22");
			ctlRightView.SetItemText(nItem, 7, L"10");
			ctlRightView.SetItemText(nItem, 8, L"12");
			ctlRightView.SetItemText(nItem, 9, L"30");

			nItem = ctlRightView.InsertItem(0, L"3");
			ctlRightView.SetItemText(nItem, 1, L"Everton");
			ctlRightView.SetItemText(nItem, 2, L"16");
			ctlRightView.SetItemText(nItem, 3, L"10");
			ctlRightView.SetItemText(nItem, 4, L"3");
			ctlRightView.SetItemText(nItem, 5, L"3");
			ctlRightView.SetItemText(nItem, 6, L"20");
			ctlRightView.SetItemText(nItem, 7, L"14");
			ctlRightView.SetItemText(nItem, 8, L"6");
			ctlRightView.SetItemText(nItem, 9, L"33");
		} else if (strSeason == "2003-2004") {
			int nItem;
			nItem = ctlRightView.InsertItem(0, L"10");
			ctlRightView.SetItemText(nItem, 1, L"Birmingham");
			ctlRightView.SetItemText(nItem, 2, L"38");
			ctlRightView.SetItemText(nItem, 3, L"12");
			ctlRightView.SetItemText(nItem, 4, L"14");
			ctlRightView.SetItemText(nItem, 5, L"12");
			ctlRightView.SetItemText(nItem, 6, L"43");
			ctlRightView.SetItemText(nItem, 7, L"48");
			ctlRightView.SetItemText(nItem, 8, L"-5");
			ctlRightView.SetItemText(nItem, 9, L"50");

			nItem = ctlRightView.InsertItem(0, L"9");
			ctlRightView.SetItemText(nItem, 1, L"Fulham");
			ctlRightView.SetItemText(nItem, 2, L"38");
			ctlRightView.SetItemText(nItem, 3, L"14");
			ctlRightView.SetItemText(nItem, 4, L"10");
			ctlRightView.SetItemText(nItem, 5, L"14");
			ctlRightView.SetItemText(nItem, 6, L"52");
			ctlRightView.SetItemText(nItem, 7, L"46");
			ctlRightView.SetItemText(nItem, 8, L"6");
			ctlRightView.SetItemText(nItem, 9, L"52");
	}	}
	else if (strConstant == "Lega Nazionale Professionisti") {
		if (strSeason == "2004-2005") {
			int nItem;
			nItem = ctlRightView.InsertItem(0, L"2");
			ctlRightView.SetItemText(nItem, 1, L"Milan");
			ctlRightView.SetItemText(nItem, 2, L"28");
			ctlRightView.SetItemText(nItem, 3, L"13");
			ctlRightView.SetItemText(nItem, 4, L"8");
			ctlRightView.SetItemText(nItem, 5, L"4");
			ctlRightView.SetItemText(nItem, 6, L"1");
			ctlRightView.SetItemText(nItem, 7, L"19");
			ctlRightView.SetItemText(nItem, 8, L"8");
			ctlRightView.SetItemText(nItem, 9, L"11");

			nItem = ctlRightView.InsertItem(0, L"1");
			ctlRightView.SetItemText(nItem, 1, L"Juventus");
			ctlRightView.SetItemText(nItem, 2, L"32");
			ctlRightView.SetItemText(nItem, 3, L"13");
			ctlRightView.SetItemText(nItem, 4, L"10");
			ctlRightView.SetItemText(nItem, 5, L"2");
			ctlRightView.SetItemText(nItem, 6, L"1");
			ctlRightView.SetItemText(nItem, 7, L"25");
			ctlRightView.SetItemText(nItem, 8, L"6");
			ctlRightView.SetItemText(nItem, 9, L"19");
}	}	}

int viewRight::OnCreate(LPCREATESTRUCT lpCreateStruct) { //The original description (Windows Explorer Application @ http://www.functionx.com/visualc/applications/explorer.htm) misses this step described here: Creating a Simple Drives Explorer Program - Repeat the last few steps from 'Open up the ClassWizard' but this time select CRightView in the 'Class name' list and CRightView in the 'Object IDs' list. Next you will need to add the line GetDocument()->pRightView = this; to the CRightView::OnCreate function as follows: @ https://www.codeproject.com/Articles/13366/Creating-a-Simple-Drives-Explorer-Program
	if (CListView::OnCreate(lpCreateStruct) == -1) return -1;
	GetDocument()->ptrViewRight = this; // TODO:  Add your specialized creation code here
	return 0;
}
