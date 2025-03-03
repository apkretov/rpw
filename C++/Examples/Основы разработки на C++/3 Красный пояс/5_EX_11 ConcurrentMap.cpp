#if 0 //@ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/tree/main/Week_5/11%20Programming%20Assignment

#include <algorithm>
#include <future>
#include <map>
#include <numeric>
#include <random>
#include <string>
#include <vector>
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

static constexpr int iter_count = 2; //MINE

template <typename K, typename V>
class ConcurrentMap {
	size_t bucket_count_;
	vector<pair<mutex, map<K, V>>> maps;
public:
	static_assert(is_integral_v<K>, "ConcurrentMap supports only integer keys");
	explicit ConcurrentMap(size_t bucket_count) : bucket_count_(bucket_count), maps(std::move(decltype(maps){bucket_count})) {}

	class Access {
		lock_guard<mutex> lock;
	public:
#ifdef MINE
		Access(mutex &mtx, map<K, V> &mp, const K &key) : lock(mtx), ref_to_map(mp), ref_to_value(mp[key]) {} // Constructor for accessing a specific value
		Access(mutex &mtx, map<K, V> &mp) : lock(mtx), ref_to_map(mp), ref_to_value(mp.begin()->second) {} // Constructor for accessing the entire map: default initialization.  
		map<K, V> &ref_to_map;
#else //GITHUB
		Access(mutex &mtx, map<K, V> &mp, const K &key) : lock(mtx), ref_to_value(mp[key]) {} // Constructor for accessing a specific value
#endif //GITHUB
		V &ref_to_value;
	};

	Access operator[](const K &key);
	map<K, V> BuildOrdinaryMap();
};

template <typename K, typename V>
ConcurrentMap<K, V>::Access ConcurrentMap<K, V>::operator[](const K &key) {
	size_t hash = static_cast<size_t>(key) % bucket_count_;
	auto &[mtx, mp] = maps[hash];
	return {mtx, mp, key};
}

template <typename K, typename V>
map<K, V> ConcurrentMap<K, V>::BuildOrdinaryMap() {
	map<K, V> result;
	for (auto &[mtx, mp] : maps) {
#ifdef MINE
		Access access{mtx, mp};
		result.insert(access.ref_to_map.begin(), access.ref_to_map.end());
#else //GITHUB
		lock_guard<mutex> lg{mtx}; //TEST!
		result.insert(mp.begin(), mp.end());
#endif //GITHUB
	}
	return result;
}

void RunConcurrentUpdates(ConcurrentMap<int, int> &cm, size_t thread_count, int key_count, int iter_count_ = iter_count) { //ORIG: void RunConcurrentUpdates(ConcurrentMap<int, int> &cm, size_t thread_count, int key_count) {
	auto kernel = [&cm, key_count, iter_count_](int seed) { //ORIG auto kernel = [&cm, key_count](int seed) {
		vector<int> updates(key_count);
		iota(begin(updates), end(updates), -key_count / 2);
		shuffle(begin(updates), end(updates), default_random_engine(seed));

		for (int i = 0; i < iter_count_; ++i) //ORIG for (int i = 0; i < 2; ++i)
			for (auto key : updates)
				cm[key].ref_to_value++;
	};

	vector<future<void>> futures;
	for (size_t i = 0; i < thread_count; ++i)
		futures.push_back(async(kernel, i));
}

void TestConcurrentUpdate() {
	const size_t thread_count = 3;
	const size_t key_count = 50000;
	ConcurrentMap<int, int> cm(thread_count);
	RunConcurrentUpdates(cm, thread_count, key_count, iter_count); //ORIG RunConcurrentUpdates(cm, thread_count, key_count);

	const auto result = cm.BuildOrdinaryMap();
	ASSERT_EQUAL(result.size(), key_count);
	for (auto &[k, v] : result)
		AssertEqual(v, thread_count * iter_count, "Key = " + to_string(k)); //ORIG AssertEqual(v, 6, "Key = " + to_string(k));
}

void TestReadAndWrite() {
	ConcurrentMap<size_t, string> cm(5);

	auto updater = [&cm] {
		for (size_t i = 0; i < 50000; ++i)
			cm[i].ref_to_value += 'a';
	};
	auto reader = [&cm] {
		vector<string> result(50000);
		for (size_t i = 0; i < result.size(); ++i)
			result[i] = cm[i].ref_to_value;
		return result;
	};

	auto u1 = async(updater);
	auto r1 = async(reader);
	auto u2 = async(updater);
	auto r2 = async(reader);
	u1.get();
	u2.get();

	for (auto f : {&r1, &r2}) {
		auto result = f->get();
		ASSERT(all_of(result.begin(), result.end(), [](const string &s) { return s.empty() || s == "a" || s == "aa"; }));
	}
}

