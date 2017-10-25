#include "stdafx.h"
#include <iostream>
#include <map>
#include <memory>
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
		//OFF counterFunction(); 
		//OFF displayOperation();
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

int main() {    
	cout << "IMPORTANT: & (not to increment shared_ptr use_count)!!!" << "\n\n";
	mapObj_t objObjects;
	for (int i = 2; i < 6; i++) {
		objObjects.insert( mapObj_t::value_type(i, make_shared<object_>(i)) );
		cout << "operation: " << objObjects.at(i)->operation << '\t' << "use_count: " << objObjects.at(i).use_count() << endl;
	}
	cout << endl;
	display(objObjects);
	return 0;
}
