#define ON
#ifdef ON

#include <iostream>
using std::cout;

void test() {
	int* a;
	int b = 7;

	a = &b;
	b += 7;
	(*a)++;
	cout << a << '\n';
}

void test2() {
	int* a;
	int b;

	a = &b;
	b = 7;
	*a++;
	cout << b << '\n';
}

void test3() {
	float arr[3] = {10, 20, 30};
	float* a = arr;
	cout << a[1] << '\n';
}

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "ru-RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//OFF test1();
	//OFF test2();
	test3();
	return 0;
}
#endif