#pragma once

class viewRight : public CListView {
protected: // create from serialization only
	viewRight();
	virtual void OnInitialUpdate(); // called first time after construct
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_DYNCREATE(viewRight)
	DECLARE_MESSAGE_MAP()
public:
	CImageList listImages; //TEST
	virtual ~viewRight();
	doc* GetDocument() const;
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	#ifdef _DEBUG
		virtual void AssertValid() const;
		virtual void Dump(CDumpContext& dc) const;
	#endif
	void setImageList(); //TEST
	void resetConstants();
	void displayConstants();
	void displayConstants(CString strConstant);
	void displayConstants(CString strConstant, CString strSeason);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  
	inline doc* viewRight::GetDocument() const { return reinterpret_cast<doc*>(m_pDocument); } // debug version in mtqcMfcView.cpp
#endif

