#if 1

#include <array>
#include <memory>
#include "../../stdafx.h"
using namespace std;

struct WeaponBehavior {
	~WeaponBehavior() = default;
	virtual void useWeapon() const = 0;
};

struct KnifeBehavior : WeaponBehavior {
	void useWeapon() const override { cout << "Cutting with a knife.\n"; }
};

struct BowAndArrowBehavior : WeaponBehavior {
	void useWeapon() const override { cout << "Shooting an arrow with a bow.\n"; }
};

struct AxeBehavior : WeaponBehavior {
	void useWeapon() const override { cout << "Chopping with an axe.\n"; }
};

struct SwordBehavior : WeaponBehavior {
	void useWeapon() const override { cout << "Swinging a sword.\n"; }
};

class Character {
	unique_ptr<WeaponBehavior> weapon;
public:
	Character(unique_ptr<WeaponBehavior> quack_behavior) : weapon(std::move(quack_behavior)) {}
	~Character() = default;
	virtual void fight() const = 0;
	void useWeapon() { weapon->useWeapon(); }
	void setWeaponBehavior(unique_ptr<WeaponBehavior> w) { weapon = std::move(w); }
};

struct King : Character {
	King() : Character(make_unique<SwordBehavior>()) {}
	void fight() const override { cout << "The king fights.\n"; }
};

struct Queen : Character {
	Queen() : Character(make_unique<KnifeBehavior>()) {}
	void fight() const override { cout << "The queen fights.\n"; }
};

struct Knight : Character {
	Knight() : Character(make_unique<AxeBehavior>()) {}
	void fight() const override { cout << "The knight fights.\n"; }
};

struct Troll : Character {
	Troll() : Character(make_unique<BowAndArrowBehavior>()) {}
	void fight() const override { cout << "The troll fights.\n"; }
};

int main() {
	print_file_line();

	array<unique_ptr<Character>, 4> characters = {
		make_unique<King>(),
		make_unique<Queen>(),
		make_unique<Knight>(),
		make_unique<Troll>()
	};

	for (auto const &character : characters) {
		character->fight();
		character->useWeapon();
		character->setWeaponBehavior(make_unique<SwordBehavior>());
		character->useWeapon();
		cout << '\n';
	}

	return 0;
}
#endif //1
