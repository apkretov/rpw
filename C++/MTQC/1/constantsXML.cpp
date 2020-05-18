#include "constantsXML.h"
using std::string;
using std::wstring;
#include <exception>
using std::exception;
#include "messages.h"
#include "functions.h"
using namespace mtqc::functions;
#include "constants.h"
using namespace mtqc::constants;

namespace mtqc {
	//To enable DLL exporting, the Original Runtime Library property "Multi-threaded Debug (/MTd)" changed to "Multi-threaded Debug DLL (/MDd)" 
	//Debug Assertion Failed! Expression: __acrt_first_block == header @ https://stackoverflow.com/questions/35310117/debug-assertion-failed-expression-acrt-first-block-header // /MD, /MT, /LD (Use Run-Time Library) @ https://docs.microsoft.com/en-us/cpp/build/reference/md-mt-ld-use-run-time-library 
	
	/*inline*/ wstring constantsXML::getCLASSCODE() const { return cstrCLASSCODE; } 
	
	/*inline*/ void constantsXML::setCLASSCODE(const wstring& strCLASSCODE) { cstrCLASSCODE = strCLASSCODE; } 

	wstring constantsXML::getStock() const { return cstrStock; } 
	void constantsXML::setStock(const wstring& strStock) { cstrStock = strStock; } 

	wstring constantsXML::getFutures() const { return cstrFutures; }  //TO DO: Create string counterparts for all wstring's.
	void constantsXML::setFutures(const wstring& strFutures) { cstrFutures = strFutures; } 

	// Make sure a member is available and filled in. 
	//TO DO: Make this check at the stage of reading a node from the XML file. Also check there if the file is available at all.
	bool constantsXML::isEmpty(const wstring& strMember, const wstring& strMemberName) const {
		if (!strMember.empty()) 
			return false;
		else {
			MessageBox(
				NULL, 
				(string("The ") + wstringToString(strMemberName) + " member is empty or not found in the XML file. It will be ignored.").c_str(), 
				STR_PROJECT_NAME, 
				MB_ICONWARNING
			);
			return true;
		}
	}

	inline bool constantsXML::stringToBool(const wstring& str1true_0false) const { 
		return stoi(str1true_0false) == NULL ? false : true; 
	}
																													
	bool constantsXML::getTradeSR() const { 
		return cblnTradeSR; 
	} 
	
	void constantsXML::setTradeSR(bool blnTRADE_SR) { 
		cblnTradeSR = blnTRADE_SR; 
	} 
	
	void constantsXML::setTradeSR(const wstring& str1true_0false) { 
		if (!isEmpty(str1true_0false, cstrTradeSRName)) 
			cblnTradeSR = stringToBool(str1true_0false);
	}

	double constantsXML::getStockPoint() const { 
		return cdblStockPoint; 
	} 
	
	void constantsXML::setStockPoint(double dblStockPoint) { 
		dblStockPoint = dblStockPoint; 
	} 
	
	//How to convert std::wstring to numeric type(int, long, float)? @ http://stackoverflow.com/questions/5118308/how-to-convert-stdwstring-to-numeric-typeint-long-float 
	void constantsXML::setStockPoint(const wstring& strStockPoint) { 
		if (!isEmpty(strStockPoint, cstrStockPointName)) 
			cdblStockPoint = stod(strStockPoint); 
	} 

	wstring constantsXML::getStockTagPrice() const { 
		return cstrStockTagPrice; 
	} 
	
	void constantsXML::setStockTagPrice(const wstring& strStockTagPrice) { 
		if (!isEmpty(strStockTagPrice, cstrStockTagPriceName)) 
			cstrStockTagPrice = strStockTagPrice; 
	}

	wstring constantsXML::getStockTagAlg() const { 
		return cstrStockTagAlg; 
	} 
	
	void constantsXML::setStockTagAlg(const wstring& strStockTagAlg) { 
		if (!isEmpty(strStockTagAlg, cstrStockTagAlgName)) 
			cstrStockTagAlg = strStockTagAlg; 
	}

