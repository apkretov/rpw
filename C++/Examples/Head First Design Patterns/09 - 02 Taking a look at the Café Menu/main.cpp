#include <iostream>
#include <memory>
#include "MenuCafe.h"
#include "MenuDiner.h"
#include "MenuPancakeHouse.h"
#include "Waitress.h"

/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/iterator/dinermergercafe
package headfirst.designpatterns.iterator.dinermergercafe;

public class MenuTestDrive {
	public static void main(String args[]) {
		PancakeHouseMenu pancakeHouseMenu = new PancakeHouseMenu();
		DinerMenu dinerMenu = new DinerMenu();
		CafeMenu cafeMenu = new CafeMenu();

		Waitress waitress = new Waitress(pancakeHouseMenu, dinerMenu, cafeMenu);

		waitress.printMenu();
		waitress.printVegetarianMenu();

		System.out.println("\nCustomer asks, is the Hotdog vegetarian?");
		System.out.print("Waitress says: ");
		if (waitress.isItemVegetarian("Hotdog")) {
			System.out.println("Yes");
		} else {
			System.out.println("No");
		}
		System.out.println("\nCustomer asks, are the Waffles vegetarian?");
		System.out.print("Waitress says: ");
		if (waitress.isItemVegetarian("Waffles")) {
			System.out.println("Yes");
		} else {
			System.out.println("No");
		}
	}
}
*/
int main() {
	auto pancakeHouseMenu = std::make_shared<PancakeHouseMenu>();
	auto dinerMenu = std::make_shared<DinerMenu>();
	auto cafeMenu = std::make_shared<CafeMenu>();

	Waitress waitress(pancakeHouseMenu, dinerMenu, cafeMenu);

	waitress.printMenu();
	waitress.printVegetarianMenu();

	std::cout << "\nCustomer asks, is the Hotdog vegetarian?\n";
	std::cout << "Waitress says: ";
	if (waitress.isItemVegetarian("Hotdog")) {
		std::cout << "Yes\n";
	} else {
		std::cout << "No\n";
	}

	std::cout << "\nCustomer asks, are the Waffles vegetarian?\n";
	std::cout << "Waitress says: ";
	if (waitress.isItemVegetarian("Waffles")) {
		std::cout << "Yes\n";
	} else {
		std::cout << "No\n";
	}

	return 0;
}