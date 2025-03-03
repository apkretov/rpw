#if 0 // @ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/tree/main/Week_5/05%20Practice%20Programming%20Assignment

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <ranges>
#include <vector>
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

template <typename T>
class SimpleVector {
public:
	SimpleVector() = default;
	explicit SimpleVector(size_t);
	SimpleVector(initializer_list<string>);
	SimpleVector(const SimpleVector &);
	SimpleVector(SimpleVector &&s) noexcept : elements(s.elements), first_free(s.first_free), cap(s.cap) { s.elements = s.first_free = s.cap = nullptr; }
	~SimpleVector() { free(); }
	SimpleVector &operator=(const SimpleVector &);
	SimpleVector &operator=(SimpleVector &&) noexcept;
	T &operator[](size_t index);
	const T &operator[](size_t index) const;
	T *begin() { return elements; }
	T *end() { return first_free; }
	const T *begin() const { return elements; }
	const T *end() const { return first_free; }
	size_t Size() const { return first_free - elements; }
	size_t Capacity() const { return cap - elements; }
	void PushBack(const T &); // GPT: 1. Define both PushBack and free inside the class for better encapsulation and clarity. // 2. Avoid using the inline keyword for these functions since they are non - trivial in size and complexity, which could lead to code bloat and negatively impact cache performance.
	void PushBack(T &&);
private: 
	static allocator<T> alloc;
	T *elements = nullptr;
	T *first_free = nullptr;
	T *cap = nullptr;
	void chk_n_alloc();
	void free();
};

template <typename T>
allocator<T> SimpleVector<T>::alloc;

template <typename T>
SimpleVector<T>::SimpleVector(size_t size) try : elements(alloc.allocate(size)), first_free(elements + size), cap(first_free) {
	for (T *p = elements; p != first_free; ++p)
		construct_at(p, T{});
}
catch (const bad_alloc &e) {
	cerr << "Error in SimpleVector(size_t size): " << e.what() << '\n';
	throw;
}

template <typename T>
SimpleVector<T>::SimpleVector(initializer_list<string> il) try : elements(alloc.allocate(il.size())), first_free(elements + il.size()), cap(first_free) {
#ifdef _1
	for (auto iter = il.begin(); iter != il.end(); ++iter)
		construct_at(elements + (iter - il.begin()), *iter);
#else //_2
	uninitialized_copy(il.begin(), il.end(), elements);
#endif //_2
}
catch (const bad_alloc &e) {
	cerr << "Error in SimpleVector(initializer_list<string> il): " << e.what() << '\n';
	throw;
}

template <typename T>
SimpleVector<T>::SimpleVector(const SimpleVector &s) try : elements(alloc.allocate(s.Size())), first_free(elements + s.Size()), cap(first_free) {
#ifdef _1
	for (T *p = elements; p != first_free; ++p)
		construct_at(p, s[p - elements]);
#else //_2
	uninitialized_copy(s.begin(), s.end(), elements);
#endif // _2
}
catch (const bad_alloc &e) {
	cerr << "Error in SimpleVector(initializer_list<string> il): " << e.what() << '\n';
	throw;
}

template <typename T>
SimpleVector<T> &SimpleVector<T>::operator=(const SimpleVector &rhs) {
#ifdef _1
	SimpleVector tmp(rhs);
	std::swap(elements, tmp.elements);
	std::swap(first_free, tmp.first_free);
	std::swap(cap, tmp.cap);
#else //_2
	if (&rhs != this) {
		auto first = alloc.allocate(rhs.Size());
		auto last = uninitialized_copy(rhs.begin(), rhs.end(), first);
		free();
		elements = first;
		first_free = cap = last;
	}
#endif //_2
	return *this;
}

template <typename T>
SimpleVector<T> &SimpleVector<T>::operator=(SimpleVector &&rhs) noexcept {
#ifdef _1
	std::swap(elements, rhs.elements);
	std::swap(first_free, rhs.first_free);
	std::swap(cap, rhs.cap);
#else //_2
	if (&rhs != this) {
		free();
		elements = rhs.elements;
		first_free = rhs.first_free;
		cap = rhs.cap;
		rhs.elements = rhs.first_free = rhs.cap = nullptr;
	}
#endif //_2
	return *this;
}

template <typename T>
T &SimpleVector<T>::operator[](size_t index) {
	if (index >= Size())
		throw out_of_range{"out_of_range"};
	return elements[index];
}

template <typename T>
const T &SimpleVector<T>::operator[](size_t index) const {
	if (index >= Size())
		throw out_of_range{"out_of_range"};
	return elements[index];
}

template <typename T>
void SimpleVector<T>::PushBack(const T &value) { 
	chk_n_alloc();
	construct_at(first_free++, value);
}

template <typename T>
void SimpleVector<T>::PushBack(T &&value) {
	chk_n_alloc();
	construct_at(first_free++, std::move(value));
}

template <typename T>
void SimpleVector<T>::chk_n_alloc() {
	if (Size() == Capacity()) {
		auto newcapacity = Size() ? Size() * 2 : 1;
		auto first = alloc.allocate(newcapacity);
		auto last = uninitialized_copy(make_move_iterator(begin()), make_move_iterator(end()), first);
		free();
		elements = first;
		first_free = last;
		cap = elements + newcapacity;
	}
}

template <typename T>
void SimpleVector<T>::free() {
	if (elements != nullptr) {
		for (T *p = first_free - 1; p != elements; --p) // Destroy the items backwards.
			destroy_at(p);
		alloc.deallocate(elements, cap - elements);
	}
}

