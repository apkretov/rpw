#include "stdafx.h"
#ifndef SHARED_HANDLERS
#include "Pr1.h"
#endif
#include "Pr1Doc.h"
#include "Pr1View.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CPr1View, CView)

BEGIN_MESSAGE_MAP(CPr1View, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint) // Standard printing commands
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_KILLFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_CIRCLE, &CPr1View::OnCircle)
END_MESSAGE_MAP()

CPr1View::CPr1View() { }
CPr1View::~CPr1View() { }
BOOL CPr1View::PreCreateWindow(CREATESTRUCT& cs) {	return CView::PreCreateWindow(cs); } // TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs

void CPr1View::OnDraw(CDC* pDC) { // CPr1View drawing
	CPr1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc) return;
	pDC->DrawText(pDoc->m_string, CRect(10, 10, 300, 100), DT_CENTER);
}

BOOL CPr1View::OnPreparePrinting(CPrintInfo* pInfo) {	return DoPreparePrinting(pInfo); /* default preparation*/ } // CPr1View printing
void CPr1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/) { } // TODO: add extra initialization before printing
void CPr1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/) { } // TODO: add cleanup after printing

#ifdef _DEBUG
void CPr1View::AssertValid() const { CView::AssertValid(); }
void CPr1View::Dump(CDumpContext& dc) const { CView::Dump(dc); }

CPr1Doc* CPr1View::GetDocument() const { // non-debug version is inline
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPr1Doc)));
	return (CPr1Doc*)m_pDocument;
}
#endif

void CPr1View::OnSize(UINT nType, int cx, int cy) {
	CView::OnSize(nType, cx, cy);
	AfxMessageBox(L"CPr1View::OnSize: WM_SIZE", MB_ICONINFORMATION);
}

void CPr1View::OnKillFocus(CWnd* pNewWnd) {
	CView::OnKillFocus(pNewWnd);
	AfxMessageBox(L"CPr1View::OnKillFocus: WM_KILLFOCUS", MB_ICONINFORMATION);
}

void CPr1View::DrawLine() {
	CClientDC dc(this);
	int oldMode = dc.SetROP2(R2_NOT); 
	CBrush* oldBrush = (CBrush*)dc.SelectStockObject(NULL_BRUSH); 
	CPen* oldPen = (CPen*) dc.SelectStockObject(BLACK_PEN);
	dc.Rectangle(MouseRect); 
	dc.SelectObject(oldBrush); 
	dc.SelectObject(oldPen); 
	dc.SetROP2(oldMode); 
}

void CPr1View::OnLButtonDown(UINT nFlags, CPoint point) {
	TestDraw = TRUE;
	DrawLine();
	MouseRect.left = point.x;
	MouseRect.top = point.y; 
	MouseRect.right  = point.x;
	MouseRect.bottom  = point.y; 
   SetCapture();
	CView::OnLButtonDown(nFlags, point);
}

void CPr1View::OnMouseMove(UINT nFlags, CPoint point) {
	if (TestDraw)	{
		DrawLine();
		MouseRect.right = point.x; 
		MouseRect.bottom = point.y; 	
		DrawLine();
		CView::OnMouseMove(nFlags, point);
}	}

void CPr1View::OnLButtonUp(UINT nFlags, CPoint point) {
	TestDraw = FALSE;
	ReleaseCapture();
	CView::OnLButtonUp(nFlags, point);
}

void CPr1View::OnCircle() {
	CDC* pDC;
	pDC = GetDC();
	pDC->Ellipse(CRect(10, 10, 100, 100)); 
}