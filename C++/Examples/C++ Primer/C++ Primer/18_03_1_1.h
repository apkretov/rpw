#pragma once

#include <string>
using std::string;

#pragma region MINE
class ZooAnimal { //VER1
	string name;
	bool onExhibit;
public:
	ZooAnimal(string const &name, bool onExhibit) : name(name), onExhibit(onExhibit) {}
};
#pragma endregion

#pragma region Multiple Inheritance
class Bear : public ZooAnimal {  //VER1
#pragma region MINE
	string species;
public:
	Bear() : ZooAnimal("Bear", false), species("Grizzly") {};
	Bear(string const &name, bool onExhibit, string const &species) : ZooAnimal(name, onExhibit), species(species) {}
#pragma endregion
};

#pragma region MINE
class Endangered {  //VER1
	enum class Severity { low, medium, high, critical }; //TEST!
	Severity severity;
public:
	explicit Endangered(Severity sever) : severity(sever) {}
	static const Severity low = Severity::low;
	static const Severity medium = Severity::medium;
	static const Severity high = Severity::high;
	static const Severity critical = Severity::critical;
};
#pragma endregion

class Panda : public Bear, public Endangered {  //VER1
#pragma region MINE
public:
	Panda();
	Panda(const string &name, bool onExhibit);
#pragma endregion
};
#pragma endregion

#pragma region Derived Constructors Initialize All Base Classes
//ORIG Panda::Panda(string name, bool onExhibit) : Bear(name, onExhibit, "Panda"), Endangered(Endangered::critical) {} // explicitly initialize both base classes
Panda::Panda(const string &name, bool onExhibit) : Bear(name, onExhibit, "Panda"), Endangered(Endangered::critical) {} // explicitly initialize both base classes
Panda::Panda() : Endangered(Endangered::critical) {} // implicitly uses the Bear default constructor to initialize the Bear subobject
#pragma endregion
