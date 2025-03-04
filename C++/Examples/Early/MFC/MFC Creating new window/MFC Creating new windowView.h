
// MFC Creating new windowView.h : interface of the CMFCCreatingnewwindowView class
//

#pragma once


class CMFCCreatingnewwindowView : public CView
{
protected: // create from serialization only
	CMFCCreatingnewwindowView();
	DECLARE_DYNCREATE(CMFCCreatingnewwindowView)

// Attributes
public:
	CMFCCreatingnewwindowDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMFCCreatingnewwindowView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MFC Creating new windowView.cpp
inline CMFCCreatingnewwindowDoc* CMFCCreatingnewwindowView::GetDocument() const
   { return reinterpret_cast<CMFCCreatingnewwindowDoc*>(m_pDocument); }
#endif

