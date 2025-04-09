#pragma once
#include "CaffeineBeverage.h"
using std::cout;

#pragma region Finally we need to deal with the Coffee and Tea classes
/* Java
public class Tea extends CaffeineBeverage { // As in our design, Tea and Coffee now extend CaffeineBeverage.
	public void brew() { // Tea needs to define brew() and addCondiments() - the two abstract methods from Beverage.
		System.out.println("Steeping the tea");
	}
	public void addCondiments() {
		System.out.println("Adding Lemon");
	}
}
*/
class Tea final : public CaffeineBeverage { // As in our design, Tea and Coffee now extend CaffeineBeverage.
public:
	void brew() override { cout << "Steeping the tea\n"; } // Tea needs to define brew() and addCondiments() - the two abstract methods from Beverage.
	void addCondiments() override { cout << "Adding Lemon\n"; }
};
#pragma endregion //Finally we need to deal with the Coffee and Tea classes