	int constantsXML::getFuturesPoint() const { 
		return cintFuturesPoint; 
	} 
	
	void constantsXML::setFuturesPoint(int intFuturesPoint) { 
		cintFuturesPoint = intFuturesPoint; 
	} 
	
	//How to convert std::wstring to numeric type(int, long, float)? @ http://stackoverflow.com/questions/5118308/how-to-convert-stdwstring-to-numeric-typeint-long-float 
	void constantsXML::setFuturesPoint(const wstring& strFuturesPoint) { 
		if (!isEmpty(strFuturesPoint, cstrFuturesPointName)) 
			cintFuturesPoint = stoi(strFuturesPoint); 
	} 

	wstring constantsXML::getFuturesTagPrice() const { 
		return cstrFuturesTagPrice; 
	} 
	
	void constantsXML::setFuturesTagPrice(const wstring& strFuturesTagPrice) { 
		if (!isEmpty(strFuturesTagPrice, cstrFuturesTagPriceName)) 
			cstrFuturesTagPrice = strFuturesTagPrice; 
	} 

	wstring constantsXML::getFuturesTagAlg() const { 
		return cstrFuturesTagAlg; 
	} 
	
	void constantsXML::setFuturesTagAlg(const wstring& strFuturesTagAlg) { 
		if (!isEmpty(strFuturesTagAlg, cstrFuturesTagAlgName)) 
			cstrFuturesTagAlg = strFuturesTagAlg; 
	}

	int constantsXML::getLotsTraded() const {	
		return cintLotsTraded; 
	} 
	
	void constantsXML::setLotsTraded(int intLotsTraded) { 
		cintLotsTraded = intLotsTraded; 
	} 
	
	void constantsXML::setLotsTraded(const wstring& strLotsTraded) { 
		if (!isEmpty(strLotsTraded, cstrLotsTradedName)) 
			cintLotsTraded = stoi(strLotsTraded); 
	} 

	int constantsXML::getLotsMax() const {	
		return cintLotsMax; 
	} 
	
	void constantsXML::setLotsMax(int intLotsMax) { 
		cintLotsMax = intLotsMax; 
	} 
	
	void constantsXML::setLotsMax(const wstring& strLotsMax) { 
		if (!isEmpty(strLotsMax, cstrLotsMaxName)) 
			cintLotsMax = stoi(strLotsMax); 
	} 

	bool constantsXML::getTradeDisabled() const { 
		return cblnTradeDisabled; 
	} 

	void constantsXML::setTradeDisabled(bool blnTradeDisabled) { 
		cblnTradeDisabled = blnTradeDisabled; 
	} 

	void constantsXML::setTradeDisabled(const wstring& str1true_0false){ 
		if (!isEmpty(str1true_0false, cstrTradeDisabledName)) 
			cblnTradeDisabled = stringToBool(str1true_0false); 
	} 

	bool constantsXML::getAllMessages() const { 
		return cblnAllMessages; 
	} 
	
	void constantsXML::setAllMessages(bool blnAllMessages) { 
		cblnAllMessages = blnAllMessages; 
	} 
	
	void constantsXML::setAllMessages(const wstring& str1true_0false){ 
		if (!isEmpty(str1true_0false, cstrAllMessagesName)) 
			cblnAllMessages = stringToBool(str1true_0false); 
	}

	int constantsXML::getResumeRange() const { 
		return cintResumeRange; 
	} 
	
	void constantsXML::setResumeRange(int intResumeRange) { 
		cintResumeRange = intResumeRange; 
	} 
	
	void constantsXML::setResumeRange(const wstring& strResumeRange) { 
		if (!isEmpty(strResumeRange, cstrResumeRangeName)) 
			cintResumeRange = stoi(strResumeRange); 
	}

	void constantsXML::destroy() { 
		delete this; 
	}
}

