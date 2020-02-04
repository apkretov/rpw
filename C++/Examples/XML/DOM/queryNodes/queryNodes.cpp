#include "stdafx.h"
#include <stdio.h> //Query XML DOM Nodes (C-C++) @ https://msdn.microsoft.com/en-us/library/ms767594(v=vs.85).aspx
#include <tchar.h>
#include <msxml6.h>
#include <atlbase.h> // Includes CComVariant and CComBSTR. //IXMLDOMNode::get_nodeValue @ https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k(MSXML%2FIXMLDOMNode%3A%3Aget_nodeValue);k(IXMLDOMNode%3A%3Aget_nodeValue);k(get_nodeValue);k(DevLang-C%2B%2B);k(TargetOS-Windows)&rd=true
#pragma warning(disable: 4996) //To use the localtime() function instead of a safe localtime_s() suggested. //TO DO: Use the safe localtime_s() function suggested.

#define CHK_HR(stmt) do { hr=(stmt); if (FAILED(hr)) goto CleanUp; } while(0) // Macro that calls a COM method returning HRESULT value.
#define CHK_ALLOC(p) do { if (!(p)) { hr = E_OUTOFMEMORY; goto CleanUp; } } while(0) // Macro to verify memory 
#define SAFE_RELEASE(p) do { if ((p)) { (p)->Release(); (p) = NULL; } } while(0) // Macro that releases a COM object if not NULL.

HRESULT VariantFromString(PCWSTR wszValue, VARIANT &Variant) { // Helper function to create a VT_BSTR variant from a null terminated string. 
	HRESULT hr = S_OK;
	BSTR bstr = SysAllocString(wszValue);
	CHK_ALLOC(bstr);
	V_VT(&Variant) = VT_BSTR;
	V_BSTR(&Variant) = bstr;
CleanUp:
	return hr;
}

HRESULT CreateAndInitDOM(IXMLDOMDocument **ppDoc) { // Helper function to create a DOM instance. 
	HRESULT hr = CoCreateInstance(__uuidof(DOMDocument60), NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(ppDoc));
	if (SUCCEEDED(hr)) {
		(*ppDoc)->put_async(VARIANT_FALSE); // these methods should not fail so don't inspect result
		(*ppDoc)->put_validateOnParse(VARIANT_FALSE);
		(*ppDoc)->put_resolveExternals(VARIANT_FALSE);
		(*ppDoc)->put_preserveWhiteSpace(VARIANT_TRUE);
	}
	return hr;
}

