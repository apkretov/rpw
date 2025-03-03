#include "stdafx.h"
#ifndef SHARED_HANDLERS // SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail and search filter handlers and allows sharing of document code with that project.
	#include "app.h"
#endif
#include "doc.h"
#include <propkey.h>
#include "viewLeft.h" //Pointer to incomplete class type is not allowed @ https://stackoverflow.com/questions/12027656/pointer-to-incomplete-class-type-is-not-allowed
#include "viewRight.h" //TEST //Pointer to incomplete class type is not allowed @ https://stackoverflow.com/questions/12027656/pointer-to-incomplete-class-type-is-not-allowed
using std::string;
using boost::property_tree::ptree;
#include <boost\property_tree\json_parser.hpp>

#ifdef _DEBUG
	#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(doc, CDocument)

BEGIN_MESSAGE_MAP(doc, CDocument)
END_MESSAGE_MAP()

doc::doc() { //TODO: add one-time construction code here
	/*KTB 
	cPtreeConstants.put("Constants.Account.Client code", "162349"); //TO DO: This code should be moved to doc::OnNewDocument().
	cPtreeConstants.put("Constants.Account.Account", "SPBFUT00gg2");

	cPtreeConstants.put("Constants.Lengths.Length of lots", "6");
	cPtreeConstants.put("Constants.Lengths.Length of price", "6");

	cPtreeConstants.put("Constants.Futures.Contract size", "100");
	cPtreeConstants.put("Constants.Futures.Futures fractional", "false");

	cPtreeConstants.put("Constants.Alligator settings 1.Candles count", "1000");
	cPtreeConstants.put("Constants.Alligator settings 1.Chart offset", "8");

	cPtreeConstants.put("Constants.Alligator settings 2.Candles count", "50");
	cPtreeConstants.put("Constants.Alligator settings 2.Chart offset", "144");
	
	cPtreeConstants.put("Constants.Period.Current period", "0");
	cPtreeConstants.put("Constants.Trade SR.Stock-to-futures adjustment", "-2.5");
	cPtreeConstants.put("Constants.Test without quotes.Stock price", "180.51");
	
	boost::property_tree::write_json(cstrConstantsFile, cPtreeConstants);
	*/
	boost::property_tree::read_json(cstrConstantsFile, cPtreeConstants);
} 

doc::~doc() { if (cblnConstantsChanged) boost::property_tree::write_json(cstrConstantsFile, cPtreeConstants); }

BOOL doc::OnNewDocument() {
	if (!CDocument::OnNewDocument()) return FALSE; // TODO: add reinitialization code here // (SDI documents will reuse this document)
	this->cptrViewLeft->createConstants(); //Windows Explorer Application - 28. To display the tree when the application comes up, call the above method the pointer to the left view class. @ http://www.functionx.com/visualc/applications/explorer.htm
	this->cptrViewRight->setImageList(); //Mine.
	return TRUE;
}

void doc::Serialize(CArchive& ar) { // doc serialization
	if (ar.IsStoring()) { /*TODO: add storing code here*/ }
	else { /*TODO: add loading code here*/ }
}

#ifdef SHARED_HANDLERS
	void doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)	{ // Support for thumbnails
		dc.FillSolidRect(lprcBounds, RGB(255, 255, 255)); // Modify this code to draw the document's data

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

	void doc::InitializeSearchContent()	{ // Support for Search Handlers
		CString strSearchContent;
		SetSearchContent(strSearchContent); // Set search contents from document's data. The content parts should be separated by ";" For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	}

	void doc::SetSearchContent(const CString& value) {
		if (value.IsEmpty()) RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
		else {
			CMFCFilterChunkValueImpl *pChunk = NULL;
			ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
			if (pChunk != NULL) {
				pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
				SetChunkValue(pChunk);
	}	}	}

#endif

#ifdef _DEBUG // doc diagnostics
	void doc::AssertValid() const { CDocument::AssertValid(); }
	void doc::Dump(CDumpContext& dc) const { CDocument::Dump(dc); }
#endif
	
const ptree* const doc::getPtreeConstants() const { return &cPtreeConstants; }

void doc::setConstantsChanged(bool blnConstantsChanged) { cblnConstantsChanged = blnConstantsChanged; }

const viewLeft* const doc::getViewLeft() const { return cptrViewLeft; }
void doc::setViewLeft(viewLeft* ptrViewLeft) { cptrViewLeft = ptrViewLeft; }

const viewRight* const doc::getViewRight() const { return cptrViewRight; }
void doc::setViewRight(viewRight* ptrViewRight) { cptrViewRight = ptrViewRight; }
