#pragma once

#pragma once
#include <iostream>
using std::cout;

#pragma region and now the Tea...
/*
public class Tea { // This looks very similar to the one we just implemented in Coffee; the second and forth steps are different, but it's basically the same recipe.
public:
	void prepareRecipe() {
		boilWater();
		steepTeaBag();
		pourInCup();
		addLemon();
	}

	public void boilWater() { System.out.println("Boiling water"); } // Notice that these two methods are exactly the same as they are in Coffee! So we definitely have some code duplication going on here.
	public void steepTeaBag() { System.out.println("Steeping the tea"); } // These two methods are specialized to Tea.
	public void addLemon() { System.out.println("Adding Lemon"); } // These two methods are specialized to Tea.
	public void pourInCup() { System.out.println("Pouring into cup"); } // Notice that these two methods are exactly the same as they are in Coffee! So we definitely have some code duplication going on here.
}
*/
class Tea { // This looks very similar to the one we just implemented in Coffee; the second and forth steps are different, but it's basically the same recipe.
public:
	void prepareRecipe() {
		boilWater();
		steepTeaBag();
		pourInCup();
		addLemon();
	}

	void boilWater() { cout << "Boiling water\n"; } // Notice that these two methods are exactly the same as they are in Coffee! So we definitely have some code duplication going on here.
	void steepTeaBag() { cout << "Steeping the tea\n"; } // These two methods are specialized to Tea.
	void addLemon() { cout << "Adding Lemon\n"; } // These two methods are specialized to Tea.
	void pourInCup() { cout << "Pouring into cup\n"; } // Notice that these two methods are exactly the same as they are in Coffee! So we definitely have some code duplication going on here.
};
#pragma endregion //and now the Tea...
