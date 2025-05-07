#pragma once

#include <memory>
#include "ObservableQuack.h"

#pragma region First we need an Observable interface
/* Java 
public interface Quackable extends QuackObservable{
	public void quack();
}
*/
class Quackable : public QuackObservable {
public:
	virtual ~Quackable() = default;
	virtual void quack() = 0;
};

using PtrQuackable = std::unique_ptr<Quackable>;
#pragma endregion //First we need an Observable interface