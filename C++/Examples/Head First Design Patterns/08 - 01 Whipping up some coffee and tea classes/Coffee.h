#pragma once

#include <iostream>

#pragma region Whipping up some coffee and tea classes (in Java)
/*
public class Coffee {
	void prepareRecipe() { // Here's our recipe for coffee, straight out of the training manual.
		boilWater();
		brewCoffeeGrinds(); // Each of the steps is implemented as a separate method.
		pourInCup();
		addSugarAndMilk();
	}

	public void boilWater() { // Each of these methods implements one step of the algorithm. There's a method to boil water,
		System.out.println("Boiling water");
	}

	public void brewCoffeeGrinds() { // brew the coffee,
		System.out.println("Dripping Coffee through filter");
	}

	public void pourInCup() { // pour the coffee in a cup and
		System.out.println("Pouring into cup");
	}

	public void addSugarAndMilk() { // add sugar and milk.
		System.out.println("Adding Sugar and Milk");
	}
}
*/
class Coffee {
public:
	void prepareRecipe() { // Here's our recipe for coffee, straight out of the training manual.
		boilWater();
		brewCoffeeGrinds(); // Each of the steps is implemented as a separate method.
		pourInCup();
		addSugarAndMilk();
	}

	void boilWater() { std::cout << "Boiling water" << std::endl; } // Each of these methods implements one step of the algorithm. There's a method to boil water,
	void brewCoffeeGrinds() { std::cout << "Dripping Coffee through filter" << std::endl; } // brew the coffee,
	void pourInCup() { std::cout << "Pouring into cup" << std::endl; } // pour the coffee in a cup and
	void addSugarAndMilk() { std::cout << "Adding Sugar and Milk" << std::endl; } // add sugar and milk.
};

#pragma endregion //Whipping up some coffee and tea classes (in Java)
