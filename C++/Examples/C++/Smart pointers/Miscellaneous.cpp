#include "stdafx.h"
#include <iostream>
#include <map>
#include <memory>
using namespace std;

#define counterFunction() { cout << __COUNTER__ << " " << __FUNCTION__ << " " << __LINE__ << '\t'; }
#define counterFunctionEndl() { counterFunction(); cout << endl; }

constexpr int mintCounter = 1000;

class object_ {
	int intArray[10000000];
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

typedef map <int, object_*> map_t;
typedef map <int, shared_ptr<object_>> mapSmartPtr;

class objects {
	map_t cobjObjects;
public:
	void insert(int intOperation) { 
		object_* objObject = new object_(intOperation); 
		cobjObjects.insert(map_t::value_type(intOperation, objObject));
	}
	
	void erase(int intOperation) { 
		auto ptrObjects = cobjObjects.find(intOperation);
		object_* objObject = ptrObjects->second;
		cobjObjects.erase(intOperation);
		delete objObject;
		objObject = nullptr;
}	};

class objectsSmartPtr {
	mapSmartPtr cobjObjects;
public:
	void insert(int intOperation) { 
		shared_ptr<object_> objObject(new object_(intOperation));
		cobjObjects.insert(mapSmartPtr::value_type(intOperation, objObject));
	}
	
