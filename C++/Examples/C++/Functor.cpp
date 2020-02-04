#include "stdafx.h" 
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
 
struct Sum { //std::for_each @ http://en.cppreference.com/w/cpp/algorithm/for_each
    Sum() : sum{0} { }
    int sum;
    void operator()(int n) { sum += n; } //an overloaded operator() in a functor to compute their sum
};
 
void sumFunctor() {
	vector<int> nums{ 3, 4, 2, 8, 15, 267 };
	Sum s = for_each(nums.begin(), nums.end(), Sum()); // calls Sum::operator() for each number
	cout << "sum: " << s.sum << '\n';
}

struct add_x { // this is a functor //C++ Functors - and their uses @ http://stackoverflow.com/questions/356950/c-functors-and-their-uses
  add_x(int x) : x(x) {}
  int operator()(int y) const { return x + y; }
private:
  int x;
};

void addFunctor() { // Now you can use it like this:
	add_x add42(42); // create an instance of the functor class
	int i = add42(8); // and "call" it
	cout << "i: " << i << endl; // and it added 42 to its argument
}

int main() {
	sumFunctor();
	addFunctor();
}
