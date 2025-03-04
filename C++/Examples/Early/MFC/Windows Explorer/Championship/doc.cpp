#include "stdafx.h"
#ifndef SHARED_HANDLERS // SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail and search filter handlers and allows sharing of document code with that project.
	#include "app.h"
#endif
#include "doc.h"
#include <propkey.h>
#include "viewLeft.h" //Pointer to incomplete class type is not allowed @ https://stackoverflow.com/questions/12027656/pointer-to-incomplete-class-type-is-not-allowed
#include "viewRight.h" //TEST //Pointer to incomplete class type is not allowed @ https://stackoverflow.com/questions/12027656/pointer-to-incomplete-class-type-is-not-allowed

#ifdef _DEBUG
	#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(doc, CDocument)

BEGIN_MESSAGE_MAP(doc, CDocument)
END_MESSAGE_MAP()

doc::doc() { /*TODO: add one-time construction code here*/ }
doc::~doc() {}

BOOL doc::OnNewDocument() {
	if (!CDocument::OnNewDocument()) return FALSE; // TODO: add reinitialization code here // (SDI documents will reuse this document)
	this->ptrViewLeft->createConstants(); //Windows Explorer Application - 28. To display the tree when the application comes up, call the above method the pointer to the left view class. @ http://www.functionx.com/visualc/applications/explorer.htm
	this->ptrViewRight->setImageList(); //TEST
	return TRUE;
}

void doc::Serialize(CArchive& ar) { // doc serialization
	if (ar.IsStoring()) { /*TODO: add storing code here*/ }
	else { /*TODO: add loading code here*/ }
}

#ifdef SHARED_HANDLERS
	// Support for thumbnails
	void doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
	{
		// Modify this code to draw the document's data
		dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

		CString strText = _T("TODO: implement thumbnail drawing here");
		LOGFONT lf;

		CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
		pDefaultGUIFont->GetLogFont(&lf);
		lf.lfHeight = 36;

		CFont fontDraw;
		fontDraw.CreateFontIndirect(&lf);

		CFont* pOldFont = dc.SelectObject(&fontDraw);
		dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
		dc.SelectObject(pOldFont);
	}

	// Support for Search Handlers
	void doc::InitializeSearchContent()
	{
		CString strSearchContent;
		// Set search contents from document's data. 
		// The content parts should be separated by ";"

		// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
		SetSearchContent(strSearchContent);
	}

	void doc::SetSearchContent(const CString& value)
	{
		if (value.IsEmpty())
		{
			RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
		}
		else
		{
			CMFCFilterChunkValueImpl *pChunk = NULL;
			ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
			if (pChunk != NULL)
			{
				pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
				SetChunkValue(pChunk);
			}
		}
	}

#endif // SHARED_HANDLERS

#ifdef _DEBUG // doc diagnostics
	void doc::AssertValid() const { CDocument::AssertValid(); }
	void doc::Dump(CDumpContext& dc) const { CDocument::Dump(dc); }
#endif

