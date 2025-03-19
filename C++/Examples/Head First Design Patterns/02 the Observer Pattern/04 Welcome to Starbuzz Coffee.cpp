#ifdef MINE

#include <memory>
#include "../../stdafx.h"
using namespace std;

struct Condiment {
	virtual ~Condiment() = default;
	virtual constexpr double cost() const = 0;
};

struct SteamedMilk : Condiment {
	constexpr double cost() const override { return 10; }
};

struct Soy : Condiment {
	constexpr double cost() const override { return 20; }
};

struct Mocha : Condiment {
	constexpr double cost() const override { return 30; }
};

struct WhippedMilk : Condiment {
	constexpr double cost() const override { return 40; }
};

class Condiments {
	vector<unique_ptr<Condiment>> condiments;
public:
	virtual ~Condiments() = default;
	void addCondiment(unique_ptr<Condiment> condiment) { condiments.push_back(std::move(condiment)); };

	double cost() const {
		double sum = 0;
		for (const auto &condiment : condiments)
			sum += condiment->cost();
		return sum;
	}
};

struct SteamedMilkandMocha : Condiments { //TO DO: Instead of creating all these classes, sets of condiments can be stored in Beverage.
	SteamedMilkandMocha() {
		addCondiment(make_unique<SteamedMilk>());
		addCondiment(make_unique<Mocha>());
	}
};

struct WhipAndSoy : Condiments {
	WhipAndSoy() {
		addCondiment(make_unique<WhippedMilk>());
		addCondiment(make_unique<Soy>());
	}
};

class Beverage {
	string description_; //TO DO: Move all these to the derived classes or store here.
	double cost_;
	unique_ptr<Condiments> condiments_;
public:
	Beverage(string_view description, double cost, unique_ptr<Condiments> condiments) : description_(description), cost_(cost), condiments_(std::move(condiments)) {}
	virtual ~Beverage() = default;
	Beverage(const Beverage &) = delete; //TO DO
	Beverage &operator=(const Beverage &) = delete; //TO DO
	Beverage(Beverage &&) = default;
	Beverage &operator=(Beverage &&) = default;

	string getDescription() const { return description_; }
	double cost() const { return cost_ + condiments_->cost(); } // The condiments cost can change any time, so sum them up each time here.
};

struct HouseBlend : Beverage {
	HouseBlend(unique_ptr<Condiments> condiments) : Beverage("Most Excellent House Blend", 10, std::move(condiments)) {}
};

struct DarkRoast : Beverage {
	DarkRoast(unique_ptr<Condiments> condiments) : Beverage("Most Excellent Dark Roast", 20, std::move(condiments)) {}
};

struct Decaf : Beverage {
	Decaf(unique_ptr<Condiments> condiments) : Beverage("Most Excellent Decaf", 30, std::move(condiments)) {}
};

struct Espresso : Beverage {
	Espresso(unique_ptr<Condiments> condiments) : Beverage("Most Excellent Espresso", 40, std::move(condiments)) {}
};

int main(int argc, char *argv[]) {
	print_file_line();

	HouseBlend house_blend_with_steamed_milk_and_mocha(make_unique<SteamedMilkandMocha>());
	cout << AS_KV(house_blend_with_steamed_milk_and_mocha.getDescription()) << '\n';
	cout << AS_KV(house_blend_with_steamed_milk_and_mocha.cost()) << '\n';
	cout << '\n';

	HouseBlend espresso_with_whip_and_soy(make_unique<WhipAndSoy>());
	cout << AS_KV(espresso_with_whip_and_soy.getDescription()) << '\n';
	cout << AS_KV(espresso_with_whip_and_soy.cost()) << '\n';

	return 0;
}
#endif //MINE

#ifndef AMAZON_Q_OPTIMIZED

#include <memory>
#include <numeric>
#include "../../stdafx.h"
using namespace std;

class Beverage;

class Condiment { // Base Condiment interface
public:
    virtual ~Condiment() = default;
    virtual constexpr double cost() const = 0;
    virtual string getName() const = 0;
};

class SteamedMilk final : public Condiment { // Concrete Condiments
    static constexpr double COST = 10.0;
public:
    constexpr double cost() const override { return COST; }
    string getName() const override { return "Steamed Milk"; }
};

class Soy final : public Condiment {
    static constexpr double COST = 20.0;
public:
    constexpr double cost() const override { return COST; }
    string getName() const override { return "Soy"; }
};

class Mocha final : public Condiment {
    static constexpr double COST = 30.0;
public:
    constexpr double cost() const override { return COST; }
    string getName() const override { return "Mocha"; }
};

class WhippedMilk final : public Condiment {
    static constexpr double COST = 40.0;
public:
    constexpr double cost() const override { return COST; }
    string getName() const override { return "Whipped Milk"; }
};

class CondimentSet { // Separated condiment management into CondimentSet class
    vector<unique_ptr<Condiment>> condiments;
public:
    void addCondiment(unique_ptr<Condiment> condiment) { condiments.push_back(std::move(condiment)); }
    double calculateTotalCost() const { return accumulate(condiments.begin(), condiments.end(), 0.0, [](double sum, const auto& condiment) { return sum + condiment->cost(); }); }

    string getDescription() const {
        string description;
        for (const auto& condiment : condiments) {
            if (!description.empty()) 
				description += ", "; 
			description += condiment->getName();
        }
        return description;
    }
};

class Beverage { // Base Beverage class
    string description_;
    double baseCost_;
    CondimentSet condiments_;
public:
    explicit Beverage(string_view description, double baseCost) : description_(description), baseCost_(baseCost) {}

    virtual ~Beverage() = default;
    Beverage(const Beverage&) = delete;
    Beverage& operator=(const Beverage&) = delete;
    Beverage(Beverage&&) = default;
    Beverage& operator=(Beverage&&) = default;

    string getDescription() const {
        string desc = description_;
        const auto condimentDesc = condiments_.getDescription();
        if (!condimentDesc.empty()) {
            desc += " with " + condimentDesc;
        }
        return desc;
    }

    double cost() const { return baseCost_ + condiments_.calculateTotalCost(); }
    void addCondiment(unique_ptr<Condiment> condiment) { condiments_.addCondiment(std::move(condiment)); }
};

class HouseBlend final : public Beverage { // Concrete Beverages
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

template<typename T, typename... Args>
unique_ptr<T> make_condiment(Args&&... args) { return make_unique<T>(forward<Args>(args)...); }

int main() {
    print_file_line();

    auto house_blend = make_unique<HouseBlend>();
    house_blend->addCondiment(make_condiment<SteamedMilk>());
    house_blend->addCondiment(make_condiment<Mocha>());

    cout << "Description: " << house_blend->getDescription() << '\n';
    cout << "Cost: $" << house_blend->cost() << '\n';
    cout << '\n';

    auto espresso = make_unique<Espresso>();
    espresso->addCondiment(make_condiment<WhippedMilk>());
    espresso->addCondiment(make_condiment<Soy>());

    cout << "Description: " << espresso->getDescription() << '\n';
    cout << "Cost: $" << espresso->cost() << '\n';

    return 0;
}
#endif //AMAZON_Q_OPTIMIZED
