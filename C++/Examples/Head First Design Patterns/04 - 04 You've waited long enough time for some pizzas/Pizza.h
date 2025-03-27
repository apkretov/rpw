#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

#pragma region Were just missing one thing PIZZA // We're just missing one thing: PIZZA!
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
	void bake() { System.out.println("Bake for 25 minutes at 350");	}
	void cut() { System.out.println("Cutting the pizza into diagonal slices"); }
	void box() { System.out.println("Place pizza in official PizzaStore box"); }
	public String getName() { return name; }
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
		cout << "Preparing " << name << '\n';
        cout << "Tossing dough...\n";
        cout << "Adding sauce...\n";
        cout << "Adding toppings:\n";
        for (const auto &topping : toppings)
			cout << " " << topping << '\n';
	}

	virtual void bake() { cout << "Bake for 25 minutes at 350\n"; }
	virtual void cut() { cout << "Cutting the pizza into diagonal slices\n"; }
	virtual void box() { cout << "Place pizza in official PizzaStore box\n"; }
	string getName() const { return name; }
};
#pragma endregion //Were just missing one thing PIZZA

using PizzaPtr = unique_ptr<Pizza>; //MINE
