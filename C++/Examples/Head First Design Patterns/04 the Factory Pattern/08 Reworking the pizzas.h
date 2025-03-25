#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "06 Building the ingredient factories.h"

using std::cout;
using std::string;
using std::vector;

/* Java
public abstract class Pizza {
	String name; // Each pizza holds a set of ingredients that are used in its preparation.
	Dough dough;
	Sauce sauce;
	Veggies veggies[];
	Cheese cheese;
	Pepperoni pepperoni;
	Clams clam;
	abstract void prepare(); // We’ve now made the prepare method abstract. This is where we are going to collect the ingredients needed for the pizza, which of course will come from the ingredient factory.
	void bake() { System.out.println("Bake for 25 minutes at 350");	} // Our other methods remain the same, with the exception of the prepare method.
	void cut() { System.out.println("Cutting the pizza into diagonal slices"); }
	void box() { System.out.println("Place pizza in official PizzaStore box"); }
	void setName(String name) { this.name = name; }
	String getName() { return name; }
	public String toString() { 
		//code to print pizza here
	}
}
*/
class Pizza {
protected:
	string name; // Each pizza holds a set of ingredients that are used in its preparation.
	Dough dough;
	Sauce sauce;
	vector<Veggies> veggies;
	Cheese cheese;
	Pepperoni pepperoni;
	Clams clam;
public:
	virtual ~Pizza() = default;
	virtual void prepare() = 0; // We’ve now made the prepare method abstract. This is where we are going to collect the ingredients needed for the pizza, which of course will come from the ingredient factory.
	virtual void bake() { cout << "Bake for 25 minutes at 350\n"; } // Our other methods remain the same, with the exception of the prepare method.
	virtual void cut() { cout << "Cutting the pizza into diagonal slices\n"; }
	virtual void box() { cout << "Place pizza in official PizzaStore box\n"; }
	void setName(const string &name) { this->name = name; }
	string getName() const { return name; }

	virtual string toString() const {
		//code to print pizza here
		return "";
	}
};