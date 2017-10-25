#include "stdafx.h" //Virtual inheritance @ https://en.wikipedia.org/wiki/Virtual_inheritance

class Animal {
public:
	virtual ~Animal() { }
	virtual void eat();
};

class Mammal : public virtual Animal { // Two classes virtually inheriting Animal:
public:
	virtual void breathe();
};

class WingedAnimal : public virtual Animal {
public:
	virtual void flap();
};

class Bat : public Mammal, public WingedAnimal {}; // A bat is still a winged mammal

int main() {
	Bat bat;
	Bat b;
	Animal& a = b;

	a.eat();

	b.eat();
	b.breathe();
	b.flap();
}

