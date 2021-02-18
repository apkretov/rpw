#include "stdafx.h"
#include <iostream>
#include <map>
#include <memory>
#include <string>
using namespace std;

#define counterFunction() { cout << __COUNTER__ << " " << __FUNCTION__ << " " << __LINE__ << '\t'; }
#define counterFunctionEndl() { counterFunction(); cout << endl; }

class object_ {
	void displayOperation() { cout << "operation = " << operation << endl; }
public:
	object_(int intOperation) : operation(intOperation) { 
		//OFF counterFunction();  
		//OFF displayOperation();
	}
	~object_() { 
		counterFunction(); 
		displayOperation();
	};
	int operation;
	bool isPending() { return operation % 2 == 0; };
};

typedef map<int, shared_ptr<object_>> mapObj_t;

void display(const mapObj_t& objObjects) { //IMPORTANT: & (not to increment shared_ptr use_count)!!!
	for (auto& sttObject : objObjects) //IMPORTANT: & (not to increment shared_ptr use_count)!!!
		cout << "operation: " << sttObject.second->operation << '\t' << "use_count: " << sttObject.second.use_count() << '\n'; 
	cout << endl;
};

void eraseERROR() {    
	mapObj_t objObjects;
	for (int i = 2; i < 6; i++) {
		objObjects.insert( mapObj_t::value_type(i, make_shared<object_>(i)) ); 
		cout << "operation: " << objObjects.at(i)->operation << '\t' << "use_count: " << objObjects.at(i).use_count() << endl;
	}
	cout << endl;
	for (auto ptrObject = objObjects.begin(); ptrObject != objObjects.end();/*IMPORTANT: empty*/) {
		cout << "operation: " << ptrObject->second->operation << '\t' << "use_count: " << ptrObject->second.use_count() << endl;
		if (ptrObject->second->isPending()) 
			objObjects.erase(ptrObject);
		else 
			++ptrObject;
	}
	cout << endl;
	display(objObjects);
	cout << endl;
}

void eraseExample() { //std::map::erase @ http://en.cppreference.com/w/cpp/container/map/erase
    map<int, string> c = {{1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}, {6, "six"}};
    cout << "size: " << c.size() << endl;
	 for (auto it = c.begin(); it != c.end();) // erase all odd numbers from c
        if (it->first % 2 == 1) 
			  it = c.erase(it);
        else 
			  ++it; 
   cout << "size: " << c.size() << endl;
	 for (auto& p : c) 
		cout << p.second << ' ';
	cout << endl;
}

int main() {
	//eraseERROR();
	eraseExample();
	return 0;
}