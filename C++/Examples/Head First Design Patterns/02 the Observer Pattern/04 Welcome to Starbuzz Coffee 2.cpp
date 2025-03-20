#ifdef AMAZON_Q_OPTIMIZED

#include <memory>
#include <numeric>
#include "../../stdafx.h"
using namespace std;

class Beverage;

class Condiment { // Base Condiment interface
public:
    virtual ~Condiment() = default;
    virtual double cost() const noexcept = 0;
    virtual string getName() const = 0;
};

class SteamedMilk final : public Condiment { // Concrete Condiments
    static constexpr double COST = 10.0;
public:
    double cost() const noexcept override { return COST; }
    string getName() const override { return "Steamed Milk"; }
};

class Soy final : public Condiment {
    static constexpr double COST = 20.0;
public:
    double cost() const noexcept override { return COST; }
    string getName() const override { return "Soy"; }
};

class Mocha final : public Condiment {
    static constexpr double COST = 30.0;
public:
    double cost() const noexcept override { return COST; }
    string getName() const override { return "Mocha"; }
};

class WhippedMilk final : public Condiment {
    static constexpr double COST = 40.0;
public:
    double cost() const noexcept override { return COST; }
    string getName() const override { return "Whipped Milk"; }
};

class CondimentSet { // Separated condiment management into CondimentSet class
    vector<unique_ptr<Condiment>> condiments;
public:
	CondimentSet() = default;
	CondimentSet(const CondimentSet &) = delete; //TO DO
	CondimentSet &operator=(const CondimentSet &) = delete; //TO DO
	CondimentSet(CondimentSet &&) noexcept = default;
	CondimentSet &operator=(CondimentSet &&) noexcept = default;

    void addCondiment(unique_ptr<Condiment> condiment) {
        if (!condiment) 
            throw invalid_argument("Cannot add null condiment");
        condiments.push_back(std::move(condiment));
    }
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
    const double baseCost_;
    CondimentSet condiments_;
public:
    Beverage(string_view description, double baseCost) : description_(description), baseCost_(baseCost) {}
	virtual ~Beverage() = default;
    Beverage(const Beverage&) = delete; //TO DO
    Beverage &operator=(const Beverage &) = delete; //TO DO
    Beverage(Beverage&&) noexcept = default;
    Beverage &operator=(Beverage &&) noexcept = default;

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
