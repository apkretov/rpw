#if 0

#include "../../stdafx.h"
#include <memory>
//OFF #include "vld.h" 
using namespace std;

struct A { /* ... */ };

#ifdef _1
int main() {
	PRINT_FILE_LINE();

	A *ptr = new A; //TEST!
}
#endif //_1

#ifdef _2
int main() {
	PRINT_FILE_LINE();

	A *ptr = new A;
	unique_ptr<A> up1(ptr);
	unique_ptr<A> up2(ptr); //TEST
}
#endif //_2

#ifdef _3
int main() {
	PRINT_FILE_LINE();

	A *ptr = new A;
	shared_ptr<A> sp1(ptr);
	shared_ptr<A> sp2(ptr); //TEST!!
}
#endif //_3

#ifdef _4
A *MakeA() { //TEST!
	return new A;
}

int main() {
	PRINT_FILE_LINE();

	unique_ptr<A> up(MakeA());
	shared_ptr<A> sp(MakeA());
	MakeA(); //TEST
}
#endif //_4

#ifdef _5
unique_ptr<A> MakeA() { //TEST
	return make_unique<A>();
}

int main() {
	PRINT_FILE_LINE();

	unique_ptr<A> up = MakeA(); //TEST!
	unique_ptr<A> up2(MakeA()); //TEST! //MINE
	shared_ptr<A> sp = MakeA(); //TEST!
}
#endif //_5

#ifndef _6
int main() {
	PRINT_FILE_LINE();

	auto up1 = make_unique<A>();
	unique_ptr<A> up2(up1.get()); //TEST
}
#endif //_6
#endif //1