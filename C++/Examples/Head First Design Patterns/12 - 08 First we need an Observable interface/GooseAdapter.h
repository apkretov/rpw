#pragma once

#include <string>
#include "Goose.h"
#include "Quackable.h"

#pragma region Integrate the helper Observable with the Quackable classes
class GooseAdapter : public Quackable {
	Goose goose;
	Observable observable;
public:
	explicit GooseAdapter(const Goose& goose) : goose(goose), observable(*this) {}
	void quack() override { goose.honk(); }
	std::string toString() const { return "Goose pretending to be a Duck"; }
	void registerObserver(PtrObserver observer) override { observable.registerObserver(observer); }
	void notifyObservers() const override { observable.notifyObservers(); }
};
#pragma endregion //Integrate the helper Observable with the Quackable classes