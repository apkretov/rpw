#pragma once

class viewRight : public CListView {
	const int cintColWidth = 200;
	void editSelectedConstant();

protected:
	viewRight();
	virtual void OnInitialUpdate(); // called first time after construct
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_DYNCREATE(viewRight)
	DECLARE_MESSAGE_MAP()

public:
	CImageList listImages;
	
	virtual ~viewRight();
	doc* GetDocument() const;
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	#ifdef _DEBUG
		virtual void AssertValid() const;
		virtual void Dump(CDumpContext& dc) const;
	#endif
	
	void setImageList();
	void resetConstants();
	void displayRoot(const CString& strRoot);
	void displayGroup(const boost::property_tree::ptree& ptreeGroup);

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnKeydown(NMHDR *pNMHDR, LRESULT *pResult);
};

#ifndef _DEBUG  
	inline doc* viewRight::GetDocument() const { return reinterpret_cast<doc*>(m_pDocument); } // debug version in mtqcMfcView.cpp
#endif

