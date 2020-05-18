#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

//Another way to declare a collection is to derive a collection from an STL collection as in the following: //Declaring collections @ https://www.codeproject.com/Articles/563/An-Introductory-STL-tutorial
class myVector : public vector<int> {};

template <typename T>
void displayVector(const vector<T>& objVector) {
	for (vector<T>::const_iterator i = objVector.begin(); i < objVector.end(); i++) cout << *i << " ";
	cout << endl;
	for (vector<T>::const_reverse_iterator i = objVector.rbegin(); i < objVector.rend(); i++) cout << *i << " ";
	cout << endl;
}

void iterators() { //Iterators @ https://www.codeproject.com/Articles/563/An-Introductory-STL-tutorial
	vector<int> myVec;
	vector<int>::iterator first, last;
	for (long i = 0; i < 10; i++) myVec.push_back(i);
	displayVector(myVec);
	first = myVec.begin();
	last = myVec.begin() + 5;
	if (last >= myVec.end()) return;
	myVec.erase(first, last);
}

int main() {
	iterators();
	return 0;
}
