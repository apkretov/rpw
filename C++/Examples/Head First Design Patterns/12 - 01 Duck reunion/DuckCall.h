#pragma once

#include "Quackable.h"

#pragma region Duck reunion
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/combining/ducks
package headfirst.designpatterns.combining.ducks;

public class DuckCall implements Quackable {
	public void quack() {
		System.out.println("Kwak");
	}
}
*/

class DuckCall : public Quackable {
public:
    void quack() override;
};
#pragma endregion //Duck reunion