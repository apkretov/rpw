#pragma once

#include <format>
#include <iostream>
#include <string>
using std::cout;
using std::format;
using std::ostream;
using std::string;

#pragma region MINE
class ZooAnimal { //VER2
friend ostream &operator<<(ostream &, const ZooAnimal &);
public:
	ZooAnimal(string const &name, bool onExhibit) : name(name), onExhibit(onExhibit) {
		cout << "ZooAnimal(string const &name, bool onExhibit)\n";
	}

	virtual ~ZooAnimal() {
		cout << "virtual ~ZooAnimal()\n";
	}

	virtual void print() {
		cout << "virtual void ZooAnimal::print: " << *this << '\n';
	}
private:
	string name;
	bool onExhibit;
};

ostream &operator<<(ostream &os, const ZooAnimal &za) {
	os << format("Name = '{}'\tOn Exhibit = {}", za.name, za.onExhibit);
	return os;
}
#pragma endregion

#pragma region Multiple Inheritance
class Bear : public ZooAnimal {  //VER2
#pragma region MINE
	string species;
public:
	Bear() : ZooAnimal("Bear", false), species("Grizzly") {
		cout << "Bear()\n";
	};

	Bear(string const &name, bool onExhibit, string const &species) : ZooAnimal(name, onExhibit), species(species) {
		cout << "Bear(string const &name, bool onExhibit, string const &species)\n";
	}

	void print() override {
		cout << "void Bear::print() override: " << *this << '\n';
	}

	virtual void toes() {
		cout << "virtual void Bear::toes()\n";
	}
#pragma endregion
};

#pragma region MINE
class Endangered {  //VER2
	enum class Severity { low, medium, high, critical };
	Severity severity;
public:
	explicit Endangered(Severity sever) : severity(sever) {
		cout << "Endangered(Severity sever)\n";
	}

	virtual ~Endangered() {
		cout << "virtual ~Endangered()\n";
	}

	virtual void print() {
		cout << format("virtual void Endangered::print(): severity = {}", static_cast<int>(severity)) << '\n';
	}

	virtual void highlight() {
		cout << "virtual void Endangered::highlight()\n";
	}

	static const Severity low = Severity::low;
	static const Severity medium = Severity::medium;
	static const Severity high = Severity::high;
	static const Severity critical = Severity::critical;
};
#pragma endregion

class Panda : public Bear, public Endangered {  //VER2
#pragma region MINE
public:
	Panda();
	Panda(const string &name, bool onExhibit = false);

	void print() final { //TEST!
		cout << "void Panda::print() final: " << *this << '\n';
		cout << "void Panda::print() final: ";
		Endangered::print();
	}

	void highlight() final {
		cout << "void Panda::highlight() final\n";
	}

	void toes() final {
		cout << "void Panda::toes() final\n";
	}

	virtual void cuddle() final {
		cout << "virtual void Panda::cuddle() final\n";
	}
#pragma endregion
};
#pragma endregion

#pragma region Derived Constructors Initialize All Base Classes
//ORIG Panda::Panda(string name, bool onExhibit) : Bear(name, onExhibit, "Panda"), Endangered(Endangered::critical) {} // explicitly initialize both base classes
Panda::Panda(const string &name, bool onExhibit) : Bear(name, onExhibit, "Panda"), Endangered(Endangered::critical) { //MINE
	cout << "Panda(const string &name, bool onExhibit)\n";
} 

Panda::Panda() : Endangered(Endangered::critical) {} // implicitly uses the Bear default constructor to initialize the Bear subobject
#pragma endregion
