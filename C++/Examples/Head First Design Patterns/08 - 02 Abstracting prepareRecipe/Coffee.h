#pragma once
#include "CaffeineBeverage.h"
using std::cout;

#pragma region Finally we need to deal with the Coffee and Tea classes
/* Java
public class Coffee extends CaffeineBeverage { // Same for Coffee, except Coffee deals with coffee, and sugar and milk instead of tea bags and lemon.
	public void brew() {
		System.out.println("Dripping Coffee through filter");
	}
	public void addCondiments() {
		System.out.println("Adding Sugar and Milk");
	}
}
*/
class Coffee final : public CaffeineBeverage { // Same for Coffee, except Coffee deals with coffee, and sugar and milk instead of tea bags and lemon.
public:
	void brew() override { cout << "Dripping Coffee through filter\n"; }
	void addCondiments() override { cout << "Adding Sugar and Milk\n"; }
};
#pragma endregion //Finally we need to deal with the Coffee and Tea classes
