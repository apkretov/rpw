#if 0 //@ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/tree/main/Week_5/01%20Programming%20Assignment

#include <cstdint>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

#ifdef ORIG
template <random_access_iterator RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
	vector<typename RandomIt::value_type> pool(first, last);
	size_t cur_pos = 0;
	while (!pool.empty()) {
		*(first++) = pool[cur_pos];
		pool.erase(pool.begin() + cur_pos);
		if (pool.empty())
			break;
		cur_pos = (cur_pos + step_size - 1) % pool.size();
	}
}
#endif //ORIG

#ifndef MINE
template <random_access_iterator RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
	vector<typename iterator_traits<RandomIt>::value_type> pool(make_move_iterator(first), make_move_iterator(last)); //TEST! //								GHATGPT: Move elements from the range [first, last) into the pool vector
	size_t cur_pos = 0;
	while (!pool.empty()) {
		*(first++) = move(pool[cur_pos]); 
		pool.erase(pool.begin() + cur_pos); 
		if (pool.empty())
			break;
		cur_pos = (cur_pos + step_size - 1) % pool.size(); 
	}
}
#endif //MINE

#ifdef GITHUB //ERR @ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/blob/main/Week_5/01%20Programming%20Assignment/Solution/permutation.cpp
template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
	std::list<typename RandomIt::value_type> pool;
	std::copy(std::make_move_iterator(first), std::make_move_iterator(last), std::inserter(pool, pool.end()));
	auto cur_pos = pool.begin();

	while (!pool.empty()) {
		*(first++) = std::move(*cur_pos);
		cur_pos = pool.erase(std::move(cur_pos));

		for (int i = 0; i < step_size - 1; ++i) {
			if (cur_pos == pool.end())
				cur_pos = pool.begin();
			cur_pos = std::move(std::next(cur_pos));
			if (cur_pos == pool.end())
				cur_pos = pool.begin();
		}
	}
}
#endif // GITHUB //ERR

vector<int> MakeTestVector() {
	vector<int> numbers(10);
	iota(begin(numbers), end(numbers), 0);
	return numbers;
}

//#pragma region MINE
//template <typename T>
//ostream &operator<<(ostream &os, const vector<T> &v) {
//	os << '{';
//	for (const auto &item : v)
//		os << item << ' ';
//	os << '}';
//	return os;
//}
//#pragma endregion //MINE

void TestIntVector() {
	const vector<int> numbers = MakeTestVector();
	{
		vector<int> numbers_copy = numbers;
		MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 1);
		ASSERT_EQUAL(numbers_copy, numbers);
	}
	{
		vector<int> numbers_copy = numbers;
		MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 3);
		ASSERT_EQUAL(numbers_copy, vector<int>({0, 3, 6, 9, 4, 8, 5, 2, 7, 1}));
	}
}

struct NoncopyableInt { // Это специальный тип, который поможет вам убедиться, что ваша реализация // функции MakeJosephusPermutation не выполняет копирование объектов. // Сейчас вы, возможно, не понимаете как он устроен, однако мы расскажем, // почему он устроен именно так, далее в блоке про move-семантику — // в видео «Некопируемые типы»
	int value;
	NoncopyableInt(int value) : value(value) {}
	NoncopyableInt(const NoncopyableInt &) = delete;
	NoncopyableInt &operator=(const NoncopyableInt &) = delete;
	NoncopyableInt(NoncopyableInt &&) = default;
	NoncopyableInt &operator=(NoncopyableInt &&) = default;
};

bool operator == (const NoncopyableInt &lhs, const NoncopyableInt &rhs) {
	return lhs.value == rhs.value;
}

ostream &operator << (ostream &os, const NoncopyableInt &v) {
	return os << v.value;
}

void TestAvoidsCopying() {
	vector<NoncopyableInt> numbers;
	numbers.push_back({1});
	numbers.push_back({2});
	numbers.push_back({3});
	numbers.push_back({4});
	numbers.push_back({5});

	MakeJosephusPermutation(begin(numbers), end(numbers), 2);

	vector<NoncopyableInt> expected;
	expected.push_back({1});
	expected.push_back({3});
	expected.push_back({5});
	expected.push_back({4});
	expected.push_back({2});

	ASSERT_EQUAL(numbers, expected);
}

int main() {
	PRINT_FILE_LINE();

	TestRunner tr;
	RUN_TEST(tr, TestIntVector);
	RUN_TEST(tr, TestAvoidsCopying);

	return 0;
}
#endif //1

/*
Считалка Иосифа
Условие

Дан диапазон объектов некоторого типа. Напишите функцию, переставляющую его элементы в соответствии с порядком, определённым так называемой считалкой Иосифа с заданным размером шага:

template <typename RandomIt>
void MakeJosephusPermutation(
	RandomIt range_begin, RandomIt range_end,
	uint32_t step_size
);

Гарантируется, что итераторы range_begin и range_end являются итераторами произвольного доступа, то есть допускают вычитание одного из другого и сложение с числом. Кроме того, вы можете полагаться на то, что step_size > 0. Тип переупорядочиваемых объектов можно получить с помощью выражения typename RandomIt::value_type. Объекты этого типа запрещено копировать. При наличии копирования этих объектов вы получите ошибку компиляции.
Ограничения

Максимальный размер диапазона — 10^5, максимальный размер шага — 10^2. Время выполнения одного вызова функции ограничено 1 секундой.
Решение с копированиями

Вам дано решение данной задачи, копирующее элементы и не укладывающееся в ограничения по времени, но в остальном корректное. Вы можете исправить его или написать своё.

josephus_permutation.cpp
*/