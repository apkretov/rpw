#undef ON
#ifdef ON

#include <iostream>
using std::cout;

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "ru-RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	double a = 2.3, b = 242, c;
	float k = 44;
	double dd = 2;
	long double s = 3;

	//ERR c = 23 + b % a;
	//ERR k >>= 2;
	//ERR if (s ^ dd);
}

#endif