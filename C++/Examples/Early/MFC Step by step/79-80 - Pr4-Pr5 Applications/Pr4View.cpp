#include "stdafx.h"
#ifndef SHARED_HANDLERS
	#include "Pr4.h"
#endif
#include "Pr4Doc.h"
#include "Pr4View.h"
#ifdef _DEBUG
	#define new DEBUG_NEW
#endif
#include "CNewDialog.h"

IMPLEMENT_DYNCREATE(CPr4View, CView)

BEGIN_MESSAGE_MAP(CPr4View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CPr4View construction/destruction

CPr4View::CPr4View()
{
	// TODO: add construction code here

}

CPr4View::~CPr4View()
{
}

BOOL CPr4View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

void CPr4View::OnDraw(CDC* pDC) { // CPr4View drawing
	CPr4Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc) return;
	pDC->TextOutW(10, 10, pDoc->stringData);
}


// CPr4View printing

BOOL CPr4View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPr4View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPr4View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CPr4View diagnostics

#ifdef _DEBUG
void CPr4View::AssertValid() const
{
	CView::AssertValid();
}

void CPr4View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPr4Doc* CPr4View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPr4Doc)));
	return (CPr4Doc*)m_pDocument;
}
#endif //_DEBUG

void CPr4View::OnLButtonUp(UINT nFlags, CPoint point) {
	CNewDialog cdialog; // объект класса
	if (cdialog.DoModal() == IDOK) { // если пользователь OK выбрал
		CPr4Doc* pDoc = GetDocument(); // получить класс документа
		pDoc->stringData = cdialog.m_Edits; // поменять переменную класса документа	
		Invalidate(); // обновить вид
	}
	CView::OnLButtonUp(nFlags, point);
}
