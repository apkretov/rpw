#pragma once

#include <memory>
#include "Quackable.h"
#include <vector>

#pragma region Lets create a flock of ducks //Let's create a flock of ducks(well, actually a flock of Quackables)
/* Java 
public class Flock implements Quackable { // Remember, the composite needs to implement the same interface as the leaf elements. Our leaf elements are Quackables.
	ArrayList quackers = new ArrayList(); // We're using an ArrayList inside each Flock to hold the Quackables that belong to the Flock.
	public void add(Quackable quacker) { // The add() method adds a Quackable to the Flock.
		quackers.add(quacker);
	}
	public void quack() {						 // Now for the quack() method - after all, the Flock is a Quackable too. The quack() method in Flock needs
		Iterator iterator = quackers.iterator(); // to work over the entire Flock. Here we iterate through the ArrayList and call quack() on each element.
		while (iterator.hasNext()) {
			Quackable quacker = (Quackable)iterator.next();
			quacker.quack();
		}
	}
}
*/
class Flock : public Quackable { // Remember, the composite needs to implement the same interface as the leaf elements. Our leaf elements are Quackables.
	std::vector<PtrQuackable> quackers; // We're using an ArrayList inside each Flock to hold the Quackables that belong to the Flock.
public:
	void add(PtrQuackable quacker) { quackers.push_back(std::move(quacker)); } // The add() method adds a Quackable to the Flock.

	void quack() override { // Now for the quack() method - after all, the Flock is a Quackable too. The quack() method in Flock needs to work over the entire Flock. Here we iterate through the ArrayList and call quack() on each element.
		for (auto const &quacker : quackers) // There it is! The Iterator Pattern at work!
			quacker->quack();
	}
};
#pragma endregion //Lets create a flock of ducks