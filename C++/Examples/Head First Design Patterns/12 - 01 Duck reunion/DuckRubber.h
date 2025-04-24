#pragma once

#include <iostream>
#include "Quackable.h"

#pragma region Duck reunion
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/combining/ducks
package headfirst.designpatterns.combining.ducks;

public class RubberDuck implements Quackable {
	public void quack() {
		System.out.println("Squeak");
	}
}
*/
class RubberDuck : public Quackable {
public:
    void quack() override { std::cout << "Squeak" << std::endl; }
};
#pragma endregion //Duck reunion