HRESULT ReportParseError(IXMLDOMDocument *pDoc, char *szDesc) { // Helper function to display parse error. It returns error code of the parse error.
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

void queryNodes() {
	HRESULT hr = S_OK;
	IXMLDOMDocument *pXMLDom = NULL;
	IXMLDOMNodeList *pNodes = NULL;
	IXMLDOMNode *pNode = NULL;
	BSTR bstrQuery1 = NULL;
	BSTR bstrQueryTest = NULL; //TEST
	BSTR bstrQuery2 = NULL;
	BSTR bstrNodeName = NULL;
	BSTR bstrNodeValue = NULL;
	VARIANT_BOOL varStatus;
	VARIANT varFileName;
	VariantInit(&varFileName);

	CHK_HR(CreateAndInitDOM(&pXMLDom));
	CHK_HR(VariantFromString(L"stocks.xml", varFileName));
	CHK_HR(pXMLDom->load(varFileName, &varStatus));
	if (varStatus != VARIANT_TRUE) CHK_HR(ReportParseError(pXMLDom, "Failed to load DOM from stocks.xml."));

	/*OFF
	bstrQuery1 = SysAllocString(L"//stock[1]/*"); // Query a single node.
	CHK_ALLOC(bstrQuery1);
	CHK_HR(pXMLDom->selectSingleNode(bstrQuery1, &pNode));
	if (pNode) {
		printf("Result from selectSingleNode:\n");
		CHK_HR(pNode->get_nodeName(&bstrNodeName));
		printf("Node, <%S>:\n", bstrNodeName);
		SysFreeString(bstrNodeName);

		CHK_HR(pNode->get_xml(&bstrNodeValue));
		printf("\t%S\n\n", bstrNodeValue);
		SysFreeString(bstrNodeValue);
		SAFE_RELEASE(pNode);
	}
	else CHK_HR(ReportParseError(pXMLDom, "Error while calling selectSingleNode."));
	*/
	
	{ //TEST
		printf("\n");
		bstrQueryTest = SysAllocString(L"portfolio/test");
		CHK_ALLOC(bstrQueryTest);
		CHK_HR(pXMLDom->selectSingleNode(bstrQueryTest, &pNode));
		if (pNode) {
			//OFF printf("Result from selectSingleNode test:\n");
			CHK_HR(pNode->get_nodeName(&bstrNodeName));
			//OFF printf("Node, <%S>:\n", bstrNodeName);
			//TEST printf("<%S>:\n", bstrNodeName);
			SysFreeString(bstrNodeName);

			CHK_HR(pNode->get_xml(&bstrNodeValue));
			//OFF printf("\t%S\n\n", bstrNodeValue);
			printf("%S\n", bstrNodeValue); //TEST 
			{ //TEST //IXMLDOMNode::get_nodeValue @ https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k(MSXML%2FIXMLDOMNode%3A%3Aget_nodeValue);k(IXMLDOMNode%3A%3Aget_nodeValue);k(get_nodeValue);k(DevLang-C%2B%2B);k(TargetOS-Windows)&rd=true
				CComVariant varNodeValue; 
				hr = pNode->get_nodeValue(&varNodeValue);
				if (FAILED(hr)) goto CleanUp;
				{ //MSXML2: How can I get value of a node? @ http://stackoverflow.com/questions/5966771/msxml2-how-can-i-get-value-of-a-node
					BSTR myBstr = L""; //Initialize a BSTR @ http://www.tek-tips.com/viewthread.cfm?qid=938639
					pNode->get_text(&myBstr);
					{ //How do you efficiently copy BSTR to wchar_t[]? @ http://stackoverflow.com/questions/71980/how-do-you-efficiently-copy-bstr-to-wchar-t
						UINT length = SysStringLen(myBstr);        // Ask COM for the size of the BSTR
						wchar_t *myString = new wchar_t[length+1]; // Note: SysStringLen doesn't include the space needed for the NULL
						wcscpy(myString, myBstr);                  // Or your favorite safer string function
						printf("myBstr = %S\n", myString);			 //...
						delete myString; // Done
					}
				}
			}
			SysFreeString(bstrNodeValue);
			SAFE_RELEASE(pNode);
		}
		else CHK_HR(ReportParseError(pXMLDom, "Error while calling selectSingleNode."));
	}
	
	/*OFF
	bstrQuery2 = SysAllocString(L"//stock[1]/*"); // Query a node-set.
	CHK_ALLOC(bstrQuery2);
	CHK_HR(pXMLDom->selectNodes(bstrQuery2, &pNodes));
	if (pNodes) {
		printf("Results from selectNodes:\n");
		long length; //get the length of node-set
		CHK_HR(pNodes->get_length(&length));
		for (long i = 0; i < length; i++) {
			CHK_HR(pNodes->get_item(i, &pNode));
			CHK_HR(pNode->get_nodeName(&bstrNodeName));
			printf("Node (%d), <%S>:\n", i, bstrNodeName);
			SysFreeString(bstrNodeName);

			CHK_HR(pNode->get_xml(&bstrNodeValue));
			printf("\t%S\n", bstrNodeValue);
			SysFreeString(bstrNodeValue);
			SAFE_RELEASE(pNode);
	}	}
	else CHK_HR(ReportParseError(pXMLDom, "Error while calling selectNodes."));
	*/
	
CleanUp:	{
	SAFE_RELEASE(pXMLDom);
	SAFE_RELEASE(pNodes);
	SAFE_RELEASE(pNode);
	SysFreeString(bstrQuery1);
	SysFreeString(bstrQuery2);
	SysFreeString(bstrNodeName);
	SysFreeString(bstrNodeValue);
	VariantClear(&varFileName);
}}

int _tmain(int argc, _TCHAR* argv[]) {
	HRESULT hr = CoInitialize(NULL);
	if (SUCCEEDED(hr)) {
		queryNodes();
		CoUninitialize();
	}
	return 0;
}