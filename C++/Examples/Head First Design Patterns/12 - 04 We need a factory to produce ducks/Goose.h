#pragma once

#include <iostream>
using std::cout;

#pragma region We need a goose adapter
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/combining/adapter
package headfirst.designpatterns.combining.adapter;

public class Goose {
	public void honk() {
		System.out.println("Honk");
	}
}
*/
class Goose {
public:
	void honk() const { cout << "Honk\n"; }
};
#pragma endregion //We need a goose adapter