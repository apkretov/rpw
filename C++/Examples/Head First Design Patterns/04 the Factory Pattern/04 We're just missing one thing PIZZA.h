#pragma once

#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;

#pragma region Were just missing one thing PIZZA // We’re just missing one thing: PIZZA!
/*Java
public abstract class Pizza { // We'll start with an abstract Pizza class and all the concrete pizzas will derive from this.
	String name; // Each Pizza has a name, a type of dough, a type of sauce, and a set of toppings.
	String dough;
	String sauce;
	ArrayList toppings = new ArrayList();
	void prepare() {
		System.out.println("Preparing " + name);
		System.out.println("Tossing dough...");
		System.out.println("Adding sauce...");
		System.out.println("Adding toppings : ");
		for (int i = 0; i < toppings.size(); i++) {
			System.out.println(" " + toppings.get(i));
		}
	}
	void bake() {
		System.out.println("Bake for 25 minutes at 350");
	}
	void cut() {
		System.out.println("Cutting the pizza into diagonal slices");
	}
	void box() {
		System.out.println("Place pizza in official PizzaStore box");
	}
	public String getName() {
		return name;
	}
}
*/
class Pizza { // We'll start with an abstract Pizza class and all the concrete pizzas will derive from this.
protected:
	string name; // Each Pizza has a name, a type of dough, a type of sauce, and a set of toppings.
	string dough;
	string sauce;
	vector<string> toppings;
public:
	virtual ~Pizza() = default;

	virtual void prepare() {
		cout << "Preparing " << name << endl;
		cout << "Tossing dough..." << endl;
		cout << "Adding sauce..." << endl;
		cout << "Adding toppings: " << endl;
		for (const auto &topping : toppings)
			cout << " " << topping << endl;
	}

	virtual void bake() { cout << "Bake for 25 minutes at 350" << endl; }
	virtual void cut() { cout << "Cutting the pizza into diagonal slices" << endl; }
	virtual void box() { cout << "Place pizza in official PizzaStore box" << endl; }
	string getName() const { return name; }
};
#pragma endregion //Were just missing one thing PIZZA

#pragma region Now we just need some concrete subclasses...
/* Java
public class NYStyleCheesePizza extends Pizza {
	public NYStyleCheesePizza() {
		name = "NY Style Sauce and Cheese Pizza"; // The NY Pizza has its own marinara style sauce and thin crust.
		dough = "Thin Crust Dough";
		sauce = "Marinara Sauce";
		toppings.add("Grated Reggiano Cheese"); // And one topping, reggiano cheese!
	}
}
*/
class NYStyleCheesePizza final : public Pizza {
public:
	NYStyleCheesePizza() {
		name = "NY Style Sauce and Cheese Pizza"; // The NY Pizza has its own marinara style sauce and thin crust.
		dough = "Thin Crust Dough";
		sauce = "Marinara Sauce";
		toppings.push_back("Grated Reggiano Cheese"); // And one topping, reggiano cheese!
	}
};

/* Java
public class ChicagoStyleCheesePizza extends Pizza {
	public ChicagoStyleCheesePizza() { // The Chicago Pizza uses plum tomatoes as a sauce along with extra thick crust.
		name = "Chicago Style Deep Dish Cheese Pizza";
		dough = "Extra Thick Crust Dough";
		sauce = "Plum Tomato Sauce";
		toppings.add("Shredded Mozzarella Cheese"); // The Chicago style deep dish pizza has lots of mozzarella cheese!
	}

	void cut() { System.out.println("Cutting the pizza into square slices"); } // The Chicago style pizza also overrides the cut() method so that the pieces are cut into squares.
}
*/
class ChicagoStyleCheesePizza : public Pizza {
public:
	ChicagoStyleCheesePizza() { // The Chicago Pizza uses plum tomatoes as a sauce along with extra thick crust.
		name = "Chicago Style Deep Dish Cheese Pizza";
		dough = "Extra Thick Crust Dough";
		sauce = "Plum Tomato Sauce";
		toppings.push_back("Shredded Mozzarella Cheese"); // The Chicago style deep dish pizza has lots of mozzarella cheese!
	}

	void cut() override { cout << "Cutting the pizza into square slices" << endl; } // The Chicago style pizza also overrides the cut() method so that the pieces are cut into squares.
};
#pragma endregion //Now we just need some concrete subclasses...

#pragma region MINE
class PepperoniPizza : public Pizza {};
class ClamPizza : public Pizza {};
class VeggiePizza : public Pizza {};

class NYStylePepperoniPizza final : public PepperoniPizza {};
class NYStyleClamPizza final : public ClamPizza {};
class NYStyleVeggiePizza final : public VeggiePizza {};
#pragma endregion //MINE

#include "02 A framework for the pizza store 2.h"
