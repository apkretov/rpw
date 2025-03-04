#include "stdafx.h" //reinterpret_cast conversion @ http://en.cppreference.com/w/cpp/language/reinterpret_cast
#include <cstdint>
#include <cassert>
#include <iostream>
using namespace std;

int f() { return 42; }

int main() {
    int i = 7;
 
    uintptr_t v1 = reinterpret_cast<uintptr_t>(&i); // pointer to integer and back // static_cast is an error
    cout << "The value of &i is 0x" << hex << v1 << '\n';
    int* p1 = reinterpret_cast<int*>(v1);
    assert(p1 == &i);
	 cout << *p1 << "\n\n"; //TEST
 
    void(*fp1)() = reinterpret_cast<void(*)()>(f); // pointer to function to another and back
    // fp1(); undefined behavior
    int(*fp2)() = reinterpret_cast<int(*)()>(fp1);
    cout << dec << fp2() << "\n\n"; // safe
 
    char* p2 = reinterpret_cast<char*>(&i); // type aliasing through pointer
    if(p2[0] == '\x7') cout << "This system is little-endian" << "\n\n";
    else cout << "This system is big-endian" << "\n\n";
 
    reinterpret_cast<unsigned int&>(i) = 42; // type aliasing through reference
    cout << i << "\n\n";
 
    const int& const_iref = i;
    //int &iref = reinterpret_cast<int&>(const_iref); //compiler error - can't get rid of const
    /*Must use const_cast instead:*/ int &iref = const_cast<int&>(const_iref);
	 cout << iref << "\n\n"; //TEST
}