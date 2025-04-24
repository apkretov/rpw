#pragma region Duck reunion
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/combining/ducks
package headfirst.designpatterns.combining.ducks;

public class RedheadDuck implements Quackable {
	public void quack() {
		System.out.println("Quack");
	}
}
*/

#ifndef REDHEAD_DUCK_H
#define REDHEAD_DUCK_H

#include "Quackable.h"

class RedheadDuck : public Quackable {
public:
    void quack() override;
};

#endif // REDHEAD_DUCK_H
#pragma endregion //Duck reunion