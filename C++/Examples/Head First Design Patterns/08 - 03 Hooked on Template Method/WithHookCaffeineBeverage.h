#pragma once

#include <iostream>
using std::cout;

#pragma region Hooked on Template Method...
/* Java
public abstract class CaffeineBeverageWithHook {
	final void prepareRecipe() { // We've added a little conditional statement that bases its success on a concrete method, customerWantsCondiments(). If the customer WANTS condiments, only then do we call addCondiments().
		boilWater();
		brew();
		pourInCup();
		if (customerWantsCondiments()) addCondiments();
	}

	abstract void brew();
	abstract void addCondiments();
	void boilWater() { System.out.println("Boiling water"); }
	void pourInCup() { System.out.println("Pouring into cup"); }
	boolean customerWantsCondiments() { return true; } // Here we've defined a method with a (mostly) empty default implementation. This method just returns true and does nothing else. // This is a hook because the subclass can override this method, but doesn't have to.
}
*/
class CaffeineBeverageWithHook {
public:
    virtual ~CaffeineBeverageWithHook() = default;

    void prepareRecipe() { // We've added a little conditional statement that bases its success on a concrete method, customerWantsCondiments(). If the customer WANTS condiments, only then do we call addCondiments().
        boilWater();
        brew();
        pourInCup();
        if (customerWantsCondiments()) //TEST!
			addCondiments();
    }

    virtual void brew() = 0;
    virtual void addCondiments() = 0;
    void boilWater() { cout << "Boiling water\n"; }
    void pourInCup() { cout << "Pouring into cup\n"; } 
    virtual bool customerWantsCondiments() { return true; } //TEST! //																					Here we've defined a method with a (mostly) empty default implementation. This method just returns true and does nothing else. // This is a hook because the subclass can override this method, but doesn't have to.
};
#pragma endregion //Hooked on Template Method...