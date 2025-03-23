#if 1

#include "../../stdafx.h"
using namespace std;

enum class BeverageSize { tall, grande, venti };

class Beverage {             
	string description = "Unknown Beverage";
	BeverageSize size = BeverageSize::tall;
public:
	virtual ~Beverage() {}
	virtual string getDescription() { return description; }                 
	virtual double cost() = 0;
	virtual void setSize(BeverageSize size) { this->size = size; }
	BeverageSize getSize() const noexcept { return size; }
protected:
	void setDescription(const string &description) { this->description = description; }
};

using BeveragePtr = unique_ptr<Beverage>;

struct CondimentDecorator : Beverage {                 
	virtual string getDescription() = 0;                      
};

struct Espresso : public Beverage {            
	Espresso() { setDescription("Espresso"); }                         
	double cost() override { return 1.99; }                                  
};

struct HouseBlend : public Beverage {                         
	HouseBlend() { setDescription("House Blend Coffee"); }
	double cost() override { return .89; }
};

class Mocha : public CondimentDecorator {
    BeveragePtr beverage;
    static const inline unordered_map<BeverageSize, double> SIZE_COSTS = {
        {BeverageSize::tall, .15},
        {BeverageSize::grande, .20},
        {BeverageSize::venti, .25}
    };
public:
    Mocha(BeveragePtr beverage) { this->beverage = std::move(beverage); }
    string getDescription() override { return beverage->getDescription() + ", Mocha"; }
    double cost() override { return SIZE_COSTS.at(beverage->getSize()) + beverage->cost(); }
	void setSize(BeverageSize size) override { beverage->setSize(size); }
};

class Soy : public CondimentDecorator {
    BeveragePtr beverage;
    static const inline unordered_map<BeverageSize, double> SIZE_COSTS = {
        {BeverageSize::tall, .10},
        {BeverageSize::grande, .15},
        {BeverageSize::venti, .20}
    };
public:
    Soy(BeveragePtr beverage) { this->beverage = std::move(beverage); }
    string getDescription() override { return beverage->getDescription() + ", Soy"; }
    double cost() override { return SIZE_COSTS.at(beverage->getSize()) + beverage->cost(); }
    
	void setSize(BeverageSize size) override { 
        Beverage::setSize(size);
        beverage->setSize(size); 
    }
};

class Whip : public CondimentDecorator {
    BeveragePtr beverage;
    static const inline unordered_map<BeverageSize, double> SIZE_COSTS = {
        {BeverageSize::tall, .05},
        {BeverageSize::grande, .10},
        {BeverageSize::venti, .15}
    };
public:
    Whip(BeveragePtr beverage) { this->beverage = std::move(beverage); }
    string getDescription() override { return beverage->getDescription() + ", Whip"; }
    double cost() override { return SIZE_COSTS.at(beverage->getSize()) + beverage->cost(); }
    
	void setSize(BeverageSize size) override { 
        Beverage::setSize(size);
        beverage->setSize(size); 
    }
};

int main(int argc, char *argv[]) {
	print_file_line();

	BeveragePtr beverage = make_unique<HouseBlend>();
	cout << beverage->getDescription() << " $" << beverage->cost() << "\n\n";

	beverage = make_unique<Mocha>(std::move(beverage));
	cout << beverage->getDescription() << " $" << beverage->cost() << '\n';
	cout << AS_KV(static_cast<size_t>(beverage->getSize())) << "\n\n";

	beverage->setSize(BeverageSize::grande);
	cout << beverage->getDescription() << " $" << beverage->cost() << '\n';
	cout << AS_KV(static_cast<size_t>(beverage->getSize())) << "\n\n";

	beverage->setSize(BeverageSize::venti);
	cout << beverage->getDescription() << " $" << beverage->cost() << '\n';
	cout << AS_KV(static_cast<size_t>(beverage->getSize())) << '\n';

	return 0;
}
#endif //1