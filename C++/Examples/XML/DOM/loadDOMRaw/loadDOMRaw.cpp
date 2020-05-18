#include "stdafx.h" //Include Headers and Libraries Manually @ https://msdn.microsoft.com/en-us/library/ms758753(v=vs.85).aspx
#include <stdio.h>
#include <tchar.h>
#include <msxml6.h>

#define CHK_HR(stmt)        do { hr=(stmt); if (FAILED(hr)) goto CleanUp; } while(0) // Macro that calls a COM method returning HRESULT value.
#define CHK_ALLOC(p)        do { if (!(p)) { hr = E_OUTOFMEMORY; goto CleanUp; } } while(0) // Macro to verify memory allcation.
#define SAFE_RELEASE(p)     do { if ((p)) { (p)->Release(); (p) = NULL; } } while(0) // Macro that releases a COM object if not NULL.

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
	}
	return hr;
}

void loadDOMRaw() {
	HRESULT hr = S_OK;
	IXMLDOMDocument *pXMLDom = NULL;
	IXMLDOMParseError *pXMLErr = NULL;

	BSTR bstrXML = NULL;
	BSTR bstrErr = NULL;
	VARIANT_BOOL varStatus;
	VARIANT varFileName;
	VariantInit(&varFileName);

	CHK_HR(CreateAndInitDOM(&pXMLDom));

	CHK_HR(VariantFromString(L"stocks.xml", varFileName)); // XML file name to load
	CHK_HR(pXMLDom->load(varFileName, &varStatus));
	if (varStatus == VARIANT_TRUE) {
		CHK_HR(pXMLDom->get_xml(&bstrXML));
		printf("XML DOM loaded from stocks.xml:\n%S\n", bstrXML);
	}else{
		CHK_HR(pXMLDom->get_parseError(&pXMLErr)); // Failed to load xml, get last parsing error
		CHK_HR(pXMLErr->get_reason(&bstrErr));
		printf("Failed to load DOM from stocks.xml. %S\n", bstrErr);
	}
CleanUp:
	SAFE_RELEASE(pXMLDom);
	SAFE_RELEASE(pXMLErr);
	SysFreeString(bstrXML);
	SysFreeString(bstrErr);
	VariantClear(&varFileName);
}

int _tmain(int argc, _TCHAR* argv[]) {
	HRESULT hr = CoInitialize(NULL);
	if (SUCCEEDED(hr)) {
		loadDOMRaw();
		CoUninitialize();
	}
	return 0;
}
