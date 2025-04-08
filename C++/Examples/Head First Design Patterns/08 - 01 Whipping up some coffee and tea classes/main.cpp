#include "../../stdafx.h"
#include "Coffee.h"
#include "Tea.h"
using std::cout;

#pragma region MINE
int main() {
	print_file_line();

	Coffee coffee;
	Tea tea;

	cout << "Making coffee...\n";
	coffee.boilWater();
	coffee.brewCoffeeGrinds();
	coffee.pourInCup();
	coffee.addSugarAndMilk();

	cout << "\nMaking tea...\n";
	tea.boilWater();
	tea.steepTeaBag();
	tea.pourInCup();
	tea.addLemon();

	return 0;
}
#pragma endregion //MINE
