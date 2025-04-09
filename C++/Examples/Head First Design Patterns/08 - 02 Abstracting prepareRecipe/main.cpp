#include <memory>
#include "../../stdafx.h"
#include "CaffeineBeverage.h"
#include "Coffee.h"
#include "Tea.h"
using std::cout;
using std::make_unique;
using std::unique_ptr;

#pragma region MINE
int main() {
	print_file_line();

	unique_ptr<CaffeineBeverage> tea = make_unique<Tea>();
	tea->prepareRecipe();
	cout << '\n';
	unique_ptr<CaffeineBeverage> coffee = make_unique<Coffee>();
	coffee->prepareRecipe();
	cout << '\n';

	return 0;
}
#pragma endregion //MINE
