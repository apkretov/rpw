#include "../../stdafx.h"
#include "ChocolateBoiler.h"

int main() {
	print_file_line();

#pragma region MINE
	auto boiler = ChocolateBoiler::getInstance();
	boiler->fill();
#pragma endregion //MINE

	return 0;
}