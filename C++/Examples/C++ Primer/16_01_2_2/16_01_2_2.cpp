#include <iostream>
#include <utility>
#include "../../stdafx.h"
#include "16_01_2_2_1.h"
#include "16_01_2_2_2.h"
using namespace std;

void One_to_One_Friendship() {
	Blob<char> ca; // BlobPtr<char> and operator==<char> are friends
	Blob<int> ia; // BlobPtr<int> and operator==<int> are friends
}

void mine1() {
	Blob<char> ca1{'a','b','c'};
	Blob<char> ca2{'a','b','c'};
	Blob<char> ca3{'a','b','d'}; // 3rd element is different

    cout << "(ca1 == ca2) = " << boolalpha << (ca1 == ca2) << '\n'; // true
	cout << "(ca1 == ca3) = " << boolalpha << (ca1 == ca3) << '\n'; // false
}

#ifndef General_and_Specific_Template_Friendship
template <typename T> class Pal; // forward declaration necessary to befriend a specific instantiation of a template

class C { //TEST! //																																						C is an ordinary, nontemplate class
	friend class Pal<C>; //TEST! //																																		Pal instantiated with class C is a friend to C
	template <typename T> friend class Pal2; //TEST! //																														all instances of Pal2 are friends to C; // no forward declaration required when we befriend all instantiations
};

template <typename T> class C2 { // C2 is itself a class template
	friend class Pal<T>; // each instantiation of C2 has the same instance of Pal as a friend // a template declaration for Pal must be in scope
	template <typename X> friend class Pal2; //TEST! //																														all instances of Pal2 are friends of each instance of C2, prior declaration needed
	friend class Pal3; //TEST! //																																			Pal3 is a nontemplate class that is a friend of every instance of C2 // prior declaration for Pal3 not needed
};
#endif

#ifndef Befriending_the_Template_s_Own_Type_Parameter // Befriending the Template�s Own Type Parameter
template <typename Type> class Bar {
	friend Type; //TEST! //																																				grants access to the type used to instantiate Bar
	// ...
};
#endif

#ifndef Template_Type_Aliases
void Template_Type_Aliases_() {
#ifdef ORIG
	typedef Blob<string> StrBlob; //TEST!
#else //MINE
	using StrBlob = Blob<string>; //TEST!
	StrBlob b({"one", "two", "three"}); 
	cout << "b.back() = " << b.back() << '\n';
#endif
}

#ifdef OFF
template <typename T> using twin = pair<T, T>; //TEST!
twin<string> authors; // authors is a pair<string, string>
twin<int> win_loss; // win_loss is a pair<int, int>
twin<double> area; // area is a pair<double, double>

//MINE
struct Vehicle {};
struct Student {};

template <typename T> using partNo = pair<T, unsigned>; //TEST!
partNo<string> books; // books is a pair<string, unsigned>
partNo<Vehicle> cars; // cars is a pair<Vehicle, unsigned>
partNo<Student> kids; // kids is a pair<Student, unsigned>
#endif
#endif

template <typename T> using Blob_t = Blob<T>; //TEST! //MINE

void mine2() {
	Blob_t<string> b1({"one", "two", "three"}); //TEST!
	using StrBlob = Blob_t<string>; //TEST!
	StrBlob b2({"one", "two", "three"});
	cout << "b1.back() = " << b1.back() << "\tb2.back() = " << b2.back() << '\n';
}

#ifdef static_Members_of_Class_Templates
template <typename T> class Foo {
public:
	static size_t count() { //TEST!
		return ctr; 
	}
	// other interface members
private:
	static size_t ctr;
	// other implementation members
};

Foo<string> fs; // instantiates static members Foo<string>::ctr and Foo<string>::count
Foo<int> fi, fi2, fi3; // all three objects share the same Foo<int>::ctr and Foo<int>::count members

template <typename T> size_t Foo<T>::ctr = 0; //TEST! //																														define and initialize ctr

void static_Members_of_Class_Templates_() {
	Foo<int> fi; // instantiates Foo<int> class // and the static data member ctr
	auto ct = Foo<int>::count(); //TEST! //																																	instantiates Foo<int>::count
	ct = fi.count(); // uses Foo<int>::count
	//TEST! ct = Foo::count(); //																																				error: which template instantiation?
}
#endif

int main(int argc, char* argv[]) {
    print_file_line();
 
#ifdef OFF
	One_to_One_Friendship();
	mine1();
	Template_Type_Aliases_();
#endif
	mine2();

	return 0;
}