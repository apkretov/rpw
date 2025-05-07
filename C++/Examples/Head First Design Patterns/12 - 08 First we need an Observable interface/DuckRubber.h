#pragma once

#include <iostream>
#include "Quackable.h"

#pragma region We need a goose adapter
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/combining/adapter
package headfirst.designpatterns.combining.adapter;

public class RubberDuck implements Quackable {
	public void quack() {
		System.out.println("Squeak");
	}
}
*/
class RubberDuck : public Quackable {
public:
	void quack() override { std::cout << "Squeak\n"; }
};
#pragma endregion //We need a goose adapter