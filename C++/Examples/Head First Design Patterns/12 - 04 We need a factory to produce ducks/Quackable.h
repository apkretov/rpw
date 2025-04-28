#pragma once

#include <memory>

#pragma region We need a goose adapter
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/combining/adapter
package headfirst.designpatterns.combining.adapter;

public interface Quackable {
	public void quack();
}
*/
class Quackable {
public:
	virtual ~Quackable() = default;
	virtual void quack() = 0;
};

using QuackablePtr = std::unique_ptr<Quackable>;
#pragma endregion //We need a goose adapter