#include "stdafx.h" //wcscat, wcscat_s @ http://en.cppreference.com/w/c/string/wide/wcscat
#include <wchar.h> 
#include <stdio.h>
#include <locale.h>
#pragma warning(disable: 4996)
 
int main(void) {
    wchar_t str[50] = L"�����, ������.";
    wcscat(str, L" ");
    wcscat(str, L"� ������ ����.");
    setlocale(LC_ALL, "en_US.utf8");
    printf("%ls", str);
}