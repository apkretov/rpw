#ifndef MINE

#include <memory>
#include "../../stdafx.h"
using namespace std;

class Beverage {
protected:
	string description_;
	const double baseCost_;
	bool hasMilk_ = false;
	bool hasSoy_ = false;
	bool hasMocha_ = false;
	bool hasWhip_ = false;
public:
	explicit Beverage(string_view description, double baseCost) : description_(description), baseCost_(baseCost) {
		if (baseCost < 0)
			throw invalid_argument("Base cost cannot be negative");
	}

	virtual ~Beverage() = default;
	Beverage(const Beverage&) = delete;
	Beverage& operator=(const Beverage&) = delete;
	Beverage(Beverage&&) noexcept = default;
	Beverage& operator=(Beverage&&) noexcept = default;

	string getDescription() const {
		string desc = description_;
		if (hasMilk_ || hasSoy_ || hasMocha_ || hasWhip_) {
			desc += " with";
			if (hasMilk_) desc += " Steamed Milk";
			if (hasSoy_) desc += (hasMilk_ ? "," : "") + string(hasMilk_ ? " " : "") + "Soy";
			if (hasMocha_) desc += (hasMilk_ || hasSoy_ ? "," : "") + string(hasMilk_ || hasSoy_ ? " " : "") + "Mocha";
			if (hasWhip_) desc += (hasMilk_ || hasSoy_ || hasMocha_ ? "," : "") + string(hasMilk_ || hasSoy_ || hasMocha_ ? " " : "") + "Whipped Milk";
		}
		return desc;
	}

	virtual double cost() const noexcept {
		double condimentCost = 0.0;
		if (hasMilk_) condimentCost += 10.0;
		if (hasSoy_) condimentCost += 20.0;
		if (hasMocha_) condimentCost += 30.0;
		if (hasWhip_) condimentCost += 40.0;
		return baseCost_ + condimentCost;
	}

	void addMilk() { hasMilk_ = true; }
	void addSoy() { hasSoy_ = true; }
	void addMocha() { hasMocha_ = true; }
	void addWhip() { hasWhip_ = true; }
};

class HouseBlend final : public Beverage {
	static constexpr double BASE_COST = 10.0;
public:
	HouseBlend() : Beverage("House Blend Coffee", BASE_COST) {}
};

class DarkRoast final : public Beverage {
	static constexpr double BASE_COST = 20.0;
public:
	DarkRoast() : Beverage("Dark Roast Coffee", BASE_COST) {}
};

class Decaf final : public Beverage {
	static constexpr double BASE_COST = 30.0;
public:
	Decaf() : Beverage("Decaf Coffee", BASE_COST) {}
};

class Espresso final : public Beverage {
	static constexpr double BASE_COST = 40.0;
public:
	Espresso() : Beverage("Espresso", BASE_COST) {}
};

int main() {
	print_file_line();

	auto house_blend = make_unique<HouseBlend>();
	house_blend->addMilk();
	house_blend->addMocha();

	cout << "Description: " << house_blend->getDescription() << '\n';
	cout << "Cost: $" << house_blend->cost() << '\n';
	cout << '\n';

	auto espresso = make_unique<Espresso>();
	espresso->addWhip();
	espresso->addSoy();

	cout << "Description: " << espresso->getDescription() << '\n';
	cout << "Cost: $" << espresso->cost() << '\n';

	return 0;
}
#endif //MINE
