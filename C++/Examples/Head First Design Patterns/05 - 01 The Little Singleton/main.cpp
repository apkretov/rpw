#include "../../stdafx.h"
#include "MyClass.h"
#include "Singleton.h"
using namespace std;

int main() {
	print_file_line();
	
#pragma region MINE
	MyClass &myclass = MyClass::getInstance();
	auto singleton = Singleton::getInstance();
#pragma endregion //MINE

	return 0;
}