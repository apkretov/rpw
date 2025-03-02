#if 0

#include <array>
#include <memory>
#include "../../stdafx.h"
using namespace std;

#include "02 But now we need the ducks to FLY.h"
#include "01 It started with a simple SimUDuck app 2.h"

int main() {
	print_file_line();

	array<unique_ptr<Duck>, 2> ducks = {
		make_unique<MallardDuck>(),
		make_unique<RedheadDuck>()
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
