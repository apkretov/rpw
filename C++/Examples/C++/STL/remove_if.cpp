#include "stdafx.h" 
#include <algorithm>
#include <string>
#include <iostream>
#include <cctype>
#include <map>
#include <memory>
#include <algorithm>
#include <vector>
#include <iterator>
#include <numeric>
using namespace std;

void remove_ifExample1() { //std::remove, std::remove_if @ http://en.cppreference.com/w/cpp/algorithm/remove
    string str1 = "Text with some   spaces";
    str1.erase( //A call to remove is typically followed by a call to a container's erase method, which erases the unspecified values and reduces the physical size of the container to match its new logical size. @ http://en.cppreference.com/w/cpp/algorithm/remove
		 remove(str1.begin(), str1.end(), ' '), str1.end()
	 );
    cout << str1 << '\n';
 
    string str2 = "Text\n with\tsome \t  whitespaces\n\n";
    str2.erase(remove_if(str2.begin(), str2.end(), [](char x){return isspace(x);}), str2.end());
    cout << str2 << '\n';
}

bool greater6 (int value) { return value > 6; }  //remove_if @ https://msdn.microsoft.com/en-us/library/mt771443.aspx#remove_if
  
void remove_ifExample2() {  
   using namespace std;  
   vector<int> v1, v2;  
   vector<int>::iterator Iter, new_end;  
  
   for (int i = 0; i <= 9; i++) v1.push_back(i);  
   for (int ii = 0; ii <= 3; ii++)  v1.push_back(7);  
	random_shuffle (v1.begin(), v1.end());  
   cout << "Vector v1 is ( "; for (Iter = v1.begin(); Iter != v1.end(); Iter++) cout << *Iter << " ";  cout << ")." << endl;  
  
   new_end = remove_if (v1.begin(), v1.end(), greater6); // Remove elements satisfying predicate greater6  
   cout << "Vector v1 with elements satisfying greater6 removed is\n ( "; for (Iter = v1.begin(); Iter != v1.end(); Iter++) cout << *Iter << " ";  cout << ")." << endl;
  
   v1.erase(new_end, v1.end()); // To change the sequence size, use erase
   cout << "Vector v1 resized elements satisfying greater6 removed is\n ( "; for (Iter = v1.begin(); Iter != v1.end(); Iter++) cout << *Iter << " "; cout << ")." << endl;
}  

#define counterFunction() { cout << __COUNTER__ << " " << __FUNCTION__ << " " << __LINE__ << '\t'; }
#define counterFunctionEndl() { counterFunction(); cout << endl; }

class object_ {
	void displayOperation() { cout << "operation = " << operation << endl; }
public:
	object_(int intOperation) : operation(intOperation) { 
		counterFunction();  
		displayOperation();
	}
	~object_() { 
		counterFunction(); 
		displayOperation();
	};
	int operation;
	bool isPending() { return operation % 2 == 0; };
};

typedef shared_ptr<object_> spObj_t;
typedef vector<spObj_t> vecObj_t;

auto displayObjectsVector(const vecObj_t& objObjects) {
	for_each( objObjects.cbegin(), objObjects.cend(), [] (const auto& ptrObject) { cout << ptrObject->operation << " "; } );
	cout << endl;
};

void remove_ifVector() {
	vecObj_t objObjects;
	for (int i = 0; i < 3; i++) objObjects.push_back(make_shared<object_>(i));
	cout << endl << "objObjects before remove_if:" << endl;
	displayObjectsVector(objObjects);
	cout << endl << "Removing operation == 0:" << endl;
	auto ptrObjectsNewEnd = remove_if(objObjects.begin(), objObjects.end(), [](const spObj_t& objObject){ return objObject->operation == 0; });
	cout << endl << "After remove_if: size = " << objObjects.size() << endl;
	objObjects.erase(ptrObjectsNewEnd, objObjects.end());
	cout << endl << "After erase:" << endl << "size = " << objObjects.size() << "\n" << "objObjects:" << endl;
	displayObjectsVector(objObjects);
	cout << endl;
}

typedef map<int, shared_ptr<object_>> mapObj_t;
typedef mapObj_t::value_type mapObj_tVT;

auto displayObjectsMap(const mapObj_t& objObjects) {
	for(auto ptrObjects = objObjects.cbegin(); ptrObjects != objObjects.cend(); ptrObjects++) cout << ptrObjects->second->operation << " ";
	cout << endl;
};

void remove_ifMap() {
	mapObj_t objObjects;
	for (int i = 0; i < 3; i++) objObjects.insert( mapObj_tVT(i, make_shared<object_>(i)) );
	cout << endl << "objObjects:" << endl;
	displayObjectsMap(objObjects);
	//EEROR! It doesn't work for map perhaps because the later is an associative contaner. //RIGHT! These algorithms cannot be used with associative containers such as std::set and std::map because ForwardIt does not dereference to a MoveAssignable type (the keys in these containers are not modifiable) //std::remove, std::remove_if @ http://en.cppreference.com/w/cpp/algorithm/remove
	//auto ptrObjectsNewEnd = remove_if(objObjects.begin(), objObjects.end(), [](mapObj_tVT ptrObject){ return ptrObject.second->operation == 0; });
}

void generate_nExample() {
    const size_t N = 5;
    int ar[N];
    generate_n(ar, N, rand); // Using the C function rand()
 
    cout << "ar: ";
    copy(ar, ar+N, ostream_iterator<int>(cout, " "));
    cout << "\n";
}

void newEnd() {
	cout << "Watch ptrEnd and ptrNewEnd in the debug mode. cout and printf don't display them exactly." << "\n\n";
	vector<int> vecInt(10);
	iota(vecInt.begin(), vecInt.end(), 0);
	copy(vecInt.cbegin(), vecInt.cend(), ostream_iterator<int>(cout, " ")); cout << endl;
	auto ptrEnd = vecInt.end();
	auto ptrNewEnd = remove_if(vecInt.begin(), vecInt.end(), [](int intNum){return intNum == 9;});
	cout << endl;
}

int main() {
	//remove_ifExample1();
	//remove_ifExample2();
	//remove_ifVector();
	//remove_ifMap();
	//generate_nExample();
	newEnd();
	return 0;
}