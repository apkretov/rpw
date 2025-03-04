#pragma once

class viewRight; 
class viewLeft; //Pointer to incomplete class type is not allowed @ https://stackoverflow.com/questions/12027656/pointer-to-incomplete-class-type-is-not-allowed

class doc : public CDocument {
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
	viewRight* ptrViewRight; //Windows Explorer Application - 11. Declare a pointer to each view class as follows. @ http://www.functionx.com/visualc/applications/explorer.htm 
	viewLeft* ptrViewLeft;
};
