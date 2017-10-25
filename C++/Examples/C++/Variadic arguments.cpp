#include "stdafx.h" //Variadic functions @ http://en.cppreference.com/w/cpp/utility/variadic
#include <iostream>
#include <cstdarg>
#include <string>
#include <vector>
using namespace std;

void simple_printf(const char* chrFormat...) {
	va_list chrArgs; //va_arg, va_copy, va_end, va_start @ https://msdn.microsoft.com/en-us/library/kb57fad8.aspx
	va_start(chrArgs, chrFormat);
	while (*chrFormat != NULL) {
		if (*chrFormat == 'i') {
			int i = va_arg(chrArgs, int);
			cout << i << '\n';
		}else if (*chrFormat == 'd') {
			double d = va_arg(chrArgs, double);
			cout << d << '\n';
		}else if (*chrFormat == 'c') {
			int c = va_arg(chrArgs, int); // note automatic conversion to integral type
			cout << static_cast<char>(c) << '\n';
		}else if (*chrFormat == 's') {
			char* s = va_arg(chrArgs, char*);
			cout << s << '\n'; //va_arg, va_copy, va_end, va_start @ https://msdn.microsoft.com/en-us/library/kb57fad8.aspx
		/* ERROR
		}else if (*chrFormat == 't') {
			string t = va_arg(args, string);
			cout << static_cast<string>(t) << '\n';
		}*/
		}else if (*chrFormat == 'v') {
			vector<vector<string>>* strTest = va_arg(chrArgs, vector<vector<string>>*);
			for (auto i = strTest->begin(); i < strTest->end(); i++) { 
				auto ptrTest = i._Ptr->begin(); //Accessing via pointers vs. [][] indexes.
				string strTestField1 = *ptrTest;
				string strTestField2 = *(++ptrTest);
				cout << strTestField1 << '\t' << strTestField2 << endl;
			}
			cout << endl;
		}
		++chrFormat;
	}
	va_end(chrArgs);
}

int main() {
	cout << "Function call 1:" << endl;
	simple_printf("icdd", 3, 'a', 1.999, 42.5);
	
	cout << endl << "Function call 2:" << endl;
	simple_printf("");

	cout << endl << "Function call 3:" << endl;
	simple_printf("s", "Abc");

	/*ERROR
	cout << endl << "Function call 4:" << endl;
	simple_printf("t", "ABC");
	*/

	vector<vector<string>> strTest = { {"000", "001"}, {"100", "101"} };
	cout << endl << "Function call 4:" << endl;
	simple_printf("v", &strTest);
}
