#undef ON
#ifdef ON

#include <iostream>

int main() {
	setlocale(LC_ALL, "RU");
	std::cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	int i = 100, sum = 0;
	for (int i = 0; i != 10; ++i)
		sum += i;
	std::cout << i << " " << sum << std::endl;
}
#endif
