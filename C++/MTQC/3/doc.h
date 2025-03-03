#pragma once

class viewLeft; //Pointer to incomplete class type is not allowed @ https://stackoverflow.com/questions/12027656/pointer-to-incomplete-class-type-is-not-allowed
class viewRight; 

class doc : public CDocument {
	const std::string cstrConstantsFile = "MTQC - Constants.json";
	boost::property_tree::ptree cPtreeConstants;
	bool cblnConstantsChanged{};

	viewLeft* cptrViewLeft;
	viewRight* cptrViewRight; //Windows Explorer Application - 11. Declare a pointer to each view class as follows. @ http://www.functionx.com/visualc/applications/explorer.htm 

protected: 
	doc();
	DECLARE_DYNCREATE(doc)
	DECLARE_MESSAGE_MAP()
	#ifdef SHARED_HANDLERS
		void SetSearchContent(const CString& value); // Helper function that sets search content for a Search Handler
	#endif

public:
	virtual ~doc();
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	#ifdef SHARED_HANDLERS
		virtual void InitializeSearchContent();
		virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
	#endif
	#ifdef _DEBUG
		virtual void AssertValid() const;
		virtual void Dump(CDumpContext& dc) const;
	#endif
	
	const boost::property_tree::ptree* const getPtreeConstants() const; //The const qualifiyer prevents outside modifications to cPtreeConstants. The constness is redundant and used for practice. //Resume
	void setConstantsChanged(bool blnConstantsChanged);

	const viewLeft* const getViewLeft() const;
	void setViewLeft(viewLeft* ptrViewLeft);
	
	const viewRight* const getViewRight() const; //The const qualifiyer prevents outside modifications to cPtreeConstants. The constness is redundant and used for practice. //Resume
	void setViewRight(viewRight* ptrViewRight);
};
