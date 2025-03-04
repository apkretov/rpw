#include "stdafx.h"
#include "FTreeBrowser.h"
#include "FTreeBrowserDoc.h"
#include "LeftView.h"
#include "CRightView.h" //Creating a Simple Drives Explorer Program - You will need to make sure you have an #include line for Rightview.h at the top of the file now. @ https://www.codeproject.com/Articles/13366/Creating-a-Simple-Drives-Explorer-Program#_articleTop

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CLeftView::OnTvnSelchanged)
END_MESSAGE_MAP()

CLeftView::CLeftView() { /*TODO: add construction code here*/ }
CLeftView::~CLeftView() {}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs

	return CTreeView::PreCreateWindow(cs);
}

void CLeftView::OnInitialUpdate() {
	CTreeView::OnInitialUpdate();
	// TODO: You may populate your TreeView with items by directly accessing its tree control through a call to GetTreeCtrl().
	GetTreeCtrl().ModifyStyle(NULL, TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT); //Creating a Simple Drives Explorer Program - Go back to the CLeftView class and add a call to the tree's ModifyStyle method in the OnInitialUpdate function. @ https://www.codeproject.com/Articles/13366/Creating-a-Simple-Drives-Explorer-Program#_articleTop
}


// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CFTreeBrowserDoc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFTreeBrowserDoc)));
	return (CFTreeBrowserDoc*)m_pDocument;
}
#endif //_DEBUG

// CLeftView message handlers
int CLeftView::OnCreate(LPCREATESTRUCT lpCreateStruct) { //Creating a Simple Drives Explorer Program - Open up the ClassWizard (press CTRL-W), under the Message Maps tab, select CLeftView in the 'Class name' list, CLeftView in the 'Object IDs' list, WM_CREATE in the 'Messages:' list. If you double-click on WM_CREATE, the OnCreate function is created and highlighted for you in the member functions list. @ https://www.codeproject.com/Articles/13366/Creating-a-Simple-Drives-Explorer-Program#_articleTop
	if (CTreeView::OnCreate(lpCreateStruct) == -1) return -1; 
	// TODO:  Add your specialized creation code here
	GetDocument()->pLeftView = this; 
	return 0;
}

void CLeftView::CreateRoots() { //Creating a Simple Drives Explorer Program - Now to populate the root items in the tree we create a function called CreateRoots. In ClassView, right-click CLeftView-> Add Member Function. @ https://www.codeproject.com/Articles/13366/Creating-a-Simple-Drives-Explorer-Program#_articleTop
	GetTreeCtrl().DeleteAllItems(); // If there is anything in the tree, remove it
	CTreeCtrl &ctlDrives = this->GetTreeCtrl();
	m_TreeImages.Create(IDB_TREE_BMP, 16, 1, RGB(255, 255, 255));
	ctlDrives.SetImageList(&m_TreeImages, TVSIL_NORMAL);

	HTREEITEM hRoot;
	char* strBuffer = NULL;
	CString strMessage;
	int nPos = 0;
	UINT nCount = 0;
	CString strDrive = L"?:\\";
	DWORD dwDriveList = ::GetLogicalDrives();
	CString cTmp;
	while (dwDriveList) {
		if (dwDriveList & 1) {
			cTmp = strDrive;
			strDrive.SetAt(0, 0x41 + nPos);
			strDrive = strDrive.Left(2);
			hRoot = ctlDrives.InsertItem(strDrive, 0, 1);
		}
		dwDriveList >>= 1;
		nPos++;
}	}

