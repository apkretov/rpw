#pragma once

#include <iostream>
#include "Quackable.h"

#pragma region We need a goose adapter
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/combining/adapter
package headfirst.designpatterns.combining.adapter;

public class RedheadDuck implements Quackable {
	public void quack() {
		System.out.println("Quack");
	}
}
*/
class RedheadDuck : public Quackable {
public:
	void quack() override { std::cout << "Quack\n"; }
};
#pragma endregion //We need a goose adapter