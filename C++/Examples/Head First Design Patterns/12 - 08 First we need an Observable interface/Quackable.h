#pragma once

#include <memory>
#include "ObservableQuack.h"

#pragma region First we need an Observable interface
/* Java 
public interface Quackable extends QuackObservable{ // So, we extend the Quackable interface with QuackObserver.
	public void quack();
}
*/
class Quackable : public QuackObservable { // So, we extend the Quackable interface with QuackObserver.
public:
	virtual ~Quackable() = default;
	virtual void quack() = 0;
};

using PtrQuackable = std::unique_ptr<Quackable>; //TO DO: This may become shared_ptr.
#pragma endregion //First we need an Observable interface