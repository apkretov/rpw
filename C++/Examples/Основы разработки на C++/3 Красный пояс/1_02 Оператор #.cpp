#if 0 

#include <iostream>
#include "../../stdafx.h"
using namespace std;

#define AS_KV(x) #x << " = " << x

int main() {
	PRINT_FILE_LINE();

	int x = 4;
	string t = "hello";
	bool isTrue = false;

	cerr << boolalpha;
	cerr <<	AS_KV(x) << '\n'
		<< AS_KV(t) << '\n'
		<< AS_KV(isTrue) << '\n';
}
#endif //1