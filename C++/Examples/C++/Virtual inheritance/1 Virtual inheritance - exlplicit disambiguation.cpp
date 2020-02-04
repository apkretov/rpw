#include "stdafx.h" //Virtual inheritance @ https://en.wikipedia.org/wiki/Virtual_inheritance

class Animal {
public:
	virtual ~Animal() { }
	virtual void eat();
};

class Mammal : public Animal {
public:
	virtual void breathe();
};

class WingedAnimal : public Animal {
public:
	virtual void flap();
};

class Bat : public Mammal, public WingedAnimal {}; // A bat is a winged mammal

int main() {
	Bat bat;
	Bat b;
	//Animal& a = b; // error: which Animal subobject should a Bat cast into, a Mammal::Animal or a WingedAnimal::Animal?
	
	Animal& mammal = static_cast<Mammal&> (b); //Explicitl conversion.
	Animal& winged = static_cast<WingedAnimal&> (b);
	
	static_cast<Mammal&>(bat).eat(); //Explicit qualification.
	bat.Mammal::eat(); //Alternatively.
	
	static_cast<WingedAnimal&>(bat).eat();  //Explicit qualification.
	bat.WingedAnimal::eat(); //Alternatively.
}