namespace mtqc {
	//Exporting C++ classes from a DLL @ http://eli.thegreenplace.net/2011/09/16/exporting-c-classes-from-a-dll/
	extern "C" MTQC_API constantsXMLv* __cdecl createConstantsXML() { 
		return new constantsXML; 
	} 
}

//+------------------------------------------------------------------------------------------------------------------------------------------------------------------- +
// This code originally resided in readWriteXML.cpp that contained where writeNodesToXML and writeXML were friend functions. The code has been moved here to export this class via DLL because the friend functions didn't work like that. 
#include <msxml6.h> //Query XML DOM Nodes (C-C++) @ https://msdn.microsoft.com/en-us/library/ms767594(v=vs.85).aspx
#include <atlbase.h> // Includes CComVariant and CComBSTR. //IXMLDOMNode::get_nodeValue @ https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k(MSXML%2FIXMLDOMNode%3A%3Aget_nodeValue);k(IXMLDOMNode%3A%3Aget_nodeValue);k(get_nodeValue);k(DevLang-C%2B%2B);k(TargetOS-Windows)&rd=true
using std::to_wstring;
	
#pragma warning(disable: 4996) //To use the localtime() function instead of a safe localtime_s() suggested. //TO DO: Use the safe localtime_s() function suggested.

#define CHK_HR(stmt) do { hr=(stmt); if (FAILED(hr)) goto CleanUp; } while(0) // Macro that calls a COM method returning HRESULT value.
#define CHK_ALLOC(p) do { if (!(p)) { hr = E_OUTOFMEMORY; goto CleanUp; } } while(0) // Macro to verify memory 
#define SAFE_RELEASE(p) do { if ((p)) { (p)->Release(); (p) = NULL; } } while(0) // Macro that releases a COM object if not NULL.

namespace mtqc {
	namespace constantsXML_ {

		const wstring mstrConstantsXML = stringToWstring(gstrMTQC) + L" - ConstantsXML.xml";
		const wstring mstrRoot = L"root";

		// Helper function to create a VT_BSTR variant from a null terminated string. 
		static HRESULT VariantFromString(PCWSTR wszValue, VARIANT &Variant) { 
			HRESULT hr = S_OK;
			BSTR bstr = SysAllocString(wszValue);
			CHK_ALLOC(bstr);
			V_VT(&Variant) = VT_BSTR;
			V_BSTR(&Variant) = bstr;
		CleanUp:
			return hr;
		}

		// Helper function to create a DOM instance.  
		static HRESULT CreateAndInitDOM(IXMLDOMDocument **ppDoc) { 
			HRESULT hr{};
			try {
				//An error occurs here when the function is first invoked. The second consequent call passes successfully. Let Microsoft be responsible for that. 
				//I'll use it for the time being like this.
				hr = CoCreateInstance(__uuidof(DOMDocument60), NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(ppDoc)); 
				
				if (SUCCEEDED(hr)) {
					(*ppDoc)->put_async(VARIANT_FALSE); // these methods should not fail so don't inspect result
					(*ppDoc)->put_validateOnParse(VARIANT_FALSE);
					(*ppDoc)->put_resolveExternals(VARIANT_FALSE);
					(*ppDoc)->put_preserveWhiteSpace(VARIANT_TRUE);
				}
			}
			
			catch (const std::exception& objException) { 
				messages::messageException(objException, __FUNCTION__, __LINE__);	
			}	
			
			return hr;
		}