void TestSpeedup() {
	{
		ConcurrentMap<int, int> single_lock(1);

		LOG_DURATION("Single lock");
		RunConcurrentUpdates(single_lock, 4, 50000);
	}
	{
		ConcurrentMap<int, int> many_locks(100);

		LOG_DURATION("100 locks");
		RunConcurrentUpdates(many_locks, 4, 50000);
	}
}

void TestMine() {
	constexpr size_t thread_count = 3;
	constexpr int key_count = 50000;
	constexpr int iter_count_ = iter_count;
	ConcurrentMap<int, int> cm(thread_count);

	auto kernel = [&cm, key_count, iter_count_](int seed) {
		vector<int> updates(key_count);
		iota(begin(updates), end(updates), -key_count / 2);
		shuffle(begin(updates), end(updates), default_random_engine(seed));

		for (int i = 0; i < iter_count_; ++i) {
			for (auto key : updates)
				cm[key].ref_to_value++;
		}
	};

	vector<future<void>> futures;
	for (size_t i = 0; i < thread_count; ++i)
		futures.push_back(async(kernel, i));

#ifndef JOIN_THREADS
	for (auto &fnc : futures)
		fnc.get();
#endif //JOIN_THREADS

	future<map<int, int>> future_map = async(launch::async, [&cm] { return cm.BuildOrdinaryMap(); });
	auto mp = future_map.get();
	ASSERT_EQUAL(mp.size(), key_count);
}

int main() {
	PRINT_FILE_LINE();

	TestRunner tr;
	RUN_TEST(tr, TestConcurrentUpdate);
	RUN_TEST(tr, TestReadAndWrite);
	RUN_TEST(tr, TestSpeedup);
	RUN_TEST(tr, TestMine);
}
#endif //1

#ifdef GITHUB //@ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/blob/main/Week_5/11%20Programming%20Assignment/Solution/concurrent_map.cpp

#include <algorithm>
#include <cmath>
#include <future>
#include <map>
#include <numeric>
#include <random>
#include <string>
#include <vector>
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

template <typename K, typename V>
class ConcurrentMap {
public:
	static_assert(is_integral_v<K>, "ConcurrentMap supports only integer keys");

	struct Access {
		Access(const K &key, pair<mutex, map<K, V>> &bucket_content) :
			guard(bucket_content.first), ref_to_value(bucket_content.second[key]) {
		}
		lock_guard<mutex> guard;
		V &ref_to_value;
	};
	explicit ConcurrentMap(size_t bucket_count);

	Access operator[](const K &key);

	map<K, V> BuildOrdinaryMap();
private:
	vector<pair<mutex, map<K, V>>> data;
};

template <typename K, typename V>
ConcurrentMap<K, V>::ConcurrentMap(size_t bucket_count) : data(bucket_count) {}

template <typename K, typename V>
typename ConcurrentMap<K, V>::Access ConcurrentMap<K, V>::operator[](const K &key) {
	auto &bucket = data[static_cast<size_t>(key) % data.size()]; //ERR: auto &bucket = data[(key < 0 ? -key : key) % data.size()];
	return {key, bucket};
}

template <typename K, typename V>
map<K, V> ConcurrentMap<K, V>::BuildOrdinaryMap() {
	map<K, V> temp;
	for (auto &[mtx, mapping] : data) {
		lock_guard<mutex> lck_guard{mtx}; //TEST!
		temp.insert(begin(mapping), end(mapping));
	}
	return temp;
}

void RunConcurrentUpdates(ConcurrentMap<int, int> &cm, size_t thread_count, int key_count) {
	auto kernel = [&cm, key_count](int seed) {
		vector<int> updates(key_count);
		iota(begin(updates), end(updates), -key_count / 2);
		shuffle(begin(updates), end(updates), default_random_engine(seed));

		for (int i = 0; i < 2; ++i) {
			for (auto key : updates) {
				cm[key].ref_to_value++;
			}
		}
		};

	vector<future<void>> futures;
	for (size_t i = 0; i < thread_count; ++i) {
		futures.push_back(async(kernel, i));
	}
}

void TestConcurrentUpdate() {
	const size_t thread_count = 3;
	const size_t key_count = 50000;

	ConcurrentMap<int, int> cm(thread_count);
	RunConcurrentUpdates(cm, thread_count, key_count);

	const auto result = cm.BuildOrdinaryMap();
	ASSERT_EQUAL(result.size(), key_count);
	for (auto &[k, v] : result) {
		ASSERT_EQUAL(v, 6);
	}
}