void TestConstruction() {
	SimpleVector<int> empty;
	ASSERT_EQUAL(empty.Size(), 0u);
	ASSERT_EQUAL(empty.Capacity(), 0u);
	ASSERT(empty.begin() == empty.end());

	SimpleVector<string> five_strings(5);
	ASSERT_EQUAL(five_strings.Size(), 5u);
	ASSERT(five_strings.Size() <= five_strings.Capacity());
	for (auto &item : five_strings) {
		ASSERT(item.empty());
	}
	five_strings[2] = "Hello";
	ASSERT_EQUAL(five_strings[2], "Hello");
}

void TestPushBack() {
	SimpleVector<int> v;
	for (int i = 10; i >= 1; --i) {
		v.PushBack(i);
		ASSERT(v.Size() <= v.Capacity());
	}
	sort(begin(v), end(v));

	const vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	ASSERT(equal(begin(v), end(v), begin(expected)));
}

class StringNonCopyable : public string {
public:
	using string::string; //TEST!
	StringNonCopyable(string &&other) : string(move(other)) {}
	StringNonCopyable(const StringNonCopyable &) = delete;
	StringNonCopyable(StringNonCopyable &&) = default;
	StringNonCopyable &operator=(const StringNonCopyable &) = delete;
	StringNonCopyable &operator=(StringNonCopyable &&) = default;
};

void TestNoCopy() {
	SimpleVector<StringNonCopyable> strings;
	static const int SIZE = 10;
	for (int i = 0; i < SIZE; ++i) {
		strings.PushBack(StringNonCopyable(to_string(i)));
	}
	for (int i = 0; i < SIZE; ++i) {
		ASSERT_EQUAL(strings[i], to_string(i));
	}
}

void TestMine1() { //MINE
	SimpleVector<string> strings;
	strings.PushBack("aaa");
	strings.PushBack("bbb");
	strings.PushBack("ccc");
	auto strings_copy(strings);

	cout << "strings_copy: ";
	for (const auto &item : strings_copy) // Using begin() & end().
		cout << item << ' ';
	cout << '\n';

	for (size_t i = 0; i < strings.Size(); ++i) // Using operator[].
		ASSERT_EQUAL(strings[i], strings_copy[i]);

	auto strings_moved(std::move(strings_copy));
	cout << "strigns_moved: ";
	ostream_iterator<string> out(cout, " ");
	ranges::copy(strings_moved, out);

	strings_copy = strings_moved;
	cout << "\nstrings_copy: ";
	ranges::copy(strings_copy, out);

	strings_copy = strings_copy;
	cout << "\nstrings_copy self-copy: ";
	ranges::copy(strings_copy, out);

	SimpleVector<string> strings_moved2;
	strings_moved2 = std::move(strings_moved);
	cout << "strings_moved2: ";
	ranges::copy(strings_moved2, out);

	cout << "\nstrings_moved2 self-copy: ";
	strings_moved2 = std::move(strings_moved2);
	ranges::copy(strings_moved2, out);

#ifdef _1
	cout << "\nstrings_moved3: ";
	SimpleVector<string> strings_moved3;
#ifdef _11
	strings_moved3 = SimpleVector<string>{3};
#else //_12
	strings_moved3 = SimpleVector<string>{"xxx", "yyy", "zzz"};
#endif //_12

#else //_2
	cout << "\nstrings_moved2 swap move-assignment: ";
	strings_moved2 = SimpleVector<string>{"xxx", "yyy", "zzz"};
	ranges::copy(strings_moved2, out);
	cout << '\n';
#endif //_2
}

struct NonSwappable {
	NonSwappable() = default;
	NonSwappable(const NonSwappable &) = delete;
	NonSwappable(NonSwappable &&) = delete;
};

void TestMine2() {
	SimpleVector<string> vec1{"one", "two", "three"};
	vec1 = std::move(vec1);

	SimpleVector<NonSwappable> vec2;
	vec2 = std::move(vec2);
}

void TestMine3() {
	try {
		constexpr auto size = 100'000'000'000;
		cout << "\nmax_sized: size = " << format_num(size) << endl;
		SimpleVector<long double> max_sized(size);
	}
	catch (const bad_alloc &e) {
		cerr << "Error in TestMine(): " << e.what() << '\n';
	}
}

int main(int argc, char *argv[]) {
	PRINT_FILE_LINE();

	TestRunner tr;
	RUN_TEST(tr, TestConstruction);
	RUN_TEST(tr, TestNoCopy);
	RUN_TEST(tr, TestPushBack);

	cout << '\n';
	RUN_TEST(tr, TestMine1);
	RUN_TEST(tr, TestMine2);
	RUN_TEST(tr, TestMine3);

	return 0;
}
#endif //1

/*
Move-семантика в SimpleVector
Условие

Решите задачу «Реализовать свой вектор» со следующими дополнительными требованиями:

	метод PushBack должен позволять добавить элемент в вектор с помощью перемещения;
	никакие методы вектора не должны осуществлять копирование элементов.

Таким образом, должен получиться вектор, позволяющий хранить некопируемые объекты.

Шаблон решения содержит юнит-тест, проверяющий работу вектора, состоящего из некопируемых строк. Если вектор будет осуществлять копирования, благодаря указанному юнит-тесту решение не скомпилируется.
Файл с заготовкой решения

simple_vector_2.h

simple_vector_2.cpp
*/