
// MFC Creating new windowView.cpp : implementation of the CMFCCreatingnewwindowView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFC Creating new window.h"
#endif

#include "MFC Creating new windowDoc.h"
#include "MFC Creating new windowView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCCreatingnewwindowView

IMPLEMENT_DYNCREATE(CMFCCreatingnewwindowView, CView)

BEGIN_MESSAGE_MAP(CMFCCreatingnewwindowView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCCreatingnewwindowView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCCreatingnewwindowView construction/destruction

CMFCCreatingnewwindowView::CMFCCreatingnewwindowView()
{
	// TODO: add construction code here

}

CMFCCreatingnewwindowView::~CMFCCreatingnewwindowView()
{
}

BOOL CMFCCreatingnewwindowView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCCreatingnewwindowView drawing

void CMFCCreatingnewwindowView::OnDraw(CDC* /*pDC*/)
{
	CMFCCreatingnewwindowDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMFCCreatingnewwindowView printing


void CMFCCreatingnewwindowView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCCreatingnewwindowView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCCreatingnewwindowView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCCreatingnewwindowView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMFCCreatingnewwindowView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCCreatingnewwindowView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCCreatingnewwindowView diagnostics

#ifdef _DEBUG
void CMFCCreatingnewwindowView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCCreatingnewwindowView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCCreatingnewwindowDoc* CMFCCreatingnewwindowView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCCreatingnewwindowDoc)));
	return (CMFCCreatingnewwindowDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCCreatingnewwindowView message handlers
