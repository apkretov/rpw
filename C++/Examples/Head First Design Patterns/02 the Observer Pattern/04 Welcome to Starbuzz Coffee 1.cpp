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
