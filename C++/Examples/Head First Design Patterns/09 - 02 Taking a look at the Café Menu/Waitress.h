#pragma once

#include <iostream>
#include <memory>
#include "Menu.h"
#include "ItemMenu.h"

/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/iterator/dinermergercafe
package headfirst.designpatterns.iterator.dinermergercafe;

import java.util.Iterator;

public class Waitress {
	Menu pancakeHouseMenu;
	Menu dinerMenu;
	Menu cafeMenu;

	public Waitress(Menu pancakeHouseMenu, Menu dinerMenu, Menu cafeMenu) {
		this.pancakeHouseMenu = pancakeHouseMenu;
		this.dinerMenu = dinerMenu;
		this.cafeMenu = cafeMenu;
	}

	public void printMenu() {
		Iterator<MenuItem> pancakeIterator = pancakeHouseMenu.createIterator();
		Iterator<MenuItem> dinerIterator = dinerMenu.createIterator();
		Iterator<MenuItem> cafeIterator = cafeMenu.createIterator();

		System.out.println("MENU\n----\nBREAKFAST");
		printMenu(pancakeIterator);
		System.out.println("\nLUNCH");
		printMenu(dinerIterator);
		System.out.println("\nDINNER");
		printMenu(cafeIterator);
	}

	private void printMenu(Iterator<MenuItem> iterator) {
		while (iterator.hasNext()) {
			MenuItem menuItem = iterator.next();
			System.out.print(menuItem.getName() + ", ");
			System.out.print(menuItem.getPrice() + " -- ");
			System.out.println(menuItem.getDescription());
		}
	}

	public void printVegetarianMenu() {
		System.out.println("\nVEGETARIAN MENU\n---------------");
		printVegetarianMenu(pancakeHouseMenu.createIterator());
		printVegetarianMenu(dinerMenu.createIterator());
		printVegetarianMenu(cafeMenu.createIterator());
	}

	public boolean isItemVegetarian(String name) {
		Iterator<MenuItem> pancakeIterator = pancakeHouseMenu.createIterator();
		if (isVegetarian(name, pancakeIterator)) {
			return true;
		}
		Iterator<MenuItem> dinerIterator = dinerMenu.createIterator();
		if (isVegetarian(name, dinerIterator)) {
			return true;
		}
		Iterator<MenuItem> cafeIterator = cafeMenu.createIterator();
		if (isVegetarian(name, cafeIterator)) {
			return true;
		}
		return false;
	}
}
*/
class Waitress {
	using PtrMenue = std::shared_ptr<Menu>;
	PtrMenue pancakeHouseMenu;
	PtrMenue dinerMenu;
	PtrMenue cafeMenu;
public:
	Waitress(PtrMenue pancakeHouseMenu, PtrMenue dinerMenu, PtrMenue cafeMenu) : pancakeHouseMenu(pancakeHouseMenu), dinerMenu(dinerMenu), cafeMenu(cafeMenu) {}

	void printMenu() {
		auto pancakeIterator = pancakeHouseMenu->createIterator();
		auto dinerIterator = dinerMenu->createIterator();
		auto cafeIterator = cafeMenu->createIterator();

		std::cout << "MENU\n----\nBREAKFAST\n";
		printMenu(pancakeIterator);
		std::cout << "\nLUNCH\n";
		printMenu(dinerIterator);
		std::cout << "\nDINNER\n";
		printMenu(cafeIterator);
	}
private:
	void printMenu(PtrIterMenuitem iterator) {
		while (iterator->hasNext()) {
			auto &menuItem = iterator->next();
			std::cout << menuItem.getName() << ", ";
			std::cout << menuItem.getPrice() << " -- ";
			std::cout << menuItem.getDescription() << "\n";
		}
	}
public:
	void printVegetarianMenu() {
		std::cout << "\nVEGETARIAN MENU\n---------------\n";
		printVegetarianMenu(pancakeHouseMenu->createIterator());
		printVegetarianMenu(dinerMenu->createIterator());
		printVegetarianMenu(cafeMenu->createIterator());
	}

	bool isItemVegetarian(const std::string &name) {
		auto pancakeIterator = pancakeHouseMenu->createIterator();
		if (isVegetarian(name, pancakeIterator)) {
			return true;
		}
		auto dinerIterator = dinerMenu->createIterator();
		if (isVegetarian(name, dinerIterator)) {
			return true;
		}
		auto cafeIterator = cafeMenu->createIterator();
		if (isVegetarian(name, cafeIterator)) {
			return true;
		}
		return false;
	}
private:
	void printVegetarianMenu(PtrIterMenuitem iterator) {
		while (iterator->hasNext()) {
			auto &menuItem = iterator->next();
			if (menuItem.isVegetarian()) {
				std::cout << menuItem.getName() << ", ";
				std::cout << menuItem.getPrice() << " -- ";
				std::cout << menuItem.getDescription() << "\n";
			}
		}
	}

	bool isVegetarian(const std::string &name, PtrIterMenuitem iterator) {
		while (iterator->hasNext()) {
			auto &menuItem = iterator->next();
			if (menuItem.getName() == name) {
				return menuItem.isVegetarian();
			}
		}
		return false;
	}
};