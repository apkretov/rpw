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