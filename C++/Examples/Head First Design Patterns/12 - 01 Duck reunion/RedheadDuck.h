#pragma once
#pragma region RedheadDuck
#include <iostream>
#include "Quackable.h"

/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/combining/ducks
package headfirst.designpatterns.combining.ducks;

public class RedheadDuck implements Quackable {
	public void quack() {
		System.out.println("Quack");
	}
}
*/

class RedheadDuck : public Quackable {
public:
    void quack() override {
        std::cout << "Quack" << std::endl;
    }
};
#pragma endregion //RedheadDuck