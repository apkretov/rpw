#ifdef ON

#include <iostream>
using namespace std;

void mine() {
	struct in_class_initializer {
		int uninit;
		int init{};
	};
	
	in_class_initializer ini;
	cout << "ini.uninit = " << ini.uninit << '\n';
	cout << "ini.init = " << ini.init << '\n';
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	mine();

	return 0;
}
#endif