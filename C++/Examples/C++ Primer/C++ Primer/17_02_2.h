#pragma once

#ifndef EX_17_11_2 // ch17/ex17_11_12_13.cpp @ https://github.com/Mooophy/Cpp-Primer/blob/master/ch17/ex17_11_12_13.cpp

#include <bitset>
#include <iostream>
#include <string>
#include <utility>
using std::bitset;
using std::ostream;
using std::pair;
using std::size_t;
using std::string;

template <size_t N> //TEST!! //class Quiz
class Quiz {
public:
	Quiz() = default; //constructors

	//ORIG Quiz(string &s) : bitquiz(s) {}
	explicit Quiz(const string &s) : bitquiz(s) {} //MINE
	explicit Quiz(string &&s) noexcept : bitquiz(std::move(s)) {} //MINE

	template <size_t M> //generate grade
	friend size_t grade(Quiz<M> const &, Quiz<M> const &);

	template <size_t M> //TEST!! //print
	friend ostream &operator<<(ostream &, Quiz<M> const &);

	void update(pair<size_t, bool>); //update bitset
private:
	bitset<N> bitquiz;
};

template <size_t N>
void Quiz<N>::update(pair<size_t, bool> pair) {
	bitquiz.set(pair.first, pair.second);
}

template <size_t M>
ostream &operator<<(ostream &os, Quiz<M> const &quiz) {
	os << quiz.bitquiz;
	return os;
}

template <size_t M>
size_t grade(Quiz<M> const &corAns, Quiz<M> const &stuAns) { //TEST! //MINE: See the whole function.
	auto result = stuAns.bitquiz ^ corAns.bitquiz; //TEST!
	result.flip();
	return result.count();
}
#endif