		// Helper function to display parse error. It returns error code of the parse error. 
		static HRESULT ReportParseError(IXMLDOMDocument *pDoc, char *szDesc) { 
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

		static wstring queryNodes(const wstring& strNode) { 
			try {
				HRESULT hr = S_OK;
				IXMLDOMDocument *pXMLDom = NULL;
				IXMLDOMNodeList *pNodes = NULL;
				IXMLDOMNode *pNode = NULL;
				BSTR bstrQuery = NULL, bstrNodeName = NULL, bstrNodeValue = NULL;
				VARIANT_BOOL varStatus;
				VARIANT varFileName;
	
				VariantInit(&varFileName);
				CHK_HR(CreateAndInitDOM(&pXMLDom));
				CHK_HR(VariantFromString(mstrConstantsXML.c_str(), varFileName));
				CHK_HR(pXMLDom->load(varFileName, &varStatus));
				if (varStatus != VARIANT_TRUE) CHK_HR(ReportParseError(pXMLDom, "Failed to load DOM from a XML file."));

				bstrQuery = SysAllocString( (mstrRoot + L"/" + strNode).c_str() ); //How to convert char * to const OLECHAR * so as to be used in SYSALLOCSTRING()? @ http://stackoverflow.com/questions/36542277/how-to-convert-char-to-const-olechar-so-as-to-be-used-in-sysallocstring
				CHK_ALLOC(bstrQuery);
				CHK_HR(pXMLDom->selectSingleNode(bstrQuery, &pNode));
				if (pNode) {
					CHK_HR(pNode->get_nodeName(&bstrNodeName)); //Result from selectSingleNode. Get a node name.
					SysFreeString(bstrNodeName);
	
					CHK_HR(pNode->get_xml(&bstrNodeValue)); //Get a node value.
					
					//IXMLDOMNode::get_nodeValue @ https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k(MSXML%2FIXMLDOMNode%3A%3Aget_nodeValue);k(IXMLDOMNode%3A%3Aget_nodeValue);k(get_nodeValue);k(DevLang-C%2B%2B);k(TargetOS-Windows)&rd=true
					{ 
						CComVariant varNodeValue; 
						hr = pNode->get_nodeValue(&varNodeValue);
						if (FAILED(hr)) goto CleanUp;
						
						//MSXML2: How can I get value of a node? @ http://stackoverflow.com/questions/5966771/msxml2-how-can-i-get-value-of-a-node
						{ 
							BSTR myBstr = L""; //Initialize a BSTR @ http://www.tek-tips.com/viewthread.cfm?qid=938639
							pNode->get_text(&myBstr); //Get the value of a node.
							return myBstr;
						}	
					}
					
					SysFreeString(bstrNodeValue);
					SAFE_RELEASE(pNode);
				}
				else 
					CHK_HR(ReportParseError(pXMLDom, "Error while calling selectSingleNode."));
				return L"";
				
				CleanUp:	{
					SAFE_RELEASE(pXMLDom);
					SAFE_RELEASE(pNodes);
					SAFE_RELEASE(pNode);
					SysFreeString(bstrQuery);
					SysFreeString(bstrNodeName);
					SysFreeString(bstrNodeValue);
					VariantClear(&varFileName);
					return L"";
				}	
			} 
			catch (const std::exception& objException) { 
				messages::messageException(objException, __FUNCTION__, __LINE__);
				return nullptr;
			}	
		}
	}
	using namespace constantsXML_;

	void constantsXML::readXML() { 
		try {
			HRESULT hr = CoInitialize(NULL);
			if (SUCCEEDED(hr)) {
				setCLASSCODE(queryNodes(cstrCLASSCODEName));
				setStock(queryNodes(cstrStockName));
				setFutures(queryNodes(cstrFuturesName)); 
				
				setTradeSR(queryNodes(cstrTradeSRName));

				setStockPoint(queryNodes(cstrStockPointName)); 
				setStockTagPrice(queryNodes(cstrStockTagPriceName)); 
				setStockTagAlg(queryNodes(cstrStockTagAlgName)); 

				setFuturesPoint(queryNodes(cstrFuturesPointName));
				setFuturesTagPrice(queryNodes(cstrFuturesTagPriceName)); 
				setFuturesTagAlg(queryNodes(cstrFuturesTagAlgName)); 

				setLotsTraded(queryNodes(cstrLotsTradedName)); 
				setLotsMax(queryNodes(cstrLotsMaxName)); 

				setTradeDisabled(queryNodes(cstrTradeDisabledName)); 
				setAllMessages(queryNodes(cstrAllMessagesName)); 

				setResumeRange(queryNodes(cstrResumeRangeName));
				CoUninitialize();
			}	
		}
		catch (const std::exception& objException) { 
			messages::messageException(objException, __FUNCTION__, __LINE__);	
		}	
	}	

