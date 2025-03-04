#include "stdafx.h"
#ifndef SHARED_HANDLERS // SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail and search filter handlers and allows sharing of document code with that project.
#include "FTreeBrowser.h"
#endif
#include "FTreeBrowserDoc.h"
#include "CRightView.h"
#include "LeftView.h" //Creating a Simple Drives Explorer Program - Next you should add #include "LeftView.h" at the top of the file. @ https://www.codeproject.com/Articles/13366/Creating-a-Simple-Drives-Explorer-Program#_articleTop

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CRightView, CListView)

BEGIN_MESSAGE_MAP(CRightView, CListView)
	ON_WM_STYLECHANGED()
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CRightView::OnNMDblclk)
END_MESSAGE_MAP()

CRightView::CRightView() { /*TODO: add construction code here*/ }
CRightView::~CRightView() {}
BOOL CRightView::PreCreateWindow(CREATESTRUCT& cs) { return CListView::PreCreateWindow(cs); } // TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs

void CRightView::OnInitialUpdate() {
	CListView::OnInitialUpdate();
	// TODO: You may populate your ListView with items by directly accessing its list control through a call to GetListCtrl().
	CListCtrl &ctlFiles = this->GetListCtrl();
	ctlFiles.ModifyStyle(NULL, LVS_REPORT);
	m_ListImages.Create(IDB_TREE_BMP, 16, 1, RGB(255, 255, 255));
	ctlFiles.SetImageList(&m_ListImages, LVSIL_SMALL);
}

#ifdef _DEBUG // CRightView diagnostics
void CRightView::AssertValid() const { CListView::AssertValid(); }
void CRightView::Dump(CDumpContext& dc) const { CListView::Dump(dc); }

CFTreeBrowserDoc* CRightView::GetDocument() const { // non-debug version is inline
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFTreeBrowserDoc)));
	return (CFTreeBrowserDoc*)m_pDocument;
}
#endif


// CRightView message handlers
void CRightView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: add code to react to the user changing the view style of your window	
	CListView::OnStyleChanged(nStyleType, lpStyleStruct);
}


int CRightView::OnCreate(LPCREATESTRUCT lpCreateStruct) { //Creating a Simple Drives Explorer Program - Repeat the last few steps from 'Open up the ClassWizard' but this time select CRightView in the 'Class name' list and CRightView in the 'Object IDs' list. @ https://www.codeproject.com/Articles/13366/Creating-a-Simple-Drives-Explorer-Program#_articleTop
	if (CListView::OnCreate(lpCreateStruct) == -1) return -1;
	// TODO:  Add your specialized creation code here
	GetDocument()->pRightView = this;
	return 0;
}

void CRightView::ResetFiles() { //Creating a Simple Drives Explorer Program - First we'll add a function to clear the list control. @ https://www.codeproject.com/Articles/13366/Creating-a-Simple-Drives-Explorer-Program#_articleTop
	CListCtrl &ctlLView = GetListCtrl();
	ctlLView.DeleteAllItems();
	while (ctlLView.DeleteColumn(0));
	UpdateWindow();
}

void CRightView::DisplayFiles(LPTSTR Path) { //Creating a Simple Drives Explorer Program - It is now time to add the functionality which will display the contents of whatever folder is selected in the left pane. @ https://www.codeproject.com/Articles/13366/Creating-a-Simple-Drives-Explorer-Program#_articleTop
	CListCtrl &ctlRightView = this->GetListCtrl();

	ResetFiles();
	ctlRightView.InsertColumn(0, _T("File Name"), LVCFMT_LEFT, 160);
	ctlRightView.InsertColumn(1, _T("File Size"), LVCFMT_LEFT, 40);

	//AfxMessageBox(Path);

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	int nItem;

	hFind = FindFirstFile(Path, &FindFileData);
	int n = 0;

	if (hFind != INVALID_HANDLE_VALUE) {

		do {
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY
				&& FindFileData.cFileName != CString(".")
				&& FindFileData.cFileName != CString(".."))
			{
				++n;
				nItem = ctlRightView.InsertItem(n, L"File", 2);


				ctlRightView.SetItemText(nItem, 0, FindFileData.cFileName);

				long lFSize = FindFileData.nFileSizeLow;
				CString strFSize = L"";
				strFSize.Format(L"%d", lFSize);

				ctlRightView.SetItemText(nItem, 1, strFSize.GetBuffer(1));
			}
		} while ((::WaitForSingleObject(m_hStopEvent, 0) !=
			WAIT_OBJECT_0) && (::FindNextFile(hFind, &FindFileData)));
		::FindClose(hFind);;

		hFind = FindFirstFile(Path, &FindFileData);
		//n = 0;
		do {

			if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				++n;
				nItem = ctlRightView.InsertItem(n, L"File", 4);


				ctlRightView.SetItemText(nItem, 0, FindFileData.cFileName);

				long lFSize = FindFileData.nFileSizeLow;
				CString strFSize = L"";
				strFSize.Format(L"%d", lFSize);

				ctlRightView.SetItemText(nItem, 1, strFSize.GetBuffer(1));
			}
		} while ((::WaitForSingleObject(m_hStopEvent, 0) !=
			WAIT_OBJECT_0) && (::FindNextFile(hFind, &FindFileData)));
		::FindClose(hFind);;
	}
}


void CRightView::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult) { //Creating a Simple Drives Explorer Program - To make this application behave a little bit more like Microsoft's Windows Explorer, you make a folder clicked on in the right pane become the selected folder in the left pane. To do this, create a function for CRightView to handle the =NM_DBLCLK message. @ https://www.codeproject.com/Articles/13366/Creating-a-Simple-Drives-Explorer-Program#_articleTop
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	CFTreeBrowserDoc* pDoc = GetDocument();
	CListCtrl &ctlRightView = this->GetListCtrl();
	int nItem = ctlRightView.GetSelectionMark();
	CString string = ctlRightView.GetItemText(nItem, 0);
	pDoc->pLeftView->SetFocus();
	pDoc->pLeftView->OnRightViewFolderSelected(string, nItem);
}
