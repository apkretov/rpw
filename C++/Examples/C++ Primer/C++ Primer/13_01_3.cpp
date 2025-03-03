#ifdef ON

#include <string>
#include <memory>
#include <vector>
using namespace std;
#include "07_05_4.h"

void When_a_Destructor_Is_Called() {
	{ // new scope
		// p and p2 point to dynamically allocated objects
		Sales_data *p = new Sales_data; // p is a built-in pointer
		auto p2 = make_shared<Sales_data>(); // p2 is a shared_ptr
		Sales_data item(*p); // copy constructor copies *p into item
		vector<Sales_data> vec; // local object
		vec.push_back(*p2); // copies the object to which p2 points
		delete p; // destructor called on the object pointed to by p
	} // exit local scope; destructor called on item, p2, and vec
	// destroying p2 decrements its use count; if the count goes to 0, the object is freed
	// destroying vec destroys the elements in vec
}
#endif