	namespace constantsXML_ {

		// Helper that allocates the BSTR param for the caller. 
		static HRESULT CreateElement(IXMLDOMDocument *pXMLDom, PCWSTR wszName, IXMLDOMElement **ppElement) { 
			HRESULT hr = S_OK;
			*ppElement = NULL;

			BSTR bstrName = SysAllocString(wszName);
			CHK_ALLOC(bstrName);
			CHK_HR(pXMLDom->createElement(bstrName, ppElement));
		CleanUp:
			SysFreeString(bstrName);
			return hr;
		}

		// Helper function to append a child to a parent node. 
		static HRESULT AppendChildToParent(IXMLDOMNode *pChild, IXMLDOMNode *pParent) { 
			HRESULT hr = S_OK;
			IXMLDOMNode *pChildOut = NULL;
			CHK_HR(pParent->appendChild(pChild, &pChildOut));
		CleanUp:
			SAFE_RELEASE(pChildOut);
			return hr;
		}

		// Helper function to create and add a processing instruction to a document node. 
		static HRESULT CreateAndAddPINode(IXMLDOMDocument *pDom, PCWSTR wszTarget, PCWSTR wszData) { 
			HRESULT hr = S_OK;
			IXMLDOMProcessingInstruction *pPI = NULL;

			BSTR bstrTarget = SysAllocString(wszTarget);
			BSTR bstrData = SysAllocString(wszData);
			CHK_ALLOC(bstrTarget && bstrData);

			CHK_HR(pDom->createProcessingInstruction(bstrTarget, bstrData, &pPI));
			CHK_HR(AppendChildToParent(pPI, pDom));
		CleanUp:
			SAFE_RELEASE(pPI);
			SysFreeString(bstrTarget);
			SysFreeString(bstrData);
			return hr;
		}

		// Helper function to create and add an attribute to a parent node. 
		static HRESULT CreateAndAddAttributeNode(IXMLDOMDocument *pDom, PCWSTR wszName, PCWSTR wszValue, IXMLDOMElement *pParent) { 
			HRESULT hr = S_OK;
			IXMLDOMAttribute *pAttribute = NULL;
			IXMLDOMAttribute *pAttributeOut = NULL; // Out param that is not used

			BSTR bstrName = NULL;
			VARIANT varValue;
			VariantInit(&varValue);

			bstrName = SysAllocString(wszName);
			CHK_ALLOC(bstrName);
			CHK_HR(VariantFromString(wszValue, varValue));

			CHK_HR(pDom->createAttribute(bstrName, &pAttribute));
			CHK_HR(pAttribute->put_value(varValue));
			CHK_HR(pParent->setAttributeNode(pAttribute, &pAttributeOut));
		CleanUp:
			SAFE_RELEASE(pAttribute);
			SAFE_RELEASE(pAttributeOut);
			SysFreeString(bstrName);
			VariantClear(&varValue);
			return hr;
		}

		// Helper function to create and append a text node to a parent node. 
		static HRESULT CreateAndAddTextNode(IXMLDOMDocument *pDom, PCWSTR wszText, IXMLDOMNode *pParent) { 
			HRESULT hr = S_OK;
			IXMLDOMText *pText = NULL;

			BSTR bstrText = SysAllocString(wszText);
			CHK_ALLOC(bstrText);

			CHK_HR(pDom->createTextNode(bstrText, &pText));
			CHK_HR(AppendChildToParent(pText, pParent));
		CleanUp:
			SAFE_RELEASE(pText);
			SysFreeString(bstrText);
			return hr;
		}

