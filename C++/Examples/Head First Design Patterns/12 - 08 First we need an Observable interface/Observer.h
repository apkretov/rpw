#pragma once

#include <memory>

#pragma region We're almost there! We just need to work on the Observer side of the pattern.
/* Java
public interface Observer { // The Observer interface just	has one method, update(), which is passed the QuackObservable that is quacking.
	public void update(QuackObservable duck);
}
*/
class Observer { // The Observer interface just	has one method, update(), which is passed the QuackObservable that is quacking.
public:
	virtual ~Observer() = default;
	virtual void update(const QuackObservable &duck) = 0;
};

using PtrObserver = std::shared_ptr<Observer>;
#pragma endregion //We're almost there! We just need to work on the Observer side of the pattern.
