#include "../../stdafx.h"
#include "MyClass.h"
using namespace std;

int main() {
	print_file_line();
	
	MyClass &myclass = MyClass::getInstance();

	return 0;
}