		// Helper function to create and append an element node to a parent node, and pass the newly created element node to caller if it wants. 
		static HRESULT CreateAndAddElementNode(IXMLDOMDocument *pDom, PCWSTR wszName, PCWSTR wszNewline, IXMLDOMNode *pParent, IXMLDOMElement **ppElement = NULL) { 
			HRESULT hr = S_OK;
			IXMLDOMElement* pElement = NULL;

			CHK_HR(CreateElement(pDom, wszName, &pElement));
			CHK_HR(CreateAndAddTextNode(pDom, wszNewline, pParent)); // Add NEWLINE+TAB for identation before this element.
			CHK_HR(AppendChildToParent(pElement, pParent)); // Append this element to parent.
		CleanUp:
			if (ppElement) *ppElement = pElement;  // Caller is repsonsible to release this element.
			else SAFE_RELEASE(pElement); // Caller is not interested on this element, so release it.
			return hr;
		}
	}

	void constantsXML::writeNodesToXML() { 
		HRESULT hr = S_OK;
		IXMLDOMDocument *pXMLDom = NULL;
		IXMLDOMElement *pRoot = NULL;
		IXMLDOMElement *pNode = NULL;
		IXMLDOMElement *pSubNode = NULL;
		IXMLDOMDocumentFragment *pDF = NULL;

		BSTR bstrXML = NULL;
		VARIANT varFileName;
		VariantInit(&varFileName);

		CHK_HR(CreateAndInitDOM(&pXMLDom));
		CHK_HR(CreateAndAddPINode(pXMLDom, L"xml", L"version='1.0'")); // Create a processing instruction element.
		CHK_HR(CreateElement(pXMLDom, mstrRoot.c_str(), &pRoot)); // Create the root element.
		CHK_HR(CreateAndAddAttributeNode(pXMLDom, L"created", L"using dom", pRoot)); // Create an attribute for the <root> element, with name "created" and value "using dom".
	
		{
			CHK_HR(CreateAndAddElementNode(pXMLDom, cstrCLASSCODEName.c_str(), L"\n\t", pRoot, &pNode)); // Create a <node...> to hold text content.
			CHK_HR(CreateAndAddTextNode(pXMLDom, getCLASSCODE().c_str(), pNode));
			SAFE_RELEASE(pNode);

			CHK_HR(CreateAndAddElementNode(pXMLDom, cstrStockName.c_str(), L"\n\t", pRoot, &pNode)); // Create a <node...> to hold text content.
			CHK_HR(CreateAndAddTextNode(pXMLDom, getStock().c_str(), pNode));
			SAFE_RELEASE(pNode);

			CHK_HR(CreateAndAddElementNode(pXMLDom, cstrFuturesName.c_str(), L"\n\t", pRoot, &pNode)); // Create a <node...> to hold text content.
			CHK_HR(CreateAndAddTextNode(pXMLDom, getFutures().c_str(), pNode));
			SAFE_RELEASE(pNode);

			CHK_HR(CreateAndAddElementNode(pXMLDom, cstrTradeSRName.c_str(), L"\n\t", pRoot, &pNode)); // Create a <node...> to hold text content.
			CHK_HR(CreateAndAddTextNode(pXMLDom, to_wstring(getTradeSR()).c_str(), pNode));
			SAFE_RELEASE(pNode);

			CHK_HR(CreateAndAddElementNode(pXMLDom, cstrStockPointName.c_str(), L"\n\t", pRoot, &pNode)); // Create a <node...> to hold text content.
			CHK_HR(CreateAndAddTextNode(pXMLDom, to_wstring(getStockPoint()).c_str(), pNode));
			SAFE_RELEASE(pNode);

			CHK_HR(CreateAndAddElementNode(pXMLDom, cstrStockTagPriceName.c_str(), L"\n\t", pRoot, &pNode)); // Create a <node...> to hold text content.
			CHK_HR(CreateAndAddTextNode(pXMLDom, getStockTagPrice().c_str(), pNode));
			SAFE_RELEASE(pNode);

			CHK_HR(CreateAndAddElementNode(pXMLDom, cstrStockTagAlgName.c_str(), L"\n\t", pRoot, &pNode)); // Create a <node...> to hold text content.
			CHK_HR(CreateAndAddTextNode(pXMLDom, getStockTagAlg().c_str(), pNode));
			SAFE_RELEASE(pNode);

			CHK_HR(CreateAndAddElementNode(pXMLDom, cstrFuturesPointName.c_str(), L"\n\t", pRoot, &pNode)); // Create a <node...> to hold text content.
			CHK_HR(CreateAndAddTextNode(pXMLDom, to_wstring(getFuturesPoint()).c_str(), pNode));
			SAFE_RELEASE(pNode);

			CHK_HR(CreateAndAddElementNode(pXMLDom, cstrFuturesTagPriceName.c_str(), L"\n\t", pRoot, &pNode)); // Create a <node...> to hold text content.
			CHK_HR(CreateAndAddTextNode(pXMLDom, getFuturesTagPrice().c_str(), pNode));
			SAFE_RELEASE(pNode);

			CHK_HR(CreateAndAddElementNode(pXMLDom, cstrFuturesTagAlgName.c_str(), L"\n\t", pRoot, &pNode)); // Create a <node...> to hold text content.
			CHK_HR(CreateAndAddTextNode(pXMLDom, getFuturesTagAlg().c_str(), pNode));
			SAFE_RELEASE(pNode);

			CHK_HR(CreateAndAddElementNode(pXMLDom, cstrLotsTradedName.c_str(), L"\n\t", pRoot, &pNode)); // Create a <node...> to hold text content.
			CHK_HR(CreateAndAddTextNode(pXMLDom, to_wstring(getLotsTraded()).c_str(), pNode));
			SAFE_RELEASE(pNode);

			CHK_HR(CreateAndAddElementNode(pXMLDom, cstrLotsMaxName.c_str(), L"\n\t", pRoot, &pNode)); // Create a <node...> to hold text content.
			CHK_HR(CreateAndAddTextNode(pXMLDom, to_wstring(getLotsMax()).c_str(), pNode));
			SAFE_RELEASE(pNode);

			CHK_HR(CreateAndAddElementNode(pXMLDom, cstrTradeDisabledName.c_str(), L"\n\t", pRoot, &pNode)); // Create a <node...> to hold text content.
			CHK_HR(CreateAndAddTextNode(pXMLDom, to_wstring(getTradeDisabled()).c_str(), pNode));
			SAFE_RELEASE(pNode);

			CHK_HR(CreateAndAddElementNode(pXMLDom, cstrAllMessagesName.c_str(), L"\n\t", pRoot, &pNode)); // Create a <node...> to hold text content.
			CHK_HR(CreateAndAddTextNode(pXMLDom, to_wstring(getAllMessages()).c_str(), pNode));
			SAFE_RELEASE(pNode);

			CHK_HR(CreateAndAddElementNode(pXMLDom, cstrResumeRangeName.c_str(), L"\n\t", pRoot, &pNode)); // Create a <node...> to hold text content.
			CHK_HR(CreateAndAddTextNode(pXMLDom, to_wstring(getResumeRange()).c_str(), pNode));
			SAFE_RELEASE(pNode);
		}

		CHK_HR(AppendChildToParent(pRoot, pXMLDom)); // add <root> to document

		CHK_HR(pXMLDom->get_xml(&bstrXML));
		CHK_HR(VariantFromString(mstrConstantsXML.c_str(), varFileName));
		CHK_HR(pXMLDom->save(varFileName));
	CleanUp:
		SAFE_RELEASE(pXMLDom);
		SAFE_RELEASE(pRoot);
		SAFE_RELEASE(pNode);
		SAFE_RELEASE(pDF);
		SAFE_RELEASE(pSubNode);
		SysFreeString(bstrXML);
		VariantClear(&varFileName);
	}

	void constantsXML::writeXML() { 
		HRESULT hr = CoInitialize(NULL);
		if (SUCCEEDED(hr)) {
			writeNodesToXML();
			CoUninitialize();
		}	
	}	
}