#pragma once

class CRightView : public CListView {
	HANDLE m_hStopEvent; //Creating a Simple Drives Explorer Program - Before you can compile and run the application at this stage, you need to add the m_hStopEvent handle. @ https://www.codeproject.com/Articles/13366/Creating-a-Simple-Drives-Explorer-Program#_articleTop
protected: // create from serialization only
	CRightView();
	DECLARE_DYNCREATE(CRightView)

// Attributes
public:
	CFTreeBrowserDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CRightView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
public:
	CImageList m_ListImages; //Creating a Simple Drives Explorer Program - Before this works, you need to add a class variable. @ https://www.codeproject.com/Articles/13366/Creating-a-Simple-Drives-Explorer-Program#_articleTop
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void ResetFiles();
	void DisplayFiles(LPTSTR Path);
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
};

#ifndef _DEBUG  // debug version in CRightView.cpp
inline CFTreeBrowserDoc* CRightView::GetDocument() const
   { return reinterpret_cast<CFTreeBrowserDoc*>(m_pDocument); }
#endif
