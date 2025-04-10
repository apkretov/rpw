#include "../../stdafx.h"
#include "MenuDiner.h"
#include "MenuPancakeHouse.h"

int main() {
	print_file_line();

#pragma region To print all the items on each menu,
/* Java
	PancakeHouseMenu pancakeHouseMenu = new PancakeHouseMenu(); // The method looks the same, but the calls are returning different types. // The implementation is showing through, breakfast items are in an ArrayList, lunch items are in an Array.
	ArrayList breakfastItems = pancakeHouseMenu.getMenuItems();
	DinerMenu dinerMenu = new DinerMenu();
	MenuItem[] lunchItems = dinerMenu.getMenuItems();
*/
	PancakeHouseMenu pancakeHouseMenu; // The method looks the same, but the calls are returning different types. // The implementation is showing through, breakfast items are in an ArrayList, lunch items are in an Array.
	vector<MenuItem> breakfastItems = pancakeHouseMenu.getMenuItems();
	DinerMenu dinerMenu;
	MenuItem *lunchItems = dinerMenu.getMenuItems();
#pragma endregion //To print all the items on each menu,

#pragma region Now, to print out the items from the PancakeHouseMenu
	/* Java
	for (int i = 0; i < breakfastItems.size(); i++) { // Now, we have to implement two different loops to step through the two implementations of the menu items...
		MenuItem menuItem = (MenuItem)breakfastItems.get(i);
		System.out.print(menuItem.getName() + " ");
		System.out.println(menuItem.getPrice() + " ");
		System.out.println(menuItem.getDescription());
	}

	for (int i = 0; i < lunchItems.length; i++) { // ...one loop for the ArrayList...
		MenuItem menuItem = lunchItems[i];
		System.out.print(menuItem.getName() + " "); // and another for the Array.
		System.out.println(menuItem.getPrice() + " ");
		System.out.println(menuItem.getDescription());
	}
	*/

	for (int i = 0; i < breakfastItems.size(); i++) { // Now, we have to implement two different loops to step through the two implementations of the menu items...
		MenuItem menuItem = breakfastItems[i];
		cout << menuItem.getName() << " ";
		cout << menuItem.getPrice() << "\n";
		cout << menuItem.getDescription() << "\n";
	}

	cout << '\n';
	for (int i = 0; i < DinerMenu::MAX_ITEMS; i++) { // ...one loop for the ArrayList...
		MenuItem menuItem = lunchItems[i];
		cout << menuItem.getName() << " "; // and another for the Array.
		cout << menuItem.getPrice() << "\n";
		cout << menuItem.getDescription() << "\n";
	}
#pragma endregion //Now, to print out the items from the PancakeHouseMenu
	return 0;
}