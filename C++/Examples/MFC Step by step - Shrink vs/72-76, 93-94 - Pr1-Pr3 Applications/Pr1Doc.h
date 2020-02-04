#pragma once

class CPr1Doc : public CDocument {
protected: 
	CPr1Doc();
	DECLARE_DYNCREATE(CPr1Doc)
	DECLARE_MESSAGE_MAP() // Generated message map functions
#ifdef SHARED_HANDLERS
	void SetSearchContent(const CString& value); // Helper function that sets search content for a Search Handler
#endif 
public: 
	CString m_string; // Attributes
	CString m_string1;
	CString m_string2;
	CString m_string3;
	virtual BOOL OnNewDocument(); // Overrides
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS
	virtual ~CPr1Doc(); // Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};
