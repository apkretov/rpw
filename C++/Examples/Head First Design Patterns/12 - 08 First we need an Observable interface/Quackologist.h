#pragma once

#include <iostream>
#include <memory>
#include "Observer.h"
#include "ObservableQuack.h"

#pragma region We're almost there! We just need to work on the Observer side of the pattern.
/* Java
public class Quackologist implements Observer { // We need to implement the Observable interface or else we won't be able to register with a QuackObservable.
	public void update(QuackObservable duck) {
		System.out.println("Quackologist: " + duck + " just quacked."); // The Quackologist is simple; it just has one method, update(), which prints out the Quackable that just quacked.
	}
}
*/
class Quackologist : public Observer { // We need to implement the Observable interface or else we won't be able to register with a QuackObservable.
public:
	void update(const QuackObservable &duck) override { std::cout << "Quackologist: " << &duck << " just quacked.\n"; } // The Quackologist is simple; it just has one method, update(), which prints out the Quackable that just quacked.
};
#pragma endregion //We're almost there! We just need to work on the Observer side of the pattern.
