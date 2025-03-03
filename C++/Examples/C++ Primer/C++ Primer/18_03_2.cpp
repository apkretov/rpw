#ifdef ON

#include <iostream>
#include "../../stdafx.h"
#include "18_03_2.h"
using namespace std;

#pragma region MINE
void print(const Bear &) {}
void highlight(const Endangered &) {}
void print(const Endangered &) {}
#pragma endregion

void Conversions_and_Multiple_Base_Classes_1() {
	void print(const Bear &); // operations that take references to base classes of type Panda
	void highlight(const Endangered &);
	ostream &operator<<(ostream &, const ZooAnimal &);

	Panda ying_yang("ying_yang", true); //ORIG Panda ying_yang("ying_yang");

	print(ying_yang); // passes Panda to a reference to Bear
	highlight(ying_yang); // passes Panda to a reference to Endangered
	cout << ying_yang << endl; // passes Panda to a reference to ZooAnimal
}

void Conversions_and_Multiple_Base_Classes_2() {
	void print(const Bear &);
	void print(const Endangered &);

	Panda ying_yang("ying_yang", true); //ORIG Panda ying_yang("ying_yang");
	//TEST! print(ying_yang); //																														error: ambiguous
}

void Lookup_Based_on_Type_of_Pointer_or_Reference() {
	cout << R"(Bear *pb = new Panda("ying_yang"):)" << "\n\n";
	Bear *pb = new Panda("ying_yang");
	pb->print(); // ok: Panda::print()
	//TEST!! pb->cuddle(); //																															error: not part of the Bear interface
	//TEST!! pb->highlight(); //																															error: not part of the Bear interface
	cout << '\n'; //MINE
	delete pb; // ok: Panda::~Panda()

	cout << "\n\n" << R"(Endangered *pe = new Panda("ying_yang"):)" << "\n\n";
	Endangered *pe = new Panda("ying_yang");
	pe->print(); // ok: Panda::print()
	//TEST! pe->toes(); //																																error: not part of the Endangered interface
	//TEST pe->cuddle(); //																																error: not part of the Endangered interface
	cout << '\n'; //MINE
	pe->highlight(); //TEST!! //																															ok: Panda::highlight()
	cout << '\n'; //MINE
	delete pe; // ok: Panda::~Panda()

#ifdef MINE
	e->print();
	unique_ptr<Endangered> e = make_unique<Panda>("ying_yang");
#endif
}

void mine() {
	Endangered en(Endangered::critical);
	en.print();
}

int main() {
	print_file_line();

	Lookup_Based_on_Type_of_Pointer_or_Reference();
	//mine();

	return 0;
}
#endif

#ifdef EX_18_23

#include "../../stdafx.h"
#include "18_03_1_2.h"
using namespace std;

struct D : X, C { 
	D() { cout << "D\n"; }
};

int main() {
	print_file_line();

	D *pd = new D;
	X *px = pd; // (a)
	A *pa = pd; // (b)
	B *pb = pd; // (c)
	C *pc = pd; // (d)
	delete pd;

	return 0;
}
#endif

#ifdef EX_18_24

#include <iostream>
#include "../../stdafx.h"
#include "18_03_2.h"
using namespace std;

int main() {
	print_file_line();

	ZooAnimal *pz = new Panda("ying_yang");
	pz->print();
	//ERR pz->cuddle(); 
	//ERR pz->highlight();
	cout << '\n';
	delete pz;

	return 0;
}
#endif

#ifdef EX_18_25

#include <iostream>
#include "../../stdafx.h"
using namespace std;

struct Base1 {
	virtual void print() { cout << "Base1::virtual void print()\n"; }
	virtual ~Base1() { cout << "Base1::~Base1()\n"; }
};

struct Base2 {
	virtual void print() { cout << "Base2::virtual void print()\n"; }
	virtual ~Base2() { cout << "Base2::~Base2()\n"; }
};

struct D1 : Base1 { 
	void print() override { cout << "D1::void print() override\n"; }
};

struct D2 : Base2 {
	void print() override { cout << "D2::void print() override\n"; }
};
struct MI : D1, D2 {
	void print() final { 
		cout << "void MI::print() final\n";
		D1::print();
		D2::print();
	}
};

int main() {
	print_file_line();

	Base1 *pb1 = new MI;
	Base2 *pb2 = new MI;
	D1 *pd1 = new MI;
	D2 *pd2 = new MI;

	cout << "(a):\n";
	pb1->print(); // (a)  //TEST!
	cout << "\n(b):\n";
	pd1->print(); // (b)  //TEST!
	cout << "\n(c):\n";
	pd2->print(); //(c)
	cout << "\n(d):\n";
	delete pb2; //(d) 
	cout << "\n(e):\n";
	delete pd1; //(e) 
	cout << "\n(f):\n";
	delete pd2; //(f) 

	return 0;
}
#endif
