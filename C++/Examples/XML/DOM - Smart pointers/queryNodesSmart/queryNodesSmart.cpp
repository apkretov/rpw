#include "stdafx.h" //Query Nodes from DOM (Smart) @ https://msdn.microsoft.com/en-us/library/ms761382(v=vs.85).aspx
#include <stdio.h>
#include <tchar.h>
#import <msxml6.dll>

#define CHK_HR(stmt)        do { hr=(stmt); if (FAILED(hr)) goto CleanUp; } while(0) // Macro that calls a COM method returning HRESULT value.

void queryNodesSmart() {
	MSXML2::IXMLDOMDocumentPtr pXMLDom;
	HRESULT hr = pXMLDom.CreateInstance(__uuidof(MSXML2::DOMDocument60), NULL, CLSCTX_INPROC_SERVER);
	if (FAILED(hr)) {
		printf("Failed to instantiate an XML DOM.\n");
		return;
	}
	try {
		pXMLDom->async = VARIANT_FALSE;
		pXMLDom->validateOnParse = VARIANT_FALSE;
		pXMLDom->resolveExternals = VARIANT_FALSE;

		//ORIG if (pXMLDom->load(L"stocks.xml") != VARIANT_TRUE) {
		if (pXMLDom->load(L"dynaDOMsmart.xml") != VARIANT_TRUE) { //TEST
			CHK_HR(pXMLDom->parseError->errorCode);
			printf("Failed to load DOM from stocks.xml.\n%s\n",
				(LPCSTR)pXMLDom->parseError->Getreason());
		}

		/*OFF
		MSXML2::IXMLDOMNodePtr pNode = pXMLDom->selectSingleNode(L"//stock[1]/*"); // Query a single node.
		if (pNode) printf("Result from selectSingleNode:\nNode, <%s>:\n\t%s\n\n", (LPCSTR)pNode->nodeName, (LPCSTR)pNode->xml);
		else printf("No node is fetched.\n");
		*/

		{ //TEST
			MSXML2::IXMLDOMNodePtr pNode = pXMLDom->selectSingleNode(/*L"portfolio/test"*/ L"root/node1"); // Query a single node.
			//OFF if (pNode) printf("Result from selectSingleNode test:\nNode, <%s>:\n\t%s\n\n", (LPCSTR)pNode->nodeName, (LPCSTR)pNode->xml);
			if (pNode) printf("%s\n\n", (LPCSTR)pNode->text);
			else printf("No node is fetched.\n");

			pNode = pXMLDom->selectSingleNode(/*L"portfolio/test2"*/ L"root/node2"); // Query a single node.
			//OFF if (pNode) printf("Result from selectSingleNode test:\nNode, <%s>:\n\t%s\n\n", (LPCSTR)pNode->nodeName, (LPCSTR)pNode->xml);
			if (pNode) printf("%s\n\n", (LPCSTR)pNode->text);
			else printf("No node is fetched.\n");
		}

		/*OFF
		MSXML2::IXMLDOMNodeListPtr pnl = pXMLDom->selectNodes(L"//stock[1]/*"); // Query a node-set.
		if (pnl) {
			printf("Results from selectNodes:\n");
			for (long i = 0; i < pnl->length; i++) {
				pNode = pnl->item[i];
				printf("Node (%d), <%s>:\n\t%s\n", i, (LPCSTR)pNode->nodeName, (LPCSTR)pnl->item[i]->xml);
			}
		}
		else printf("No node set is fetched.\n");
		*/
	}
	catch (_com_error errorObject) { printf("Exception thrown, HRESULT: 0x%08x", errorObject.Error()); }
CleanUp:
	return;
}

int _tmain(int argc, _TCHAR* argv[]) {
	HRESULT hr = CoInitialize(NULL);
	if (SUCCEEDED(hr)) {
		queryNodesSmart();
		CoUninitialize();
	}
	return 0;
}