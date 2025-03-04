#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
	#include "FTreeBrowser.h"
#endif
#include "FTreeBrowserDoc.h"
#include <propkey.h>
#include "LeftView.h"

#ifdef _DEBUG
	#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CFTreeBrowserDoc, CDocument)

BEGIN_MESSAGE_MAP(CFTreeBrowserDoc, CDocument)
END_MESSAGE_MAP()

CFTreeBrowserDoc::CFTreeBrowserDoc() {	/*TODO: add one-time construction code here*/ }

CFTreeBrowserDoc::~CFTreeBrowserDoc() {}

BOOL CFTreeBrowserDoc::OnNewDocument() {
	if (!CDocument::OnNewDocument())	return FALSE;
	// TODO: add reinitialization code here (SDI documents will reuse this document)
	this->pLeftView->CreateRoots(); //Creating a Simple Drives Explorer Program - Place a call to the CreateRoots function here. @ https://www.codeproject.com/Articles/13366/Creating-a-Simple-Drives-Explorer-Program#_articleTop
	return TRUE;
}


void CFTreeBrowserDoc::Serialize(CArchive& ar) { // CFTreeBrowserDoc serialization
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CFTreeBrowserDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CFTreeBrowserDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CFTreeBrowserDoc::SetSearchContent(const CString& value)
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

// CFTreeBrowserDoc diagnostics

#ifdef _DEBUG
void CFTreeBrowserDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFTreeBrowserDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CFTreeBrowserDoc commands
