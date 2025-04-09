#pragma once
#include <iostream>
using std::cout;

#pragma region Now we have a new prepareRecipe() method
/* Java
public abstract class CaffeineBeverage { // CaffeineBeverage is abstract, just like in the class design.
	final void prepareRecipe() { // Now, the same prepareRecipe() method will be used to make both Tea and Coffee. prepareRecipe() is declared final because we don't want our subclasses to be able to override this method and change the recipe! We've generalized steps 2 and 4 to brew() the beverage and addCondiments().
		boilWater();
		brew();
		pourInCup();
		addCondiments();
	}
	abstract void brew(); // Because Coffee and Tea handle these methods in different ways, they're going to have to be declared as abstract. Let the subclasses worry about that stuff!
	abstract void addCondiments();
	void boilWater() { // Remember, we moved these into the CaffeineBeverage class (back in our class diagram).
		System.out.println("Boiling water");
	}
	void pourInCup() {
		System.out.println("Pouring into cup");
	}
}
*/
class CaffeineBeverage { // CaffeineBeverage is abstract, just like in the class design.
public:
	virtual ~CaffeineBeverage() = default;

	void prepareRecipe() { // Now, the same prepareRecipe() method will be used to make both Tea and Coffee. prepareRecipe() is declared final because we don't want our subclasses to be able to override this method and change the recipe! We've generalized steps 2 and 4 to brew() the beverage and addCondiments().
		boilWater();
		brew();
		pourInCup();
		addCondiments();
	}

	virtual void brew() = 0; // Because Coffee and Tea handle these methods in different ways, they're going to have to be declared as abstract. Let the subclasses worry about that stuff!
	virtual void addCondiments() = 0;
	void boilWater() { cout << "Boiling water\n"; } // Remember, we moved these into the CaffeineBeverage class (back in our class diagram).
	void pourInCup() { cout << "Pouring into cup\n"; }
};
#pragma endregion //Now we have a new prepareRecipe() method
