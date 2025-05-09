#pragma once

#include <memory>
#include <vector>
#include "Quackable.h"

#pragma region Integrate the helper Observable with the Quackable classes
class Flock : public Quackable { // Remember, the composite needs to implement the same interface as the leaf elements. Our leaf elements are Quackables.
	std::vector<PtrQuackable> quackers; // We're using an ArrayList inside each Flock to hold the Quackables that belong to the Flock.
	Observable observable;
public:
	Flock() : observable(*this) {}
	void add(PtrQuackable quacker) { quackers.push_back(std::move(quacker)); } // The add() method adds a Quackable to the Flock.

	void quack() override { // Now for the quack() method - after all, the Flock is a Quackable too. The quack() method in Flock needs to work over the entire Flock. Here we iterate through the ArrayList and call quack() on each element.
		for (auto const &quacker : quackers) // There it is! The Iterator Pattern at work!
			quacker->quack();
	}

	void registerObserver(PtrObserver observer) override { 
		for (auto &quacker : quackers) 
			quacker->registerObserver(observer);
	}

	void notifyObservers() override { 
		for (const auto &quacker : quackers)
			quacker->notifyObservers(); 
	}
};
#pragma endregion //Integrate the helper Observable with the Quackable classes