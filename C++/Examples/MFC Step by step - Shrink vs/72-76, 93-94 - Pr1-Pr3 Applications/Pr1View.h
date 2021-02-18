#pragma once

class CPr1View : public CView {
	BOOL TestDraw;
	CRect MouseRect;
	void DrawLine();
protected:
	CPr1View();
	DECLARE_DYNCREATE(CPr1View)
	CPr1Doc* GetDocument() const; // Attributes
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	DECLARE_MESSAGE_MAP() // Generated message map functions
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view // Overrides
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual ~CPr1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnCircle();
};

#ifndef _DEBUG  // debug version in Pr1View.cpp
inline CPr1Doc* CPr1View::GetDocument() const { return reinterpret_cast<CPr1Doc*>(m_pDocument); }
#endif

