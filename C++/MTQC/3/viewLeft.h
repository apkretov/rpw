#pragma once

class doc;

class viewLeft : public CTreeView {
protected: 
	viewLeft(); // create from serialization only
	virtual void OnInitialUpdate(); // called first time after construct
	DECLARE_DYNCREATE(viewLeft)
	DECLARE_MESSAGE_MAP()
public:
	CImageList treeImages; //Windows Explorer Application - 22. In the header file of the CLeftView class, declare a CImageList variable named. @ http://www.functionx.com/visualc/applications/explorer.htm
	doc* GetDocument() const;
	virtual ~viewLeft(); // Implementation
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	#ifdef _DEBUG
		virtual void AssertValid() const;
		virtual void Dump(CDumpContext& dc) const;
	#endif
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CString getSelectedPath(bool* const ptrBlnHasParent = nullptr) const;
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
	void createConstants();
	afx_msg void OnTvnKeydown(NMHDR *pNMHDR, LRESULT *pResult);
};

#ifndef _DEBUG //debug version in LeftView.cpp
	//inline doc* viewLeft::GetDocument() { return reinterpret_cast<doc*>(m_pDocument); }
	inline doc* viewLeft::GetDocument() const { return reinterpret_cast<doc*>(m_pDocument); }
#endif
