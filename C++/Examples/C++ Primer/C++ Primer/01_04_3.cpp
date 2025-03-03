#ifdef ON

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	int sum = 0, value = 0;
	
	while (std::cin >> value) // read until end-of-file, calculating a running total of all values read
		sum += value; // equivalent to sum = sum + value;
	std::cout << "Sum is: " << sum << std::endl;
	
	return 0;
}
#endif