#if 0

#include <array>
#include "../../stdafx.h"
#include "04 Joe thinks about inheritance 2.h"
using namespace std;

struct FlyRocketPowered final : FlyBehavior {
	void fly() const override { cout << "The duck flies rocket-powered.\n"; }
};

struct RocketDuck final : Duck {
	RocketDuck() : Duck(make_unique<MuteQuack>(), make_unique<FlyRocketPowered>()) {}
	void display() const override { cout << "The duck looks like a rocket duck.\n"; }
};

int main() {
	print_file_line();

	array<unique_ptr<Duck>, 5> ducks = {
		make_unique<MallardDuck>(),
		make_unique<RedheadDuck>(),
		make_unique<RubberDuck>(),
		make_unique<DecoyDuck>(),
		make_unique<RocketDuck>()
	};

	for (const auto &duck : ducks) {
		duck->quack();
		duck->swim();
		duck->display();
		duck->fly();
		cout << '\n';
	}
	return 0;
}
#endif 
