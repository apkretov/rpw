#pragma region Duck reunion
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/combining/ducks
package headfirst.designpatterns.combining.ducks;

public class MallardDuck implements Quackable {
	public void quack() {
		System.out.println("Quack");
	}
}
*/

#ifndef MALLARD_DUCK_H
#define MALLARD_DUCK_H

#include "Quackable.h"

class MallardDuck : public Quackable {
public:
    void quack() override;
};

#endif // MALLARD_DUCK_H
#pragma endregion //Duck reunion