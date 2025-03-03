#include "stdafx.h"
#include <tchar.h>
#include <string>
using std::string;
#include "constatnsXML.h"

#import <msxml6.dll>

#define CHK_HR(stmt) do { hr=(stmt); if (FAILED(hr)) goto CleanUp; } while(0) // Macro that calls a COM method returning HRESULT value.
#define stringise(str_) (#str_)

static MSXML2::IXMLDOMDocumentPtr pXMLDom;

template<typename T> static void queryNode(const string& strNode, T& varNode) { // Query a single node. +------------------------------------------------------------------ +
	const string strRoot = "root/";
	MSXML2::IXMLDOMNodePtr pNode = pXMLDom->selectSingleNode((strRoot + strNode).c_str()); // Query a single node.
	if (pNode) {
		//OFF if (typeid(varNode) == typeid(string))	varNode = pNode->text;
		MessageBox(nullptr, (LPCWSTR)pNode->text, L"readFromXMLSmart", NULL);
	}else MessageBox(nullptr, (LPCWSTR)L"No node is fetched!\n" + pXMLDom->parseError->Getreason(), (LPCWSTR)L"Warining", MB_ICONEXCLAMATION | MB_OK);
}

static void queryNodesSmart(constatnsXML& objConstatnsXML) { // Query Nodes from DOM (Smart) @ https://msdn.microsoft.com/en-us/library/ms761382(v=vs.85).aspx +------------------------------------------------------------------ +
	const string strMT4QuikConnector = "MT4QuikConnector";
	const string strConstatnsXML = strMT4QuikConnector + " - Constatns.xml";
	HRESULT hr = pXMLDom.CreateInstance(__uuidof(MSXML2::DOMDocument60), NULL, CLSCTX_INPROC_SERVER);
	if (FAILED(hr)) {
		MessageBox(nullptr, (LPCWSTR)L"Failed to instantiate an XML DOM!", (LPCWSTR)L"Error", MB_ICONERROR | MB_OK);
		return;
	}
	try {
		pXMLDom->async = VARIANT_FALSE;
		pXMLDom->validateOnParse = VARIANT_FALSE;
		pXMLDom->resolveExternals = VARIANT_FALSE;
		if (pXMLDom->load(strConstatnsXML.c_str()) != VARIANT_TRUE) {
			CHK_HR(pXMLDom->parseError->errorCode);
			MessageBox(nullptr, (LPCWSTR)L"Failed to load DOM from stocks.xml!\n" + pXMLDom->parseError->Getreason(), (LPCWSTR)L"Error", MB_ICONERROR | MB_OK);
		}
		queryNode(stringise(cstrCLASSCODE), objConstatnsXML.getCLASSCODE());
	}
	catch (_com_error errorObject) { MessageBox(nullptr, (LPCWSTR)L"Exception thrown, HRESULT:\n" + errorObject.Error(), (LPCWSTR)L"Error", MB_ICONERROR | MB_OK); }
CleanUp:
	return;
}

void readFromXMLSmart(constatnsXML& objConstatnsXML) { //+------------------------------------------------------------------ +
	HRESULT hr = CoInitialize(NULL);
	if (SUCCEEDED(hr)) {
		queryNodesSmart(objConstatnsXML);
		CoUninitialize();
}	}
