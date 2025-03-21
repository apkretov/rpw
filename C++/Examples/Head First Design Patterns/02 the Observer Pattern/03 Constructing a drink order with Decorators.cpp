#ifdef CURSOR

#include <memory>
#include "../../stdafx.h"
using namespace std;

class Beverage {
protected:
	string description_;
	const double baseCost_;
public:
	explicit Beverage(string_view description, double baseCost) 
		: description_(description), baseCost_(baseCost) {
		if (baseCost < 0) {
			throw invalid_argument("Base cost cannot be negative");
		}
	}

	virtual ~Beverage() = default;
	Beverage(const Beverage&) = delete;
	Beverage& operator=(const Beverage&) = delete;
	Beverage(Beverage&&) noexcept = default;
	Beverage& operator=(Beverage&&) noexcept = default;

	[[nodiscard]] virtual string getDescription() const { return description_; }
	[[nodiscard]] virtual double cost() const noexcept { return baseCost_; }
};

// Base decorator class
class CondimentDecorator : public Beverage {
protected:
	unique_ptr<Beverage> beverage_;
public:
	explicit CondimentDecorator(unique_ptr<Beverage> beverage) 
		: Beverage("", 0), beverage_(std::move(beverage)) {}

	[[nodiscard]] string getDescription() const override {
		return beverage_->getDescription();
	}

	[[nodiscard]] double cost() const noexcept override {
		return beverage_->cost();
	}
};

// Concrete decorators
class Mocha final : public CondimentDecorator {
	static constexpr double COST = 30.0;
public:
	explicit Mocha(unique_ptr<Beverage> beverage) 
		: CondimentDecorator(std::move(beverage)) {}

	[[nodiscard]] string getDescription() const override {
		return beverage_->getDescription() + ", Mocha";
	}

	[[nodiscard]] double cost() const noexcept override {
		return beverage_->cost() + COST;
	}
};

class Whip final : public CondimentDecorator {
	static constexpr double COST = 40.0;
public:
	explicit Whip(unique_ptr<Beverage> beverage) 
		: CondimentDecorator(std::move(beverage)) {}

	[[nodiscard]] string getDescription() const override {
		return beverage_->getDescription() + ", Whip";
	}

	[[nodiscard]] double cost() const noexcept override {
		return beverage_->cost() + COST;
	}
};

class Soy final : public CondimentDecorator {
	static constexpr double COST = 20.0;
public:
	explicit Soy(unique_ptr<Beverage> beverage) 
		: CondimentDecorator(std::move(beverage)) {}

	[[nodiscard]] string getDescription() const override {
		return beverage_->getDescription() + ", Soy";
	}

	[[nodiscard]] double cost() const noexcept override {
		return beverage_->cost() + COST;
	}
};

class SteamedMilk final : public CondimentDecorator {
	static constexpr double COST = 10.0;
public:
	explicit SteamedMilk(unique_ptr<Beverage> beverage) 
		: CondimentDecorator(std::move(beverage)) {}

	[[nodiscard]] string getDescription() const override {
		return beverage_->getDescription() + ", Steamed Milk";
	}

	[[nodiscard]] double cost() const noexcept override {
		return beverage_->cost() + COST;
	}
};

// Concrete beverages
class DarkRoast final : public Beverage {
	static constexpr double BASE_COST = 20.0;
public:
	DarkRoast() : Beverage("Dark Roast Coffee", BASE_COST) {}
};

class HouseBlend final : public Beverage {
	static constexpr double BASE_COST = 10.0;
public:
	HouseBlend() : Beverage("House Blend Coffee", BASE_COST) {}
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

	// Create a DarkRoast
	unique_ptr<Beverage> beverage = make_unique<DarkRoast>();
	cout << beverage->getDescription() << " $" << beverage->cost() << '\n';

	// Wrap it with Mocha
	unique_ptr<Beverage> mocha = make_unique<Mocha>(std::move(beverage));
	cout << mocha->getDescription() << " $" << mocha->cost() << '\n';

	// Wrap it with Whip
	unique_ptr<Beverage> whip = make_unique<Whip>(std::move(mocha));
	cout << whip->getDescription() << " $" << whip->cost() << '\n';
	cout << '\n';

	// Create another example with HouseBlend
	unique_ptr<Beverage> beverage2 = make_unique<HouseBlend>();
	cout << beverage2->getDescription() << " $" << beverage2->cost() << '\n';

