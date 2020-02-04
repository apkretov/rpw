#include "stdafx.h" //The following example uses a lambda function to increment all of the elements of a vector and then uses an overloaded operator() in a functor to compute their sum: //std::for_each @ http://en.cppreference.com/w/cpp/algorithm/for_each . Also see std::for_each @ http://www.cplusplus.com/reference/algorithm/for_each/
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
 
struct Sum {
    Sum() : sum{0} { }
    void operator()(int n) { sum += n; } //an overloaded operator() in a functor to compute their sum
    int sum;
};
 
int main() {
    vector<int> nums{ 3, 4, 2, 8, 15, 267 };
    auto print = [](const int& n) { cout << " " << n; };
 
    cout << "before:";
    for_each(nums.begin(), nums.end(), print);
    cout << '\n';

    for_each(nums.begin(), nums.end(), [](int &n){ n++; }); //a lambda function to increment all of the elements of a vector
	 Sum s = for_each(nums.begin(), nums.end(), Sum()); // calls Sum::operator() for each number
 
    cout << "after: ";
    for_each(nums.begin(), nums.end(), print);
    cout << '\n';
    cout << "sum: " << s.sum << '\n';
}
