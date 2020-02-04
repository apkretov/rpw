#include "stdafx.h"
#include <iostream>
#include <map>
#include <algorithm>
#include <iterator>
#include <memory>
#include <string>
#include <vector>  
#include <numeric>
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

void display(const mapObj_t& objObjects) { 
	for (auto& sttObject : objObjects) 
		cout << "operation: " << sttObject.second->operation << '\t' << "use_count: " << sttObject.second.use_count() << endl; 
	cout << endl;
};

void copyMapObjectERROR() { //The copy algorithm doesn't work for an associative map container.
	mapObj_t objObjects;
	for (int i = 2; i < 6; i++) {
		objObjects.insert( mapObj_t::value_type(i, make_shared<object_>(i)) ); 
		cout << "operation: " << objObjects.at(i)->operation << '\t' << "use_count: " << objObjects.at(i).use_count() << endl;
	}
	cout << endl;
	mapObj_t objObjectsCopy;
	//ERROR copy(objObjects.cbegin(), objObjects.cend(), back_inserter(objObjectsCopy));
}

void copyMapERROR() { //The copy algorithm doesn't work for an associative map container.
	map<int, double> mapIntDouble;
	for (int i = 2; i < 6; i++) mapIntDouble.insert( pair<int, double>(i, i + 0.5) ); 
	map<int, double> mapIntDoubleCopy;
	//ERROR copy(mapIntDouble.cbegin(), mapIntDouble.cend(), back_inserter(mapIntDoubleCopy));
}

void copyVector1() { //<algorithm> functions //copy // @ https://msdn.microsoft.com/en-us/library/mt771443.aspx#copy 
   using namespace std;  
   vector <int> v1, v2;  
   vector <int>::iterator Iter1, Iter2;  
  
   int i;  
   for ( i = 0 ; i <= 5 ; i++ ) v1.push_back( 10 * i );  
  
   int ii;  
   for ( ii = 0 ; ii <= 10 ; ii++ ) v2.push_back( 3 * ii );  
  
   cout << "v1 = ( " ;  
   for ( Iter1 = v1.begin( ) ; Iter1 != v1.end( ) ; Iter1++ )  cout << *Iter1 << " ";  
   cout << ")" << endl;  
  
   cout << "v2 = ( " ;  
   for ( Iter2 = v2.begin( ) ; Iter2 != v2.end( ) ; Iter2++ )  cout << *Iter2 << " ";  
   cout << ")" << endl;  
  
   copy( v1.begin( ), v1.begin( ) + 3, v2.begin( ) + 4 ); // To copy the first 3 elements of v1 into the middle of v2  
  
   cout << "v2 with v1 insert = ( " ;  
   for ( Iter2 = v2.begin( ) ; Iter2 != v2.end( ) ; Iter2++ )  cout << *Iter2 << " ";  
   cout << ")" << endl;  
  
   copy( v2.begin( )+4, v2.begin( ) + 7, v2.begin( ) + 2 );  // To shift the elements inserted into v2 two positions  to the left  
  
   cout << "v2 with shifted insert = ( " ;  
   for ( Iter2 = v2.begin( ) ; Iter2 != v2.end( ) ; Iter2++ )  cout << *Iter2 << " ";  
   cout << ")" << endl;  
}  

auto copyVector2() { //std::copy, std::copy_if @ http://en.cppreference.com/w/cpp/algorithm/copy
    std::vector<int> from_vector(10);
    std::iota(from_vector.begin(), from_vector.end(), 0);
 
    std::vector<int> to_vector;
    std::copy(from_vector.begin(), from_vector.end(), std::back_inserter(to_vector));
// or, alternatively,
//  std::vector<int> to_vector(from_vector.size());
//  std::copy(from_vector.begin(), from_vector.end(), to_vector.begin());
// either way is equivalent to
//  std::vector<int> to_vector = from_vector;
 
    std::cout << "to_vector contains: ";
    std::copy(to_vector.begin(), to_vector.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
}

int main() {
	//copyMapObjectERROR();
	//copyMapERROR();
	//copyVector1();
	copyVector2();
}