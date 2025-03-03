#include "stdafx.h"
#include <stdio.h> //Query XML DOM Nodes (C-C++) @ https://msdn.microsoft.com/en-us/library/ms767594(v=vs.85).aspx
#include <tchar.h>
#include <msxml6.h>
#include <atlbase.h> // Includes CComVariant and CComBSTR. //IXMLDOMNode::get_nodeValue @ https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k(MSXML%2FIXMLDOMNode%3A%3Aget_nodeValue);k(IXMLDOMNode%3A%3Aget_nodeValue);k(get_nodeValue);k(DevLang-C%2B%2B);k(TargetOS-Windows)&rd=true
#include <memory>
#include <string>
using std::string;
using std::wstring;
#include "constatnsXML.h"

#pragma warning(disable: 4996) //To use the localtime() function instead of a safe localtime_s() suggested. //TO DO: Use the safe localtime_s() function suggested.

#define CHK_HR(stmt) do { hr=(stmt); if (FAILED(hr)) goto CleanUp; } while(0) // Macro that calls a COM method returning HRESULT value.
#define CHK_ALLOC(p) do { if (!(p)) { hr = E_OUTOFMEMORY; goto CleanUp; } } while(0) // Macro to verify memory 
#define SAFE_RELEASE(p) do { if ((p)) { (p)->Release(); (p) = NULL; } } while(0) // Macro that releases a COM object if not NULL.
//KTB #define stringise(str_) (#str_)

extern const wstring gstrMT4QuikConnector;

void messageException(const std::exception& objException);

static HRESULT VariantFromString(PCWSTR wszValue, VARIANT &Variant) { // Helper function to create a VT_BSTR variant from a null terminated string. //+------------------------------------------------------------------ +
	HRESULT hr = S_OK;
	BSTR bstr = SysAllocString(wszValue);
	CHK_ALLOC(bstr);
	V_VT(&Variant) = VT_BSTR;
	V_BSTR(&Variant) = bstr;
CleanUp:
	return hr;
}

static HRESULT CreateAndInitDOM(IXMLDOMDocument **ppDoc) { // Helper function to create a DOM instance.  //+------------------------------------------------------------------ +
	HRESULT hr = CoCreateInstance(__uuidof(DOMDocument60), NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(ppDoc));
	if (SUCCEEDED(hr)) {
		(*ppDoc)->put_async(VARIANT_FALSE); // these methods should not fail so don't inspect result
		(*ppDoc)->put_validateOnParse(VARIANT_FALSE);
		(*ppDoc)->put_resolveExternals(VARIANT_FALSE);
		(*ppDoc)->put_preserveWhiteSpace(VARIANT_TRUE);
	}
	return hr;
}

static HRESULT ReportParseError(IXMLDOMDocument *pDoc, char *szDesc) { // Helper function to display parse error. It returns error code of the parse error. //+------------------------------------------------------------------ +
	HRESULT hr = S_OK;
	HRESULT hrRet = E_FAIL; // Default error code if failed to get from parse error.
	IXMLDOMParseError *pXMLErr = NULL;
	BSTR bstrReason = NULL;

	CHK_HR(pDoc->get_parseError(&pXMLErr));
	CHK_HR(pXMLErr->get_errorCode(&hrRet));
	CHK_HR(pXMLErr->get_reason(&bstrReason));
	printf("%s\n%S\n", szDesc, bstrReason);

CleanUp:
	SAFE_RELEASE(pXMLErr);
	SysFreeString(bstrReason);
	return hrRet;
}

