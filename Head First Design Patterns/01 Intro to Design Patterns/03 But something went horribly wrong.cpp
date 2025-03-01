#if 0

#define ORIG

#include <array>
#include <memory>
#include "../../stdafx.h"
using namespace std;

#ifdef ORIG
#include "02 But now we need the ducks to FLY.h"
#include "01 It started with a simple SimUDuck app 2.h"

#else //MINE
#include "01 It started with a simple SimUDuck app 1.h"

struct FlyingDuck : Duck {
	void fly() const { cout << "The duck flies.\n"; }
};

struct MallardDuck final : FlyingDuck {
	void display() const override { cout << "The duck looks like a mallard.\n"; }
};

struct RedheadDuck final : FlyingDuck {
	void display() const override { cout << "The duck looks like a redhead.\n"; }
};
#endif //MINE

struct RubberDuck final : Duck {
	void quack() const override { cout << "The duck squeaks.\n"; }
	void display() const override { cout << "The duck looks like a rubber duck.\n"; }
};

int main() {
	print_file_line();

	array<unique_ptr<Duck>, 3> ducks = {
		make_unique<MallardDuck>(),
		make_unique<RedheadDuck>(),
		make_unique<RubberDuck>()
	};

	for (const auto &duck : ducks) {
		duck->quack();
		duck->swim();
		duck->display();
#ifdef ORIG
		duck->fly();
#else //MINE
		if (auto flying_duck = dynamic_cast<FlyingDuck *>(duck.get()); flying_duck != nullptr)
			flying_duck->fly();
#endif //MINE
		cout << '\n';
	}

	return 0;
}
#endif 