	void erase(int intOperation) { cobjObjects.erase(intOperation); }
	void clear() { cobjObjects.clear(); }
};

void insertMemoryLeak(int intOperation) { //Memory leak.
	objects objObjects;
	objObjects.insert(intOperation);
	//Memory leak due to missing: objObjects.erase(intOperation);
}

void insertSmartPtr(int intOperation) { //Add using a smart pointer.
	objectsSmartPtr objObjectsSmartPtr;
	objObjectsSmartPtr.insert(intOperation);
}

void insertClearSmartPtr() {
	objectsSmartPtr objObjectsSmartPtr;
	cout << "Inserting smart pointer objects in a loop and clearing the collection..." << endl; 
	for (size_t i = 0; i < mintCounter * 0.04; i++) objObjectsSmartPtr.insert(i);
	objObjectsSmartPtr.clear();
}

void insertEraseSmartPtr() {
	objectsSmartPtr objObjectsSmartPtr;
	cout << "Inserting and erasing smart pointer objects in a loop..." << endl; 
	for (size_t i = 0; i < mintCounter * 0.04; i++) {
		objObjectsSmartPtr.insert(i);
		objObjectsSmartPtr.erase(i);
}	}

void insertSmartPtrLoop() {
	objectsSmartPtr objObjectsSmartPtr;
	cout << "Inserting smart pointer objects in a loop..." << endl; 
	for (size_t i = 0; i < mintCounter * 0.04; i++) objObjectsSmartPtr.insert(i);
}

shared_ptr<object_> mptrObject;

void deleteSmartPtrUnique() {
	cout << "Creating and deleting a unique smart pointer object..." << endl << endl;
	mptrObject = make_shared<object_>(111);
	cout << "mptrObject.use_count() = " << mptrObject.use_count() << endl;
	cout << boolalpha; //std::boolalpha @ http://www.cplusplus.com/reference/ios/boolalpha/
	cout << "mptrObject.unique() = " << mptrObject.unique() << endl;
	object_* objObject = mptrObject.get();
	cout << "objObject->operation = " << objObject->operation << endl;
	
	mptrObject.reset();
	cout << endl << "After mptrObject.reset():" << endl;
	cout << "mptrObject.use_count() = " << mptrObject.use_count() << endl;
	cout << "mptrObject.unique() = " << mptrObject.unique() << endl;
	mptrObject = nullptr;
	cout << endl;
}

void deleteSmartPtrShared() {
	cout << "Creating and deleting a non-unique (truly shared) smart pointer object..." << endl << endl;
	mptrObject = make_shared<object_>(111);
	cout << "mptrObject.use_count() = " << mptrObject.use_count() << endl << endl;
	
	shared_ptr<object_> ptrObject = mptrObject;
	cout << "After ptrObject = mptrObject: mptrObject.use_count() = " << mptrObject.use_count() << endl;
	cout << "ptrObject.use_count() = " << ptrObject.use_count() << endl;
	cout << boolalpha; //std::boolalpha @ http://www.cplusplus.com/reference/ios/boolalpha/
	cout << "mptrObject.unique() = " << mptrObject.unique() << endl;
	cout << "ptrObject.unique() = " << ptrObject.unique() << endl;
	cout << "mptrObject.get()->operation = " << mptrObject.get()->operation << endl;
	
	mptrObject.reset();
	cout << endl << "After mptrObject.reset():" << endl;
	cout << "mptrObject.use_count() = " << mptrObject.use_count() << endl;
	cout << "mptrObject.get()->operation = " << mptrObject.get()->operation << endl;
	cout << "ptrObject.use_count() = " << ptrObject.use_count() << endl;
	cout << "ptrObject.get()->operation = " << ptrObject.get()->operation << endl;
	cout << "mptrObject.unique() = " << mptrObject.unique() << endl;
	cout << "ptrObject.unique() = " << ptrObject.unique() << endl;
	mptrObject = nullptr;
	ptrObject = nullptr;
	cout << endl;
}

void shared_ptrReset () { //std::shared_ptr::reset @ http://www.cplusplus.com/reference/memory/shared_ptr/reset/
  shared_ptr<int> sp; // empty

  sp.reset (new int); // takes ownership of pointer
  *sp=10;
  cout << *sp << '\n';

  sp.reset (new int); // deletes managed object, acquires new pointer
  *sp=20;
  cout << *sp << '\n';

  sp.reset(); // deletes managed object
}

void shared_ptrUnique() { //std::shared_ptr::unique @ http://www.cplusplus.com/reference/memory/shared_ptr/unique/
  shared_ptr<int> foo;
  shared_ptr<int> bar (new int);

  cout << "foo unique?\n" << boolalpha;

  cout << "1: " << foo.unique() << '\n';  // false (empty)

  foo = bar;
  cout << "2: " << foo.unique() << '\n';  // false (shared with bar)

  bar = nullptr;
  cout << "3: " << foo.unique() << '\n';  // true
}

void getAfterReset() {
	shared_ptr<object_> objObject(new object_(111));
	cout << objObject->operation << endl;
	cout << objObject.get() << endl;
	objObject.reset();
	cout << objObject.get() << endl;
}

void unique_ptrAssignment () { //std::unique_ptr::operator= @ http://www.cplusplus.com/reference/memory/unique_ptr/operator=/
  unique_ptr<int> foo;
  unique_ptr<int> bar;
  
  foo = unique_ptr<int>(new int (101));  // rvalue
  bar = move(foo);                       // using move
  
  cout << "foo: "; if (foo) cout << *foo << '\n'; else cout << "empty\n";
  cout << "bar: "; if (bar) cout << *bar << '\n'; else cout << "empty\n";
}

#define RESET
#define NULLPTR
void unique_ptrNull() {
	unique_ptr<object_> objObject;
	printf_s("Uninitialised objObject = %p\n", objObject);
	objObject = make_unique<object_>(111);
	printf_s("After make_unique: objObject = %p\n", objObject);
	printf_s("objObject.get() = %p\n", objObject.get());
	#ifdef RESET
		objObject.reset();
		printf_s("After objObject.reset(): objObject = %p\n", objObject);
	#elif defined (NULLPTR)
		objObject = nullptr;
		printf_s("After objObject = nullptr: objObject = %p\n", objObject);
	#endif
}

void deleteConst(const object_* const objObject) { //ERROR: The stored object is deleted despite it is being accessed through a const object.
	try { 
		//Compile-time error: objObject->operation = 111; //Error	C3490	'operation' cannot be modified because it is being accessed through a const object.
		//counterFunction();
		cout << "Before delete objObject..." << endl;
		delete objObject; 
	} 
	catch (const std::exception& objException ) { cout << objException.what(); }
} 

void deleteConst() {
	try { 
		unique_ptr<object_> ptrObject = make_unique<object_>(0);
		deleteConst(ptrObject.get());
	}
	catch(const exception& objException) {	cout << typeid(objException).name() << '\t' << objException.what() << endl; }
}

weak_ptr<int> gw; //Demonstrates how lock is used to ensure validity of the pointer. //std::weak_ptr @ http://en.cppreference.com/w/cpp/memory/weak_ptr
 
void f() { 
	cout << "use_count == " << gw.use_count() << ": ";
	if (auto spt = gw.lock()) cout << *spt << "\n"; // Has to be copied into a shared_ptr before usage
	else cout << "gw is expired\n";
}
 
void weak_ptrExample() {
	{
		auto sp = make_shared<int>(42);
		gw = sp;
		f();
	}
	f();
}

int main() {
	try { 
		//cout << "Inserting objects..." << endl; for (int i = 0; i < mintCounter * 0.05; i++) insertMemoryLeak(i);
		//cout << "Inserting smart pointer objects..." << endl; for (int i = 0; i < mintCounter * 0.05; i++) insertSmartPtr(i);
		//insertClearSmartPtr();
		//insertEraseSmartPtr();
		//for (int i = 0; i < 5; i++) insertSmartPtrLoop();
		//deleteSmartPtrUnique();
		//shared_ptrReset();
		//shared_ptrUnique();
		//getAfterReset();
		//unique_ptrAssignment();
		//unique_ptrNull();
		//deleteConst(make_unique<object_>(0).get()); //ERROR: The stored object is deleted despite it is being accessed through a const object.
		//deleteConst();
		weak_ptrExample();
		return 0;
	}
	catch(const exception& objException) {	cout << typeid(objException).name() << '\t' << objException.what() << endl; }
}

