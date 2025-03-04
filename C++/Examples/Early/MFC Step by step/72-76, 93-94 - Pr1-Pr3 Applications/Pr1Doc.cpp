
// Pr1Doc.cpp : implementation of the CPr1Doc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Pr1.h"
#endif

#include "Pr1Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPr1Doc

IMPLEMENT_DYNCREATE(CPr1Doc, CDocument)

BEGIN_MESSAGE_MAP(CPr1Doc, CDocument)
END_MESSAGE_MAP()


// CPr1Doc construction/destruction

CPr1Doc::CPr1Doc()
{
	// TODO: add one-time construction code here

}

CPr1Doc::~CPr1Doc()
{
}

BOOL CPr1Doc::OnNewDocument() {
	if (!CDocument::OnNewDocument())	return FALSE;
	m_string = L"Первые шаги - лучший сайт!";
	m_string1 = L"String1";
	m_string2 = L"String2";
	m_string3 = L"String3 Finish String";
	return TRUE;
}

void CPr1Doc::Serialize(CArchive& ar) { // CPr1Doc serialization
	if (ar.IsStoring()) { //Storing.
		ar << m_string1;
		ar << m_string2;
		ar << m_string3;
	} else { //Loading.
		ar >> m_string1;
		ar >> m_string2;
		ar >> m_string3;
}	}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CPr1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CPr1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CPr1Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk !=  NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CPr1Doc diagnostics

#ifdef _DEBUG
void CPr1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPr1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPr1Doc commands
