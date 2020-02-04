#include "stdafx.h" //Re[3]: wcscat_s @ http://rsdn.org/forum/cpp.applied/2780568.hot
#include <cstdlib>

int main() {
	wchar_t* A = L"Lorem ipsum "; // конкатенация в стиле Си
	wchar_t* B = L"dolor sit amet";
	size_t const count = wcslen(A) + wcslen(B) + 1; 
	wchar_t* buffer = (wchar_t*)calloc(count, sizeof(wchar_t)); // или (wchar_t*) malloc(count*sizeof(wchar_t))
	wcscpy_s(buffer, count, A);
	wcscat_s(buffer, count, B);
	printf("%ls\n\n", buffer);
	free(buffer);
}

