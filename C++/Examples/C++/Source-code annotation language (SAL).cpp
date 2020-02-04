#include "stdafx.h"
#include <sstream>

wchar_t* wmemcpy_(_Out_writes_all_(count) wchar_t *dest, _In_reads_(count) const wchar_t *src, _In_ size_t count) { //SAL Makes Code More Valuable @ https://msdn.microsoft.com/en-us/library/hh916383(v=vs.110).aspx
	//ERROR: size_t i; for (i = 0; i <=/*BUG: off-by-one error*/ count; i++) dest[i] = src[i];
	return dest;
}

wchar_t* charToWchar_t(char* orig) { // Convert from char to wchar_t. //"How to: Convert Between Various String Types" @ https://msdn.microsoft.com/en-us/library/ms235631.aspx //+------------------------------------------------------------------+
	size_t newsize = strlen(orig) + 1; // newsize describes the length of the wchar_t string called wcstring in terms of the number of wide characters, not the number of bytes.
	wchar_t * wcstring = new wchar_t[newsize]; // The following creates a buffer large enough to contain the exact number of characters in the original string in the new format. If you want to add more characters to the end of the string, increase the value of newsize to increase the size of the buffer.
	size_t convertedChars = 0; // Convert char* string to a wchar_t* string.
	mbstowcs_s(&convertedChars, wcstring, newsize, orig, _TRUNCATE);
	return(wcstring);
}

void SALwmemcpy() { //"SAL Makes Code More Valuable" @ https://msdn.microsoft.com/en-us/library/hh916383(v=vs.110).aspx //I didn't notice any advantage SAL is supposed provide. Neither the VS code analysis tool (Alt + F11) caught it.
	const wchar_t* ptrSource = charToWchar_t("Test");
	wchar_t ptrDestination[4];
	wmemcpy_(ptrDestination, ptrSource, 4);
}

void InCallee(_In_ int *pInt) {	int i = *pInt; }

void GoodInCaller() {
	int *pInt = new int;
	*pInt = 5;
	InCallee(pInt);
	delete pInt;
}

void BadInCaller() { //The VS code analysis tool (Alt + F11) did catch it.
	int *pInt = NULL;
	InCallee(pInt); // pInt should not be NULL
}

void SAL_In_() { //Example: The _In_ Annotation @ https://msdn.microsoft.com/en-us/library/hh916383(v=vs.110).aspx
	GoodInCaller();
	//ERROR: BadInCaller();
}

void GoodInOptCallee(_In_opt_ int *pInt) { if (pInt != NULL) int i = *pInt; }

void BadInOptCallee(_In_opt_ int *pInt) { int i = *pInt; /*Dereferencing NULL pointer ‘pInt’*/ }

void InOptCaller() { //Example: The _In_opt_ Annotation @ https://msdn.microsoft.com/en-us/library/hh916383(v=vs.110).aspx
	int *pInt = NULL;
	GoodInOptCallee(pInt);
	//ERROR: BadInOptCallee(pInt);
}

int main() {
	SALwmemcpy(); 
	SAL_In_();
	InOptCaller();
	printf("Source-code annotation language (SAL) demonstration completed w/o errors. Invoke errors by uncommenting them.\n");
	return 0;
}

