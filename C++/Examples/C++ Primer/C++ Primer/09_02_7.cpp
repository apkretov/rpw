#ifdef ON

#include <iostream>
#include <vector>
using namespace std;

void Relational_Operators() {
	vector<int> v1 = {1, 3, 5, 7, 9, 12};
	vector<int> v2 = {1, 3, 9};
	vector<int> v3 = {1, 3, 5, 7};
	vector<int> v4 = {1, 3, 5, 7, 9, 12};

	// ORIG
	//v1 < v2 // true; v1 and v2 differ at element[2]: v1[2] is less than v2[2]
	//v1 < v3 // false; all elements are equal, but v3 has fewer of them;
	//v1 == v4 // true; each element is equal and v1 and v4 have the same size()
	//v1 == v2 // false; v2 has fewer elements than v1

	//MINE //TEST
	cout << boolalpha << (v1 < v2) << '\n'; // true; v1 and v2 differ at element[2]: v1[2] is less than v2[2]
	cout << boolalpha << (v1 < v3) << '\n'; // false; all elements are equal, but v3 has fewer of them;
	cout << boolalpha << (v1 == v4) << '\n'; // true; each element is equal and v1 and v4 have the same size()
	cout << boolalpha << (v1 == v2) << '\n'; // false; v2 has fewer elements than v1
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	Relational_Operators();

	return 0;
}
#endif