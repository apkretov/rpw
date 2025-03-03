#undef ON
#ifdef ON

#include <iostream>
using std::cout;
using std::cin;

#include <cstdio>

void test() {
	char* a = new char[20];
	delete[] a;
}

void mine() {
	const unsigned m = 0xfffffff; // Array pointers.
	const int n = 10; // Arrays.
	double** a = new double* [m];

	cout << "Filling in the array...\n";
	for (int i = 0; i < n; ++i) {
		a[i] = new double[m];
	}
	cout << "Check out the memory before delete[] a[]...\n";
	(void)getchar();
	
	for (int i = 0; i < n; ++i) {
		delete[] a[i];
	}
	
	cout << "Check out the memory before delete[] a...\n";
	(void)getchar();
	delete[] a;
	
	cout << "Check out the memory...\n";
	(void)getchar();
}

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "ru-RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";
	
	//OFF test();
	mine();

	return 0;
}
#endif