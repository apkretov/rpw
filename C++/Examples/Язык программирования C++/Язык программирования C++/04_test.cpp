#undef ON
#ifdef ON

#include <iostream>
using std::cout;

int main(int argc, char* agrv[]) {
	setlocale(LC_ALL, "ru-RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	int i = 5;

	while (i <= 5) {
		cout << (--i)-- << " ";
		if (i < 2)
			break;
	}
}
#endif