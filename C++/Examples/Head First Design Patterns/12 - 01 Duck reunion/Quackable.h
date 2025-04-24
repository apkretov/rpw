#pragma once

#pragma region Duck reunion
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/combining/ducks
package headfirst.designpatterns.combining.ducks;

public interface Quackable {
	public void quack();
}
*/
class Quackable {
public:
    virtual void quack() = 0;
    virtual ~Quackable() = default;
};
#pragma endregion //Duck reunion