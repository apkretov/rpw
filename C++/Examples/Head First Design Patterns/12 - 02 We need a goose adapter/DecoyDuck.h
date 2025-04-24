#pragma once

#include "Quackable.h"
#include <iostream>
using std::cout;

#pragma region We need a goose adapter
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/combining/adapter
package headfirst.designpatterns.combining.adapter;

public class DecoyDuck implements Quackable {
	public void quack() {
		System.out.println("<< Silence >>");
	}
}
*/
class DecoyDuck : public Quackable {
public:
	void quack() const override { cout << "<< Silence >>\n"; }
};
#pragma endregion //We need a goose adapter