#ifdef ON
#include <iostream>
using namespace std;
#include "07_02_1.h"

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

#ifdef Class_Types
	//OFF Sales_data item1; // default-initialized object of type Sales_data
	class Sales_data item1; //TEST! // equivalent declaration
#elif !Class_Declarations
	class Screen__Overloading_Based_on_const; //TEST! // declaration of the	Screen class

	class link_Screen {
		//TEST! Screen window;
		link_Screen *prev;
		link_Screen *next;
	};

#endif
	return 0;
}
#endif

#ifdef EX_07_31
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

#ifndef MINE
	struct X; // Forward declarations.
	struct Y;
	
	struct X { // The definitions.
		Y *y{};
	};

	struct Y {
		X x{};
	};

	X x;
	Y y;

	x.y = &y;
	y.x = x;

#elif !CHATGPT
	class Y; // forward declaration

	class X {
	private:
		Y *y_ptr;
	public:
		X() : y_ptr(nullptr) {}
		void set_y(Y *y) { y_ptr = y; }
	};

	class Y {
	private:
		X x_obj;
	public:
		Y() {}
		X &get_x() { return x_obj; }
	};

	X x;
	Y y;
	x = y.get_x();
	x.set_y(&y);

#endif
	
	return 0;
}
#endif
