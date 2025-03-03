#pragma once

#include <format>
#include <iostream>
#include <string>
using std::cout;
using std::format;
using std::max;
using std::ostream;
using std::string;

#pragma region MINE
class ZooAnimal { //VER4
	friend ostream &operator<<(ostream &, const ZooAnimal &);
public:
 	ZooAnimal() = default;
	ZooAnimal(string const &name, bool onExhibit) : name(name), onExhibit(onExhibit) {}

	virtual ~ZooAnimal() {
		cout << "virtual ~ZooAnimal()\n";
	}

	virtual void print() {
		cout << "virtual void ZooAnimal::print: " << *this << '\n';
	}

	virtual double max_weight() {
		cout << "virtual double ZooAnimal::max_weight()\n";
		return 111;
	}
private:
	string name;
	bool onExhibit{};
};

ostream &operator<<(ostream &os, const ZooAnimal &za) {
	os << format("Name = '{}'\tonExhibit = {}", za.name, za.onExhibit);
	return os;
}
#pragma endregion

#pragma region Multiple Inheritance
#pragma region Using a Virtual Base Class
class Bear : virtual public ZooAnimal { //VER4 //TEST! //																								the order of the keywords public and virtual is not significant
#pragma endregion
#pragma region MINE
	string species;
public:
	Bear() : ZooAnimal("Bear", false), species("Grizzly") {};
	Bear(string const &name, bool onExhibit, string const &species) : ZooAnimal(name, onExhibit), species(species) {}

	void print() override {
		cout << "void Bear::print() override: " << *this << '\n';
	}

	virtual void toes() {
		cout << "virtual void Bear::toes()\n";
	}

	double max_weight() override {
		return 0;
	}
#pragma endregion
};

#pragma region Using a Virtual Base Class
class Raccoon : public virtual ZooAnimal { //VER1 //TEST //																						the order of the keywords public and virtual is not significant
	using ZooAnimal::ZooAnimal; //MINE
}; 
#pragma endregion

#pragma region MINE
class Endangered {
	enum class Severity { low, medium, high, critical };
	Severity severity;
public:
	explicit Endangered(Severity sever) : severity(sever) {}

	virtual ~Endangered() {
		cout << "virtual ~Endangered()\n";
	}

	virtual void print() {
		cout << format("virtual void Endangered::print(): severity = {}", static_cast<int>(severity)) << '\n';
	}

	virtual void highlight() {
		cout << "virtual void Endangered::highlight()\n";
	}

	virtual double max_weight() {
		cout << "virtual double Endangered::max_weight()\n";
		return 222;
	}

	static const Severity low = Severity::low;
	static const Severity medium = Severity::medium;
	static const Severity high = Severity::high;
	static const Severity critical = Severity::critical;
};
#pragma endregion

#pragma region Using a Virtual Base Class
class Panda : public Bear, public Raccoon, public Endangered { //VER4 //TEST
#pragma endregion
#pragma region MINE
public:
	Panda();
	Panda(const string &name, bool onExhibit = false);

	void print() final {
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

	double max_weight() final;
#pragma endregion
};
#pragma endregion

#pragma region Derived Constructors Initialize All Base Classes
//ORIG Panda::Panda(string name, bool onExhibit) : Bear(name, onExhibit, "Panda"), Endangered(Endangered::critical) {} // explicitly initialize both base classes
Panda::Panda(const string &name, bool onExhibit) : Bear(name, onExhibit, "Panda"), Endangered(Endangered::critical) {} // explicitly initialize both base classes
Panda::Panda() : Endangered(Endangered::critical) {} // implicitly uses the Bear default constructor to initialize the Bear subobject
#pragma endregion

#pragma region Class Scope under Multiple Inheritance
double Panda::max_weight() /*ORIG const*/ {
	cout << "double Panda::max_weight() final\n";
	return max(ZooAnimal::max_weight(), Endangered::max_weight());
}
#pragma endregion
