#pragma once

class CLeftView; //Creating a Simple Drives Explorer Program - In the Workspace pane, click on the FileView tab. Open up the Header Files folder and open the file FTreeBrowserDoc.h. In this file, insert the lines... @ https://www.codeproject.com/Articles/13366/Creating-a-Simple-Drives-Explorer-Program#_articleTop
class CRightView;

class CFTreeBrowserDoc : public CDocument {
protected: // create from serialization only
	CFTreeBrowserDoc();
	DECLARE_DYNCREATE(CFTreeBrowserDoc)

// Attributes
public:

// Operations
public:
	CLeftView *pLeftView; //Creating a Simple Drives Explorer Program - In the Workspace pane, click on the FileView tab. Open up the Header Files folder and open the file FTreeBrowserDoc.h. In this file, insert the lines... @ https://www.codeproject.com/Articles/13366/Creating-a-Simple-Drives-Explorer-Program#_articleTop
	CRightView *pRightView;

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CFTreeBrowserDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