	// Wrap it with Soy
	unique_ptr<Beverage> soy = make_unique<Soy>(std::move(beverage2));
	cout << soy->getDescription() << " $" << soy->cost() << '\n';

	// Wrap it with Mocha
	unique_ptr<Beverage> mocha2 = make_unique<Mocha>(std::move(soy));
	cout << mocha2->getDescription() << " $" << mocha2->cost() << '\n';

	return 0;
}
#endif //CURSOR

#ifndef MINE

#include <memory>
#include <string>
#include "../../stdafx.h"
using namespace std;

class Beverage; // Forward declaration
using BeveragePtr = std::unique_ptr<Beverage>;

class Beverage { // Base class for all beverages
	double cost_;
	string description_;
public:
	explicit Beverage(double base_cost, string_view description = "Unknown Beverage") : cost_(base_cost), description_(description) {}
	virtual ~Beverage() = default;
	virtual double cost() const { return cost_; }
	virtual string getDescription() const { return description_; }
};

class HouseBlend final : public Beverage { // Concrete beverage
	static constexpr double COST = 100.0;
public:
	HouseBlend() : Beverage(COST, "House Blend Coffee") {}
};

class DarkRoast final : public Beverage { // Concrete beverage
	static constexpr double COST = 200.0;
public:
	DarkRoast() : Beverage(COST, "Dark Roast Coffee") {}
};

class Decaf final : public Beverage { // Concrete beverage
	static constexpr double COST = 300.0;
public:
	Decaf() : Beverage(COST, "Decaf Coffee") {}
};

class Espresso final : public Beverage { // Concrete beverage
	static constexpr double COST = 400.0;
public:
	Espresso() : Beverage(COST, "Espresso") {}
};

class Condiment : public Beverage { // Base decorator class
	BeveragePtr beverage_;
	string condiment_name_;
public:
	Condiment(double cost, BeveragePtr beverage, string_view condiment_name)
		: Beverage(cost, ""), beverage_(std::move(beverage)), condiment_name_(condiment_name) {
	}

	double cost() const override { return Beverage::cost() + beverage_->cost(); }
	string getDescription() const override { return beverage_->getDescription() + " with " + condiment_name_; }
};

class SteamedMilk final : public Condiment { // Concrete decorator
	static constexpr double COST = 10.0;
public:
	explicit SteamedMilk(BeveragePtr beverage) : Condiment(COST, std::move(beverage), "Steamed Milk") {}
};

class Soy final : public Condiment { // Concrete decorator
	static constexpr double COST = 20.0;
public:
	explicit Soy(BeveragePtr beverage) : Condiment(COST, std::move(beverage), "Soy") {}
};

class Mocha final : public Condiment { // Concrete decorator
	static constexpr double COST = 30.0;
public:
	explicit Mocha(BeveragePtr beverage) : Condiment(COST, std::move(beverage), "Mocha") {}
};

class WhippedMilk final : public Condiment { // Concrete decorator
	static constexpr double COST = 40.0;
public:
	explicit WhippedMilk(BeveragePtr beverage) : Condiment(COST, std::move(beverage), "Whipped Milk") {}
};

int main() {
	print_file_line();

	auto house_blend = std::make_unique<HouseBlend>();
	cout << "Beverage: " << house_blend->getDescription() << '\n';
	cout << AS_KV(house_blend->cost()) << '\n'; // 100.0

	auto with_steamed_milk = std::make_unique<SteamedMilk>(std::move(house_blend));
	cout << "Beverage: " << with_steamed_milk->getDescription() << '\n';
	cout << AS_KV(with_steamed_milk->cost()) << '\n'; // 110.0

	auto with_steamed_milk_and_soy = std::make_unique<Soy>(std::move(with_steamed_milk));
	cout << "Beverage: " << with_steamed_milk_and_soy->getDescription() << '\n';
	cout << AS_KV(with_steamed_milk_and_soy->cost()) << '\n'; // 130.0

	auto with_double_soy = std::make_unique<Soy>(std::move(with_steamed_milk_and_soy));
	cout << "Beverage: " << with_double_soy->getDescription() << '\n';
	cout << AS_KV(with_double_soy->cost()) << '\n'; // 150.0

	return 0;
}
#endif //MINE
