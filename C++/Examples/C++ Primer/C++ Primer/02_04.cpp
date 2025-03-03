#undef EX_02_26
#ifdef EX_02_26

#include <iostream>
using std::cout;

void f(int i) {
	const int ci{i};
	cout << ci << '\n';
}

int main(int argc, char** argv) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	int cnt = 0;
	const int sz = cnt;	
	cout << sz << '\n';

	f(cnt);

	return 0;
}
#endif