void TestReadAndWrite() {
	ConcurrentMap<size_t, string> cm(5);

	auto updater = [&cm] {
		for (size_t i = 0; i < 50000; ++i) {
			cm[i].ref_to_value += 'a';
		}
		};

	auto reader = [&cm] {
		vector<string> result(50000);
		for (size_t i = 0; i < result.size(); ++i) {
			result[i] = cm[i].ref_to_value;
		}
		return result;
		};

	auto u1 = async(updater);
	auto r1 = async(reader);
	auto u2 = async(updater);
	auto r2 = async(reader);

	u1.get();
	u2.get();

	for (auto f : {&r1, &r2}) {
		auto result = f->get();
		ASSERT(all_of(result.begin(), result.end(), [](const string &s) {
			return s.empty() || s == "a" || s == "aa";
			}));
	}
}

void TestSpeedup() {
	{
		ConcurrentMap<int, int> single_lock(1);

		LOG_DURATION("Single lock");
		RunConcurrentUpdates(single_lock, 4, 50000);
	}
	{
		ConcurrentMap<int, int> many_locks(100);

		LOG_DURATION("100 locks");
		RunConcurrentUpdates(many_locks, 4, 50000);
	}
}

int main() {
	TestRunner tr;
	tr.RunTest(TestConcurrentUpdate, "TestConcurrentUpdate");
	tr.RunTest(TestReadAndWrite, "TestReadAndWrite");
	tr.RunTest(TestSpeedup, "TestSpeedup");
	return 0;
}
#endif //GITHUB

/*
ConcurrentMap
�������

� ��������� ������� ������ ������� Synchronized� �� ��� ������ ��������� ���� � ���, ��� ���������� ������� ����������� ������ ��������� �������� �������� ������ ������������� ���������. � ���� ������ �� �������� � ������.

������� ����������, ��� � ��� ���� map, � �������� ���������� ��������� �������. ����� ���������������� ������ � ����, �� ����� ������ ��������� � ����� map'� �������� ��������� (��������, �������� ��� map � ������ Synchronized). ������ ������� ����������, ��� � ��� ���� Synchronized<map<int, int>>, � ������� �������� ��� ����� �� 1 �� 10000. ���������� �������, ��� ����� �� ������ ������ �� ���������� � ����� 10, � �� ������� � ��������, � ����� 6712, �� ��� ������ �������� ��� ��������� ����� � ��� �� ���������. ��� ��������� ������� ������, � ���������� ��������� ������� �� ����� �� ��������. ��� ����, ���� �� ����� ���������� � ����� 6712 ������������ �� ���������� �������, �� �������������, ����������, �����������.

������ ��������� ���� � ������� ��� ������� �� ���������� ����������� � ���������������� ������� ������ � �������� ������ �� ��� ��������� ���������. ����� ��� ��������� ������ ������� � ������ ������ ��� ������� ����� �������� � ���� � ��� �� ����������, � ������, ������ ����������� ��� ������������. ��� ���� ��� ��������� ����������� � ���� ������. ��� ���� �������� ������ ������ ConcurrentMap ��� � ����� �����������:

template <typename K, typename V>
class ConcurrentMap {
public:
  static_assert(is_integral_v<K>, "ConcurrentMap supports only integer keys");

  struct Access {
	V& ref_to_value;
  };

  explicit ConcurrentMap(size_t bucket_count);

  Access operator[](const K& key);

  map<K, V> BuildOrdinaryMap();
};

	static_assert � ������ ������ �������, ��� � ������ ������ ��������������, ��� ������� ConcurrentMap'� ����� ���� ������ ����� �����.
	����������� ������ ConcurrentMap<K, V> ��������� ���������� �����������, �� ������� ���� ������� �� ������������ ������.
	operator[] ������ ����� ���� ��� ��, ��� ����������� �������� � map � ���� ���� key ������������ � �������, �� ������ ���������� ������ ������ Access, ���������� ������ �� ��������������� ��� ��������; ���� �� key ����������� � �������, � ���� ���� �������� ���� (key, V()) � ������� ������ ������ Access, ���������� ������ �� ������ ��� ����������� ��������.
	��������� Access, ������ ����� ���� ��� ��, ��� � � ������� Synchronized, � ������������� ������ �� �������� ������� � ������������ ������������� ������� � ����.
	����� BuildOrdinaryMap ������ ������� ������ ����� ������� � ���������� ���� ������� �������. ��� ���� �� ������ ���� ����������������, �� ���� ��������� ��������, ����� ������ ������ ��������� �������� � ConcurrentMap.

���� � ���������� �������

concurrent_map.cpp
*/