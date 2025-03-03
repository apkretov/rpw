#ifdef ON

#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;

int i{100}, j{3};
double d{1.1};

void Explicit_Conversions() {
	//TEST! double slope = i / j; cout << slope << '\n';
}

void Named_Casts() {
	double slope = static_cast<double>(j) / i; // cast used to force floating-point division

	//TEST void *p = &d; //																																										ok: address of any nonconst object can be stored in a void*
	//TEST double *dp = static_cast<double*>(p); //																																				ok: converts void* back to the original pointer type

	char c{'a'};
	const char *pc{&c};
	//TEST! char *p = const_cast<char *>(pc); *p = 'b'; cout << c << '\n'; //																																	ok: but writing through p is undefined

	//ORIG const char *cp;
	const char *cp{&c}; //MINE
	//TEST! char *q = static_cast<char *>(cp); //																																				error: static_cast can’t cast away const
	//TEST! const char *p = static_cast<const char *>(cp); //MINE
	//TEST! string s = static_cast<string>(cp); //																																			ok: converts string literal to string
	//TEST! string s = const_cast<string>(cp); //																																				error: const_cast only changes constness

	{
		//ORIG int *ip;
		int *ip{&i}; //MINE
		char *pc = reinterpret_cast<char *>(ip); //TEST!! 
		string str(pc);//TEST! 
		cout << "str: " << str << '\n';
	}
}

void mine1() {
	int i{static_cast<int>(d)}; cout << i << '\n';
}

void mine2() {
	void *p{&d};
	//TEST cout << *static_cast<double *>(p) << '\n';
}

void mine3() {
	char c{'a'};
	const char *cp{&c};
	char *p = {const_cast<char *>(cp)};

	cout << *p << '\n';
	//TEST *p = 'b'; cout << *p << '\n';
}

void mine4() { // reinterpret_cast in C++ | Type Casting operators - GeeksforGeeks @ https://www.geeksforgeeks.org/reinterpret_cast-in-c-type-casting-operators/?ref=leftbar-rightbar
	int *p = new int(65); // CPP program to demonstrate working of reinterpret_cast
	char *ch = reinterpret_cast<char *>(p);
	cout << *p << endl;
	cout << *ch << endl;
	cout << p << endl;
	cout << ch << endl << endl;
}

// reinterpret_cast in C++ | Type Casting operators - GeeksforGeeks @ https://www.geeksforgeeks.org/reinterpret_cast-in-c-type-casting-operators/?ref=leftbar-rightbar
void mine5() { // CPP code to illustrate using structure
    struct mystruct { // creating structure mystruct
        int x;
        int y;
        char c;
        bool b;
    };
    mystruct s; // Assigning values
    s.x = 5;
    s.y = 10;
    s.c = 'a';
    s.b = true;

    // data type must be same during casting as that of original
    int *p = reinterpret_cast<int *>(&s); // converting the pointer of's'to, pointer of int type in'p'.    
	
	cout << sizeof(s) << endl;
	cout << sizeof s.x << ' ' << sizeof s.y << ' ' << sizeof s.c << ' ' << sizeof s.b << "\n\n"; //MINE

    cout << *p << endl; // printing the value currently pointed by *p

    p++; // incrementing the pointer by 1
    cout << *p << endl; // printing the next integer value

    p++;
    char *ch = reinterpret_cast<char *>(p); // we are casting back char * pointed by p using char *ch.
    cout << *ch << endl; // printing the character value pointed by (*ch)

    ch++;
    bool *n = reinterpret_cast<bool *>(ch); /* since, (*ch) now points to boolean value, so it is required to access the value using same type conversion.so, we have used data type of *n to be bool. */
    cout << *n << endl;
    cout << *(reinterpret_cast<bool *>(ch)) << endl; // we can also use this line of code to print the value pointed by (*ch).
}

void Old_Style_Casts() {
	int i{100}, *ip{&i};
	//TEST! char *pc = (char *)ip; //																																								ip is a pointer to int
	//MINE cout << *ip << ' ' << *pc << '\n';
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//Explicit_Conversions();
	//mine1();
	Named_Casts();
	//mine2();
	//mine3();
	//mine4();
    //mine5();
	//Old_Style_Casts();

	return 0;
}
#endif

#ifdef EX_04_36

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	int i{10};
	double d{2};

	i *= static_cast<int>(d);
	cout << i << '\n';
	
	return 0;
}
#endif

#ifdef EX_04_37

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	int i; 
	double d; 
	const string *ps;
	char *pc; 
	void *pv;

	//TEST! pv = static_cast<void *>(const_cast<string *>(ps)); // (a) pv = (void *)ps;
	//TEST i = static_cast<int>(*pc); // (b) i = int(*pc); 
	//TEST pv = static_cast<void *>(&d); // (c) pv = &d; 
	//TEST pc = static_cast<char *>(pv); // (d) pc = (char *)pv; 

	return 0;
}
#endif