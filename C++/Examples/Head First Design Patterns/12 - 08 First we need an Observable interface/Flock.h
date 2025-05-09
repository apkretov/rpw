#pragma once

#include <memory>
#include <vector>
#include "Quackable.h"

#pragma region Sharpen your pencil
class Flock : public Quackable { // Flock is a Quackable, so now it’s a QuackObservable too.
	std::vector<PtrQuackable> quackers; // Here’s the Quackables that are in the Flock.
	Observable observable;
public:
	Flock() : observable(*this) {}
	void add(PtrQuackable quacker) { quackers.push_back(std::move(quacker)); }          

	void quack() override {                                       
		for (auto const &quacker : quackers)         
			quacker->quack();
	}

	void registerObserver(PtrObserver observer) override { // When you register as an Observer with the Flock, you actually get registered with everything that’s IN the flock, which is every Quackable, whether it’s a duck or another Flock.
		for (auto &quacker : quackers)  // We iterate through all the Quackables in the Flock and delegate the call to each Quackable.If the Quackable is another Flock, it will do the same.
			quacker->registerObserver(observer);
	}

	void notifyObservers() const override {} //TEST! // Each Quackable does its own notification, so Flock doesn’t have to worry about it. This happens when Flock delegates quack() to each Quackable in the Flock.
};
#pragma endregion //Sharpen your pencil