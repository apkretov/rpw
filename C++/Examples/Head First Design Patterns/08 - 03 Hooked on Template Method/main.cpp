#include <iostream>
#include "../../stdafx.h"
#include "WithHookCoffee.h"
#include "WithHookTea.h"  
using std::cout;

#pragma region Lets run the TestDrive //Let's run the TestDrive
/* Java
public class BeverageTestDrive {
	public static void main(String[] args) {
		TeaWithHook teaHook = new TeaWithHook(); // Create a tea
		CoffeeWithHook coffeeHook = new CoffeeWithHook(); // A coffee

		System.out.println("\nMaking tea...");
		teaHook.prepareRecipe(); // And call prepareRecipe() on both!

		System.out.println("\nMaking coffee...");
		coffeeHook.prepareRecipe(); // And call prepareRecipe() on both!
	}
}
*/
int main() {
	print_file_line();

	cout << "Making tea...\n";
	TeaWithHook teaHook; // Create a tea
	teaHook.prepareRecipe(); // And call prepareRecipe() on both!

	cout << "\nMaking coffee...\n";
	CoffeeWithHook coffeeHook; // A coffee
	coffeeHook.prepareRecipe(); // And call prepareRecipe() on both!

	return 0;
}
#pragma endregion //Lets run the TestDrive
