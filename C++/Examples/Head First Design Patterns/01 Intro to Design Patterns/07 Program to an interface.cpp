#if 1

#include <array>
#include <memory>
#include "../../stdafx.h"
using namespace std;

struct Animal {
	virtual ~Animal() = default;
	virtual void makeSound() = 0;
};

void bark() { cout << "Make a bark sound.\n"; }
void meow() { cout << "Make a meow sound.\n"; }

struct Dog final : Animal {
	void makeSound() override { bark(); }
};

struct Cat final : Animal {
	void makeSound() override { meow(); }
};

int main(int argc, char *argv[]) {
	print_file_line();

	auto a = make_unique<Dog>(); // Programming to an interface/supertype
	a->makeSound();

#pragma region MINE
	auto a2 = make_unique<Cat>();
	array<unique_ptr<Animal>, 2> arr = {std::move(a), std::move(a2)};
	for (const auto &a : arr)
		a->makeSound();
#pragma endregion MINE

	return 0;
}
#endif //1