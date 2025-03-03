#if 0

#include <iostream>
#include "../../stdafx.h"
using namespace std;

int main(int argc, char *argv[]) {
	PRINT_FILE_LINE();

	LOG_DURATION("main");
	
	cin.tie(nullptr); //TEST!
	string x;
	while (cin >> x)
		cout << x;

	return 0;
}
#endif //1