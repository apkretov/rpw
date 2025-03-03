#undef ON
#ifdef ON

#include <iostream>

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "ru-Ru");
	std::cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n"; //TEMPLATE

	std::cout << "Hello, World!" << std::endl;
	return 1;
}
#endif