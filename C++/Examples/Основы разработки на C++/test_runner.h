#pragma once

#include <algorithm>
#include <deque>
#include <iostream>
#include <map>
#include <sstream>
#include <ranges>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#pragma region //1_03 Оператор #
#define RUN_TEST(tr, func) tr.RunTest(func, #func)  
#pragma endregion

#pragma region //MINE__
#define ASSERT_EQUAL(t, u) AssertEqual(t, u, "")
#define ASSERT(b) Assert(b, "")
#pragma endregion //MINE__

#ifdef TMP_TEST_RUNNER_H //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week2/03%20Programming%20Assingment/test_runner.h
#include <map>
#include <unordered_map>
#include <set>

template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &s) {
	os << "{";
	bool first = true;
	for (const auto &x : s) {
		if (!first)
			os << ", ";
		first = false;
		os << x;
	}
	return os << "}";
}

template <class T>
std::ostream &operator<<(std::ostream &os, const std::set<T> &s) {
	os << "{";
	bool first = true;
	for (const auto &x : s) {
		if (!first)
			os << ", ";
		first = false;
		os << x;
	}
	return os << "}";
}

template <class K, class V>
std::ostream &operator<<(std::ostream &os, const std::unordered_map<K, V> &m) {
	os << "{";
	bool first = true;
	for (const auto &kv : m) {
		if (!first)
			os << ", ";
		first = false;
		os << kv.first << ": " << kv.second;
	}
	return os << "}";
}
#endif //TMP_TEST_RUNNER_H

template <class Container>
std::ostream &PrintContainer(std::ostream &os, const Container &c) { // Helper function to print containers (vectors, sets, deques)
	os << "{";
	bool first = true;
	for (const auto &x : c) {
		if (!first)
			os << ", ";
		first = false;
		os << x; // Assumes x has an operator<< defined.
	}
	return os << "}";
}

template <class Map>
std::ostream &PrintMap(std::ostream &os, const Map &m) { // Helper function to print maps (unordered_map)
	os << "{";
	bool first = true;
	for (const auto &[key, value] : m) {
		if (!first)
			os << ", ";
		first = false;
		os << key << ": " << value; // Assumes key & value have operator<< defined.
	}
	return 	os << "}";
}

#define PRINT_CONTAINER(containerType) \
template<class T> \
std::ostream&operator<<(std::ostream&os, const containerType<T>&c){ \
	return PrintContainer(os,c); \
}

#define PRINT_MAP(mapType) \
template<class K,class V> \
std::ostream&operator<<(std::ostream&os, const mapType<K,V>&m){ \
	return PrintMap(os,m); \
}

PRINT_CONTAINER(std::vector);
PRINT_CONTAINER(std::deque);
PRINT_CONTAINER(std::set);
PRINT_CONTAINER(std::multiset);
PRINT_CONTAINER(std::unordered_set);
PRINT_CONTAINER(std::unordered_multiset);

PRINT_MAP(std::map);
PRINT_MAP(std::multimap);
PRINT_MAP(std::unordered_map);
PRINT_MAP(std::unordered_multimap);

class TestRunner {
public:
	~TestRunner() {
		if (fail_count > 0) {
			std::cerr << fail_count << " tests failed. Terminate.\n";
			exit(1);
		}
	}

	template <typename TestFunc>
	void RunTest(TestFunc func, std::string_view test_name) {
		try {
			func();
			std::cerr << test_name << " OK" << std::endl;
		}
		catch (const std::runtime_error &e) {
			++fail_count;
			std::cerr << test_name << " failed: " << e.what() << std::endl;
		}
	}
private:
	int fail_count{};
};

template <typename T, typename U>
void AssertEqual(const T &t, const U &u, std::string_view hint) { //ORIG void AssertEqual(const T &t, const U &u, const string &hint) {
	if (t != u) {
		std::ostringstream os;
		//ORIG os << "Assertion failed: " << t << " != " << u << " Hint: " << hint;
#pragma region MINE__
		if (hint.empty())
			os << "Assertion failed: " << t << " != " << u;
		else
			os << "Assertion failed: " << t << " != " << u << " Hint: " << hint;
#pragma endregion //MINE__
		throw std::runtime_error(os.str());
	}
}

void Assert(bool b, std::string_view hint) { //ORIG void Assert(bool b, const string &hint) {
	AssertEqual(b, true, hint);
}
