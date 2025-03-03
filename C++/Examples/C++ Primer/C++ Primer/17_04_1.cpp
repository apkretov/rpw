#ifdef ON

#include <functional>
#include <iostream>
#include <random>
#include <ranges>
#include "../../stdafx.h"
#include "14_08_2_util.h"
using namespace std;

void Random_Number_Engines_and_Distribution() {
	default_random_engine e; // generates random unsigned integers
	for (size_t i = 0; i < 10; ++i)
		cout << e() << " "; // e() "calls" the object to produce the next random number
	cout << '\n'; //MINE
}

void Distribution_Types_and_Engines() {
	uniform_int_distribution<unsigned> u(0, 9); // uniformly distributed from 0 to 9 inclusive
	default_random_engine e; // generates unsigned random integers
	for (size_t i = 0; i < 10; ++i)
		cout << u(e) << " "; // u uses e as a source of numbers // each call returns a uniformly distributed value in the specified range
	cout << '\n'; //MINE
}

void Comparing_Random_Engines_and_the_rand_Function() {
	default_random_engine e; //MINE
	cout << "min: " << e.min() << " max: " << e.max() << endl;
}

#pragma region Engines Generate a Sequence of Numbers
vector<unsigned> bad_randVec() { // almost surely the wrong way to generate a vector of random integers // output from this function will be the same 100 numbers on every call!
	default_random_engine e;
	uniform_int_distribution<unsigned> u(0, 9);
	vector<unsigned> ret;
	for (size_t i = 0; i < 100; ++i)
		ret.push_back(u(e));
	return ret;
}

vector<unsigned> good_randVec(); //MINE

void Engines_Generate_a_Sequence_of_Numbers(function<vector<unsigned>()> randVec) {
#ifdef ORIG
	vector<unsigned> v1(bad_randVec());
	vector<unsigned> v2(bad_randVec());
#else //MINE
	vector<unsigned> v1(randVec());
	vector<unsigned> v2(randVec());
#endif
	ranges::copy(v1, ostream_iterator<unsigned>(cout, " ")); cout << "\n\n"; //MINE
	ranges::copy(v2, ostream_iterator<unsigned>(cout, " ")); cout << "\n\n"; //MINE

	cout << ((v1 == v2) ? "equal" : "not equal") << endl; // will print equal
	cout << '\n'; //MINE
}

vector<unsigned> good_randVec() { // returns a vector of 100 uniformly distributed random numbers
	static default_random_engine e; // because engines and distributions retain state, they usually should be // defined as static so that new numbers are generated on each call
	static uniform_int_distribution<unsigned> u(0, 9);
	vector<unsigned> ret;
	for (size_t i = 0; i < 100; ++i)
		ret.push_back(u(e));
	return ret;
}
#pragma endregion

vector<unsigned> mine() {
	Rnd rnd;
	vector<unsigned> ret;
	for (size_t i = 0; i < 100; ++i)
		//ret.push_back(u(e));
		ret.push_back(rnd());
	return ret;
}

void Seeding_a_Generator() {
	default_random_engine e1; // uses the default seed
	default_random_engine e2(2147483646); // use the given seed value
	
	default_random_engine e3; // e3 and e4 will generate the same sequence because they use the same seed // uses the default seed value
	e3.seed(32767); // call seed to set a new seed value
	default_random_engine e4(32767); // set the seed value to 32767

	for (size_t i = 0; i != 100; ++i) {
		if (e1() == e2())
			cout << "unseeded match at iteration: " << i << endl;
		if (e3() != e4())
			cout << "seeded differs at iteration: " << i << endl;
	}

	{
		default_random_engine e1(time(0)); // a somewhat random seed
	}
}

int main() {
	print_file_line();

	//Random_Number_Engines_and_Distribution();
	//Distribution_Types_and_Engines();
	//Comparing_Random_Engines_and_the_rand_Function();
	Engines_Generate_a_Sequence_of_Numbers(bad_randVec);
	Engines_Generate_a_Sequence_of_Numbers(good_randVec);
	Engines_Generate_a_Sequence_of_Numbers(mine);
	//Seeding_a_Generator();
}
#endif
