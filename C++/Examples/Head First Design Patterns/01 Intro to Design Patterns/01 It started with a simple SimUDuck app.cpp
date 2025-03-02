#if 0

#include <array>
#include <memory>
#include "../../stdafx.h"
#include "01 It started with a simple SimUDuck app 1.h"
#include "01 It started with a simple SimUDuck app 2.h"
using namespace std;

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
		cout << '\n';
	}

	return 0;
}
#endif //1