static wstring queryNodes(const wstring& strNode) { //+------------------------------------------------------------------ +
	try {
		const wstring strConstatnsXML = gstrMT4QuikConnector + L" - Constatns.xml";	
		const wstring strRoot = L"root/";
		HRESULT hr = S_OK;
		IXMLDOMDocument *pXMLDom = NULL;
		IXMLDOMNodeList *pNodes = NULL;
		IXMLDOMNode *pNode = NULL;
		BSTR bstrQuery = NULL, bstrNodeName = NULL, bstrNodeValue = NULL;
		VARIANT_BOOL varStatus;
		VARIANT varFileName;
	
		VariantInit(&varFileName);
		CHK_HR(CreateAndInitDOM(&pXMLDom));
		CHK_HR(VariantFromString(strConstatnsXML.c_str(), varFileName));
		CHK_HR(pXMLDom->load(varFileName, &varStatus));
		if (varStatus != VARIANT_TRUE) CHK_HR(ReportParseError(pXMLDom, "Failed to load DOM from stocks.xml."));

		bstrQuery = SysAllocString( (strRoot + strNode).c_str() ); //How to convert char * to const OLECHAR * so as to be used in SYSALLOCSTRING()? @ http://stackoverflow.com/questions/36542277/how-to-convert-char-to-const-olechar-so-as-to-be-used-in-sysallocstring
		CHK_ALLOC(bstrQuery);
		CHK_HR(pXMLDom->selectSingleNode(bstrQuery, &pNode));
		if (pNode) {
			CHK_HR(pNode->get_nodeName(&bstrNodeName)); //Result from selectSingleNode. Get a node name.
			SysFreeString(bstrNodeName);
	
			CHK_HR(pNode->get_xml(&bstrNodeValue)); //Get a node value.
			{ //IXMLDOMNode::get_nodeValue @ https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k(MSXML%2FIXMLDOMNode%3A%3Aget_nodeValue);k(IXMLDOMNode%3A%3Aget_nodeValue);k(get_nodeValue);k(DevLang-C%2B%2B);k(TargetOS-Windows)&rd=true
				CComVariant varNodeValue; 
				hr = pNode->get_nodeValue(&varNodeValue);
				if (FAILED(hr)) goto CleanUp;
				{ //MSXML2: How can I get value of a node? @ http://stackoverflow.com/questions/5966771/msxml2-how-can-i-get-value-of-a-node
					BSTR myBstr = L""; //Initialize a BSTR @ http://www.tek-tips.com/viewthread.cfm?qid=938639
					pNode->get_text(&myBstr); //Get the value of a node.
					/*KTB { //How do you efficiently copy BSTR to wchar_t[]? @ http://stackoverflow.com/questions/71980/how-do-you-efficiently-copy-bstr-to-wchar-t
						UINT intLength = SysStringLen(myBstr);        // Ask COM for the size of the BSTR
						wchar_t *myString = new wchar_t[intLength + 1]; // Note: SysStringLen doesn't include the space needed for the NULL
						wcscpy(myString, myBstr);                  // Or your favorite safer string function
						//MessageBox(nullptr, myString, charToLPCWSTR(strMT4QuikConnector.c_str()), 0); 
						MessageBox(nullptr, myString, strMT4QuikConnector.c_str(), 0); 
						delete myString; // Done
					}*/
					//MessageBox(nullptr, myBstr, gstrMT4QuikConnector.c_str(), 0); 
					return myBstr;
			}	}
			SysFreeString(bstrNodeValue);
			SAFE_RELEASE(pNode);
		}
		else CHK_HR(ReportParseError(pXMLDom, "Error while calling selectSingleNode."));
		return nullptr;
		CleanUp:	{
			SAFE_RELEASE(pXMLDom);
			SAFE_RELEASE(pNodes);
			SAFE_RELEASE(pNode);
			SysFreeString(bstrQuery);
			SysFreeString(bstrNodeName);
			SysFreeString(bstrNodeValue);
			VariantClear(&varFileName);
			return nullptr;
	}	} 
	catch (const std::exception& objException) { 
		messageException(objException);
		return nullptr;
}	}

void readFromXML(constatnsXML& objConstatnsXML) { //+------------------------------------------------------------------ +
	HRESULT hr = CoInitialize(NULL);
	if (SUCCEEDED(hr)) {
		//KTB objConstatnsXML.setCLASSCODE(queryNodes(objConstatnsXML.getCLASSCODName()));
		//KTB objConstatnsXML.setFutures(queryNodes(objConstatnsXML.getFuturesName()));
		//MessageBox(NULL, objConstatnsXML.getFutures().c_str(), L"", NULL);
		//KTB objConstatnsXML.setTradeDisabled(queryNodes(objConstatnsXML.getTradeDisabledName()));
		//MessageBox(NULL, std::to_wstring(objConstatnsXML.getTradeDisabled()).c_str(), L"", NULL);
		CoUninitialize();
}	}