void CLeftView::OpenFolder(CString CStrPath) { //Creating a Simple Drives Explorer Program - Next we look at what happens when a folder is selected (opened) in the left hand pane. @ https://www.codeproject.com/Articles/13366/Creating-a-Simple-Drives-Explorer-Program#_articleTop
	CTreeCtrl &ctlFolders = this->GetTreeCtrl();
	HTREEITEM hRoot;
	HTREEITEM hFolder;
	hRoot = ctlFolders.GetSelectedItem();
	HTREEITEM hChild = ctlFolders.GetChildItem(hRoot);
	while (hChild != 0) { // Clear the selected node
		ctlFolders.DeleteItem(hChild);
		hChild = ctlFolders.GetChildItem(hRoot);
	}
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	CStrPath = CStrPath + L"\\*.*";
	hFind = FindFirstFile(CStrPath, &FindFileData);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			long lFSize = FindFileData.nFileSizeLow;
			CString strFSize = L"";
			if ( FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && FindFileData.cFileName != CString(".") && FindFileData.cFileName != CString("..") ) //Want folders that aren't . and ..
				hFolder = ctlFolders.InsertItem(FindFileData.cFileName, 2, 3, hRoot);
		} while ((::WaitForSingleObject(m_hStopEvent, 0) != WAIT_OBJECT_0)
			&& (::FindNextFile(hFind, &FindFileData)));
		::FindClose(hFind);;
}	}

void CLeftView::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult) { //Creating a Simple Drives Explorer Program - Now that we have the necessary functions, we can react when a node changes in the tree view. Using either the ClassWizard, the Messages section of the Properties, or whatever, generate a TVN_SELCHANGED message for the CLeftView class. @ https://www.codeproject.com/Articles/13366/Creating-a-Simple-Drives-Explorer-Program#_articleTop
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	*pResult = 0; // TODO: Add your control notification handler code here
	CFTreeBrowserDoc* pDoc = GetDocument();
	CTreeCtrl &ctlFiles = this->GetTreeCtrl(); // Get a reference to the tree control
	HTREEITEM nodSelected = ctlFiles.GetSelectedItem(); // Find out what item is selected in the tree
	CString strSelected = ctlFiles.GetItemText(nodSelected); // Get the string of the selected node
	HTREEITEM nodParent = nodSelected;
	do { //Build the full path with wild cards
		nodParent = ctlFiles.GetParentItem(nodParent);
		if (nodParent != NULL) strSelected = ctlFiles.GetItemText(nodParent) + "\\" + strSelected;
	} while (nodParent != NULL);
	CString strSearchPath = strSelected + "\\*.*";
	pDoc->pRightView->DisplayFiles(strSearchPath.GetBuffer(1));
	OpenFolder(strSelected);
}

void CLeftView::OnRightViewFolderSelected(CString strPath, UINT index) { //Creating a Simple Drives Explorer Program - Then you need to create the function CLeftView::OnRightViewFolderSelected(...). @ https://www.codeproject.com/Articles/13366/Creating-a-Simple-Drives-Explorer-Program#_articleTop
	CFTreeBrowserDoc *pDoc = GetDocument();
	CTreeCtrl &ctlFolders = this->GetTreeCtrl(); // Get a reference to the tree control
	HTREEITEM nodSelected = ctlFolders.GetSelectedItem(); // Find out what item is selected in the tree
	ctlFolders.Expand(nodSelected, TVE_EXPAND); //Open up the branch
	int count = 0;
	HTREEITEM nodChild;
	nodChild = ctlFolders.GetChildItem(nodSelected);
	if (index > 0) {
		do {
			nodChild = ctlFolders.GetNextItem(nodChild, TVGN_NEXT);
			++count;
		} while (count < (int)index);
	}
	if (nodChild != NULL) {
		ctlFolders.SelectItem(nodChild);
		ctlFolders.Expand(nodChild, TVE_EXPAND);
		nodSelected = nodChild;
		CString strSelected = ctlFolders.GetItemText(nodSelected); // Get the string of the selected node
		HTREEITEM nodParent = nodSelected;
		do { //Build the full path with wild cards
			nodParent = ctlFolders.GetParentItem(nodParent);
			if (nodParent != NULL) strSelected = ctlFolders.GetItemText(nodParent) + "\\" + strSelected;
		} while (nodParent != NULL);
		CString strSearchPath = strSelected + "\\*.*";
		pDoc->pRightView->DisplayFiles(strSearchPath.GetBuffer(1));
}	}
