#include "stdafx.h" //Create an XML Document Dynamically (Smart) @ https://msdn.microsoft.com/en-us/library/ms755690(v=vs.85).aspx
#include <stdio.h>
#include <tchar.h>
#import <msxml6.dll>

void dynamDOMsmart() {
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
		pXMLDom->preserveWhiteSpace = VARIANT_TRUE;

		MSXML2::IXMLDOMProcessingInstructionPtr pi = pXMLDom->createProcessingInstruction(L"xml", L"version='1.0'"); // Create a processing instruction targeted for xml.
		pXMLDom->appendChild(pi);

		MSXML2::IXMLDOMCommentPtr pc = pXMLDom->createComment(L"sample xml file created using XML DOM object."); // Create a comment for the document.
		pXMLDom->appendChild(pc);

		MSXML2::IXMLDOMElementPtr pRoot = pXMLDom->createElement(L"root"); // Create the root element (i.e., the documentElement).

		MSXML2::IXMLDOMAttributePtr pa = pXMLDom->createAttribute(L"created"); // Create a "created" attribute for the root element and assign the "using dom" character data as the attribute value.
		pa->value = L"using dom";
		pRoot->setAttributeNode(pa);

		// Next, we will create and add more nodes to the root element we've just created.
		MSXML2::IXMLDOMElementPtr pe = pXMLDom->createElement(L"node1"); // Create an element to hold text content
		pRoot->appendChild(pXMLDom->createTextNode(L"\n\t")); // Add newline + tab for indentation.
		pe->text = L"some character data";
		pRoot->appendChild(pe);

		/*OFF
		pe = pXMLDom->createElement(L"node2"); // Create an element to hold a CDATA section.
		pRoot->appendChild(pXMLDom->createTextNode(L"\n\t")); // Add newline + tab for indentation.
		pe->appendChild(pXMLDom->createCDATASection(L"<some mark-up text>"));
		pRoot->appendChild(pe);

		pe = pXMLDom->createElement(L"node3"); // Create an element to hold three empty subelements
		pRoot->appendChild(pXMLDom->createTextNode(L"\n\t")); // Add newline +tab for indentation.

		MSXML2::IXMLDOMDocumentFragmentPtr pdf = pXMLDom->createDocumentFragment();
		pdf->appendChild(pXMLDom->createTextNode(L"\n\t\t"));
		pdf->appendChild(pXMLDom->createElement(L"subNode1"));
		pdf->appendChild(pXMLDom->createTextNode(L"\n\t\t"));
		pdf->appendChild(pXMLDom->createElement(L"subNode2"));
		pdf->appendChild(pXMLDom->createTextNode(L"\n\t\t"));
		pdf->appendChild(pXMLDom->createElement(L"subNode3"));
		pdf->appendChild(pXMLDom->createTextNode(L"\n\t"));
		pe->appendChild(pdf);
		pRoot->appendChild(pe);

		pRoot->appendChild(pXMLDom->createTextNode(L"\n"));
		*/

		{ //TEST
			pe = pXMLDom->createElement(L"node2"); // Create an element to hold text content
			pRoot->appendChild(pXMLDom->createTextNode(L"\n\t")); // Add newline + tab for indentation.
			pe->text = L"some character data 2";
			pRoot->appendChild(pe);
			pRoot->appendChild(pXMLDom->createTextNode(L"\n")); // Add newline + tab for indentation.
		}

		pXMLDom->appendChild(pRoot); // Add the root element to the DOM instance.

		printf("Dynamically created DOM:\n%s\n", static_cast<PCSTR>(pXMLDom->xml));

		hr = pXMLDom->save(L"dynaDOMsmart.xml");
		if (SUCCEEDED(hr)) printf("DOM saved to dynaDOMsmart.xml\n");
		else printf("Failed to save DOM to dynaDomsmart.xml\n");
	}
	catch (_com_error errorObject) { printf("exception thrown, HRESULT: 0x%08x", errorObject.Error());	}
}

int _tmain(int argc, _TCHAR* argv[]) {
	HRESULT hr = CoInitialize(NULL);
	if (SUCCEEDED(hr)) {
		dynamDOMsmart();
		CoUninitialize();
	}
	return 0;
}