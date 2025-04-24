#pragma region Duck reunion
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/combining/ducks
package headfirst.designpatterns.combining.ducks;

public class DuckCall implements Quackable {
	public void quack() {
		System.out.println("Kwak");
	}
}
*/

#ifndef DUCK_CALL_H
#define DUCK_CALL_H

#include "Quackable.h"

class DuckCall : public Quackable {
public:
    void quack() override;
};

#endif // DUCK_CALL_H
#pragma endregion //Duck reunion