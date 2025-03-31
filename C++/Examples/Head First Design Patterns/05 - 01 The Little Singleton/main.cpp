#include "../../stdafx.h"
#include "ChocolateBoiler.h"
#include "Singleton.h"
#include "MyClass.h"
using namespace std;

int main() {
	print_file_line();
	
#pragma region MINE
	MyClass &myclass = MyClass::getInstance();
	auto singleton = Singleton::getInstance();

	ChocolateBoiler boiler1;
	boiler1.fill();
	ChocolateBoiler boiler2;
	boiler2.fill();
#pragma endregion //MINE

	return 0;
}