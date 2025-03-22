#if 1

#include "../../stdafx.h"
using namespace std;

#pragma region Writing the Starbuzz code
/* Java
public abstract class Beverage { // Beverage is an abstract class with the two methods getDescription() and cost().
	String description = "Unknown Beverage";
	public String getDescription() { return description; } // getDescription is already implemented for us, but we need to implement cost() in the subclasses.
	public abstract double cost();
}
*/

class Beverage { // Beverage is an abstract class with the two methods getDescription() and cost().
	string description = "Unknown Beverage";
public:
	virtual ~Beverage() {}
	virtual string getDescription() { return description; }  // getDescription is already implemented for us, but we need to implement cost() in the subclasses.
	virtual double cost() = 0;
protected:
	void setDescription(const string &desc) { description = desc; }
};

/* Java
public abstract class CondimentDecorator extends Beverage { // First, we need to be interchangeable with a Beverage, so we extend the Beverage class.
	public abstract String getDescription(); // We're also going to require that the condiment decorators all reimplement the getDescription() method. Again, we'll see why in a sec...
}
*/

struct CondimentDecorator : Beverage { // First, we need to be interchangeable with a Beverage, so we inherit from the Beverage class.
	virtual string getDescription() = 0; // We're also going to require that the condiment decorators all reimplement the getDescription() method. Again, we'll see why in a sec...
};
#pragma endregion //Writing the Starbuzz code

#pragma region Coding beverages
/* Java
public class Espresso extends Beverage { // First we extend the Beverage class, since this is a beverage.
	public Espresso() {	description = "Espresso"; } // To take care of the description, we set this in the constructor for the class. Remember the description instance variable is inherited from Beverage.
	public double cost() { return 1.99;	} // Finally, we need to compute the cost of an Espresso. We don't need to worry about adding in condiments in this class, we just need to return the price of an Espresso: $1.99.
}
*/

struct Espresso : public Beverage { // First we extend the Beverage class, since this is a beverage.
	Espresso() { setDescription("Espresso"); } // To take care of the description, we set this in the constructor for the class. Remember the description instance variable is inherited from Beverage.
	double cost() override { return 1.99; } // Finally, we need to compute the cost of an Espresso. We don't need to worry about adding in condiments in this class, we just need to return the price of an Espresso: $1.99.
};

/*Java
public class HouseBlend extends Beverage { // Okay, here's another Beverage. All we	do is set the appropriate description, "House Blend Coffee, " and then return the correct cost : 89¢.
	public HouseBlend() { description = "House Blend Coffee"; }
	public double cost() { return .89; }
}
*/

struct HouseBlend : public Beverage { // Okay, here's another Beverage. All we do is set the appropriate description, "House Blend Coffee, " and then return the correct cost : 89¢.
	HouseBlend() { setDescription("House Blend Coffee"); }
	double cost() override { return .89; }
};
#pragma endregion //Coding beverages

#pragma region Coding condiments
/*Java
public class Mocha extends CondimentDecorator { // Mocha is a decorator, so we extend CondimentDecorator. // Remember, CondimentDecorator extends Beverage.
	Beverage beverage; // An instance variable to hold the beverage we are wrapping.
	public Mocha(Beverage beverage) { this.beverage = beverage;	} // A way to set this instance	variable to the object we are wrapping.Here, we’re going to pass the beverage we’re wrapping to the decorator’s constructor.
	public String getDescription() { return beverage.getDescription() + ", Mocha"; } // We want our description to not only include the beverage - say "Dark Roast" - but also to include each item decorating the beverage, for instance, "Dark Roast, Mocha". So we first delegate to the object we are decorating to get its description, then append ", Mocha" to that description.
	public double cost() { return .20 + beverage.cost(); } // Now we need to compute the cost of our beverage with Mocha.First, we delegate the call to the object we’re decorating, so that it can compute the cost; then, we add the cost of Mocha to the result.
}
*/

struct Mocha : public CondimentDecorator { // Mocha is a decorator, so we inherit from CondimentDecorator. // Remember, CondimentDecorator inherits from Beverage.
	unique_ptr<Beverage> beverage; // An instance variable to hold the beverage we are wrapping.
	Mocha(unique_ptr<Beverage> beverage) { this->beverage = std::move(beverage); } // A way to set this instance variable to the object we are wrapping. Here, we're going to pass the beverage we're wrapping to the decorator's constructor.
	string getDescription() override { return beverage->getDescription() + ", Mocha"; } // We want our description to not only include the beverage - say "Dark Roast" - but also to include each item decorating the beverage, for instance, "Dark Roast, Mocha". So we first delegate to the object we are decorating to get its description, then append ", Mocha" to that description.
	double cost() override { return .20 + beverage->cost(); } // Now we need to compute the cost of our beverage with Mocha. First, we delegate the call to the object we're decorating, so that it can compute the cost; then, we add the cost of Mocha to the result.
};
#pragma endregion //Coding condiments

#pragma region Sharpen your pencil
struct Soy : public CondimentDecorator {
	unique_ptr<Beverage> beverage;
	Soy(unique_ptr<Beverage> beverage) { this->beverage = std::move(beverage); }
	string getDescription() override { return beverage->getDescription() + ", Soy"; }
	double cost() override { return .15 + beverage->cost(); } // Soy costs 15 cents
};

struct Whip : public CondimentDecorator {
	unique_ptr<Beverage> beverage;
	Whip(unique_ptr<Beverage> beverage) { this->beverage = std::move(beverage); }
	string getDescription() override { return beverage->getDescription() + ", Whip"; }
	double cost() override { return .10 + beverage->cost(); } // Whip costs 10 cents
};
#pragma endregion //Sharpen your pencil

#pragma region Serving some coffees
/* Java
public class StarbuzzCoffee {
	public static void main(String args[]) {
		Beverage beverage = new Espresso();
		System.out.println(beverage.getDescription() + " $" + beverage.cost());
		Beverage beverage2 = new DarkRoast();
		beverage2 = new Mocha(beverage2);
		beverage2 = new Mocha(beverage2);
		beverage2 = new Whip(beverage2);
		System.out.println(beverage2.getDescription() + " $" + beverage2.cost());
		Beverage beverage3 = new HouseBlend();
		beverage3 = new Soy(beverage3);
		beverage3 = new Mocha(beverage3);
		beverage3 = new Whip(beverage3);
		System.out.println(beverage3.getDescription() + " $" + beverage3.cost());
	}
}
*/

int main(int argc, char *argv[]) {
	print_file_line();

	auto beverage = make_unique<Espresso>();
	cout << beverage->getDescription() << " $" << beverage->cost() << endl;

	unique_ptr<Beverage> beverage2 = make_unique<HouseBlend>();
	beverage2 = make_unique<Mocha>(std::move(beverage2));
	beverage2 = make_unique<Mocha>(std::move(beverage2));
	beverage2 = make_unique<Whip>(std::move(beverage2));
	cout << beverage2->getDescription() << " $" << beverage2->cost() << endl;

	unique_ptr<Beverage> beverage3 = make_unique<HouseBlend>();
	beverage3 = make_unique<Soy>(std::move(beverage3));
	beverage3 = make_unique<Mocha>(std::move(beverage3));
	beverage3 = make_unique<Whip>(std::move(beverage3));
	cout << beverage3->getDescription() << " $" << beverage3->cost() << endl;

	return 0;
}
#pragma endregion //Serving some coffees
#endif //1