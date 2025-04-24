#pragma region Duck reunion
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/combining/ducks
package headfirst.designpatterns.combining.ducks;

public class DecoyDuck implements Quackable {
	public void quack() {
		System.out.println("<< Silence >>");
	}
}
*/

#ifndef DECOY_DUCK_H
#define DECOY_DUCK_H

#include "Quackable.h"

class DecoyDuck : public Quackable {
public:
    void quack() override;
};

#endif // DECOY_DUCK_H
#pragma endregion //Duck reunion