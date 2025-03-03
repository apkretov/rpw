#ifdef ON

#include <functional>
#include <iostream>
#include <random>
#include "../../stdafx.h"
using namespace std;

void Generating_Random_Real_Numbers() {
	default_random_engine e; // generates unsigned random integers

#ifdef Generating_Random_Real_Numbers
	uniform_real_distribution<double> u(0, 1); // uniformly distributed from 0 to 1 inclusive
#elif! Using_the_Distribution_s_Default_Result_Type
	uniform_real_distribution<> u(0, 1); // empty <> signify we want to use the default result type // generates double by default
#endif

	for (size_t i = 0; i < 10; ++i)
		cout << u(e) << " ";
	cout << '\n';
}

void Generating_Numbers_That_Are_Not_Uniformly_Distributed() {
	default_random_engine e; // generates random integers
	normal_distribution<> n(4, 1.5); // mean 4, standard deviation 1.5
	vector<unsigned> vals(9); // nine elements each 0

	for (size_t i = 0; i != 200; ++i) {
		unsigned v = lround(n(e)); // round to the nearest integer
		if (v < vals.size()) // if this result is in range
			++vals[v]; // count how often each number appears
	}
	
	for (size_t j = 0; j != vals.size(); ++j)
		cout << j << ": " << string(vals[j], '*') << endl;

}

void The_bernoulli_distribution_Class() {
	string resp;
	default_random_engine e; // e has state, so it must be outside the loop!
	bernoulli_distribution b; // 50/50 odds by default

	auto play = [&b, &e](bool player) { //MINE
		cout << (player ? "You" : "I") << " roll: " << b(e) << endl;
		return !b(e); // return true if I rolled a 1
	};

	do {
		bool first = b(e); // if true, the program will go first
		cout << (first ? "We go first" : "You get to go first") << endl;
		cout << ((play(first)) ? "sorry, you lost" : "congrats, you won") << endl; // play the game passing the indicator of who goes first
		cout << "play again? Enter ’yes’ or ’no’" << endl;
	} while (cin >> resp && resp[0] == 'y');
}

int main() {
	print_file_line();

	//Generating_Random_Real_Numbers();
	Generating_Numbers_That_Are_Not_Uniformly_Distributed();
	//The_bernoulli_distribution_Class();
}
#endif
