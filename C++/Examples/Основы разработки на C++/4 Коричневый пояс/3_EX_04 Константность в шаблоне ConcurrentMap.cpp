#if 0 //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/tree/main/week3/04%20Programming%20Assingment

#undef MINE
#define GITHUB

#include <future>
#include <mutex>
#include <numeric>
#include <random>
#include <unordered_map>
#include <utility>
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

#ifdef MINE
template <typename K, typename V, typename Hash = hash<K>>
class ConcurrentMap {
public:
	using MapType = unordered_map<K, V, Hash>;
	explicit ConcurrentMap(size_t bucket_count) : maps(std::move(decltype(maps){bucket_count})) {}

	class WriteAccess {
		lock_guard<mutex> lock;
	public:
		WriteAccess(mutex &mtx, MapType &mp, const K &key) : lock(mtx), ref_to_value(mp[key]) {} //TEST //														mp[key] must be used to insert values.
		V &ref_to_value;
	};

	class ReadAccess {
		lock_guard<mutex> lock;
	public:
		ReadAccess(mutex &mtx, const MapType &mp, const K &key) : lock(mtx), ref_to_value(mp.at(key)) {} //TEST! //										Perplexity: Do not access an element in a const unordered_map using the operator[], which is not available for constant maps. Use the at() method instead of the operator[].
		const V &ref_to_value;
	};

	WriteAccess operator[](const K &key);
	ReadAccess At(const K &key) const;
	bool Has(const K &key) const;
	MapType BuildOrdinaryMap() const;
private:
	Hash hasher;
	vector<pair<mutable mutex, MapType>> maps;
	size_t GetBucketIdx(const K &key) const { return hasher(key) % maps.size(); } //TEST!!  //															MINE: size_t GetBucketIdx(const K &key) const { return hasher(key) % bucket_count_; }
};

template <typename K, typename V, typename Hash>
ConcurrentMap<K, V, Hash>::WriteAccess ConcurrentMap<K, V, Hash>::operator[](const K &key) {
	auto &[mtx, mp] = maps.at(GetBucketIdx(key));
	return {mtx, mp, key};
}

template <typename K, typename V, typename Hash>
ConcurrentMap<K, V, Hash>::ReadAccess ConcurrentMap<K, V, Hash>::At(const K &key) const {
	auto &[mtx, mp] = maps.at(GetBucketIdx(key));
	return ReadAccess(const_cast<mutex &>(mtx), mp, key); // Cast away const since mtx is mutable.
}

template<typename K, typename V, typename Hash>
bool ConcurrentMap<K, V, Hash>::Has(const K &key) const {
	auto &[mtx, mp] = maps.at(GetBucketIdx(key));
	lock_guard<mutex> lg(const_cast<mutex &>(mtx)); // Cast away const since mtx is mutable.
	return mp.contains(key);
}

template<typename K, typename V, typename Hash>
ConcurrentMap<K, V, Hash>::MapType ConcurrentMap<K, V, Hash>::BuildOrdinaryMap() const {
	MapType result;
	for (auto &[mtx, mp] : maps) {
		lock_guard<mutex> lg(const_cast<mutex &>(mtx)); // Cast away const since mtx is mutable.
		result.insert(mp.begin(), mp.end());
	}
	return result;
}
#endif //MINE

#ifdef GITHUB //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week3/04%20Programming%20Assingment/solution.cpp
template <typename K, typename V, typename Hash = std::hash<K>>
class ConcurrentMap {
public:
	using MapType = unordered_map<K, V, Hash>;
private:
	struct Bucket {
		MapType data;
		mutable mutex m; //TEST!! //																														Myself: Must be after data.
	};

	Hash hasher;
	vector<Bucket> buckets;
public:
	struct WriteAccess : lock_guard<mutex> { //TEST!! //																									��������� ������������ �� lock_guard<mutex>, ����� �������������, ��� ������� // ����� �������� �� ����������� bucket'�. ������ ������������ ����� ���� �� // ������ �������� ���� ���� lock_guard<mutex>, �� ����� ������ ���������� // �� ������� ������������� ����� � �� �����������, ��� � ������� �� �������� �� ����������
		V &ref_to_value;
		WriteAccess(const K &key, Bucket &bucket) : lock_guard(bucket.m), ref_to_value(bucket.data[key]) {}
	};

	struct ReadAccess : lock_guard<mutex> {
		const V &ref_to_value;
		ReadAccess(const K &key, const Bucket &bucket) : lock_guard(bucket.m), ref_to_value(bucket.data.at(key)) {}
	};

	explicit ConcurrentMap(size_t bucket_count) : buckets(bucket_count) {}
	WriteAccess operator[](const K &key) { return {key, buckets[GetIndex(key)]}; }
	ReadAccess At(const K &key) const { return {key, buckets[GetIndex(key)]}; } //TEST!! //																	Myself: Unlike my approach, which retrieves the mutex by reference (auto &[mtx, mp] = maps.at(GetBucketIdx(key));), passing an entire bucket (with the mutable mutex) allows the mutex to be mutable in the ReadAccess constructor. Therefore, my approach requires using an improper const_cast (const_cast<mutex &>(mtx);).

	bool Has(const K &key) const {
		auto &bucket = buckets[GetIndex(key)];
		lock_guard g(bucket.m);
		return bucket.data.count(key) > 0;
	}

	MapType BuildOrdinaryMap() const {
		MapType result;
		for (auto &[data, mtx] : buckets) {
			lock_guard g(mtx);
			result.insert(begin(data), end(data));
		}
		return result;
	}
private:
	size_t GetIndex(const K &key) const { return hasher(key) % buckets.size(); }
};
#endif //GITHUB

void RunConcurrentUpdates(ConcurrentMap<int, int> &cm, size_t thread_count, int key_count) {
	auto kernel = [&cm, key_count](int seed) {
		vector<int> updates(key_count);
		iota(begin(updates), end(updates), -key_count / 2);
		shuffle(begin(updates), end(updates), default_random_engine(seed));
		for (int i = 0; i < 2; ++i)
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

	RunConcurrentUpdates(cm, thread_count, key_count);
	const auto result = as_const(cm).BuildOrdinaryMap();
	ASSERT_EQUAL(result.size(), key_count);
	for (auto &[k, v] : result)
		AssertEqual(v, 6, "Key = " + to_string(k));
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

void TestConstAccess() {
	const unordered_map<int, string> expected = {
	  {1, "one"},
	  {2, "two"},
	  {3, "three"},
	  {31, "thirty one"},
	  {127, "one hundred and twenty seven"},
	  {1598, "fifteen hundred and ninety eight"}
	};

	const ConcurrentMap<int, string> cm = [&expected] {
		ConcurrentMap<int, string> result(3);
		for (const auto &[k, v] : expected) {
			result[k].ref_to_value = v;
		}
		return result;
		}();

	vector<future<string>> futures;
	for (int i = 0; i < 10; ++i) {
		futures.push_back(async([&cm, i] {
			try {
				return cm.At(i).ref_to_value;
			}
			catch (exception &) {
				return string();
			}
			}));
	}
	futures.clear();

	ASSERT_EQUAL(cm.BuildOrdinaryMap(), expected);
}

//#define OFF
#ifdef OFF
void TestStringKeys() {
	const unordered_map<string, string> expected = {
	  {"one", "ONE"},
	  {"two", "TWO"},
	  {"three", "THREE"},
	  {"thirty one", "THIRTY ONE"},
	};

	const ConcurrentMap<string, string> cm = [&expected] {
		ConcurrentMap<string, string> result(2);
		for (const auto &[k, v] : expected) {
			result[k].ref_to_value = v;
		}
		return result;
		}();

	ASSERT_EQUAL(cm.BuildOrdinaryMap(), expected);
}

struct Point {
	int x, y;
};

struct PointHash {
	size_t operator()(Point p) const {
		hash<int> h;
		return h(p.x) * 3571 + h(p.y);
	}
};

bool operator==(Point lhs, Point rhs) {
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

void TestUserType() {
	ConcurrentMap<Point, size_t, PointHash> point_weight(5);

	vector<future<void>> futures;
	for (int i = 0; i < 1000; ++i) {
		futures.push_back(async([&point_weight, i] {
			point_weight[Point{i, i}].ref_to_value = i;
			}));
	}

	futures.clear();

	for (int i = 0; i < 1000; ++i) {
		ASSERT_EQUAL(point_weight.At(Point{i, i}).ref_to_value, i);
	}

	const auto weights = point_weight.BuildOrdinaryMap();
	for (int i = 0; i < 1000; ++i) {
		ASSERT_EQUAL(weights.at(Point{i, i}), i);
	}
}

void TestHas() {
	ConcurrentMap<int, int> cm(2);
	cm[1].ref_to_value = 100;
	cm[2].ref_to_value = 200;

	const auto &const_map = as_const(cm);
	ASSERT(const_map.Has(1));
	ASSERT(const_map.Has(2));
	ASSERT(!const_map.Has(3));
}
#endif //OFF

int main() {
	PRINT_FILE_LINE(); //MINE

	TestRunner tr;
	RUN_TEST(tr, TestConcurrentUpdate);
	RUN_TEST(tr, TestReadAndWrite);
	RUN_TEST(tr, TestSpeedup);
	RUN_TEST(tr, TestConstAccess);
#ifdef OFF
	RUN_TEST(tr, TestStringKeys);
	RUN_TEST(tr, TestUserType);
	RUN_TEST(tr, TestHas);
#endif //OFF
}
#endif //1

/*
������������� � ������� ConcurrentMap
���������

�� ��� �������� ������������� � ������ Synchronized, ������� ����������� � �������� ����� �� �++�. �� ������� ������ ������ �� ������ �������� ���������������� � ConcurrentMap. � �������, ��� �� �������� ��� � �������� ����� �� �++�, �� ������� ��� ������ ���� � unordered-���������� � mutable-����. � ������ �� �������� ��� ������, ����� ���������� ConcurrentMap � ��� ������������ ����������.

��� ������ � ����������� ������ �ConcurrentMap� �� ��������� ����� �� C++�. ���� ��������� � ������ ������� � ������������ �����������. ��� ��� ���� �� �� ��������� �������� ����, ������ ������ ������ ��� ������ � ����. �������������� ���������� �� ��������� � �������� ������ �� �++�:

	������ ������ ���� ������������ unordered-��������� ������ std::map

	���������� ���������� ����� ������������� ����, � �� ������ �������������

	����� �������� ����������� ������ Has � At

	����� ������� ����� BuildOrdinaryMap �����������

�������

������� ����������, ��� � ��� ���� unordered_map, � �������� ���������� ��������� �������. ����� ���������������� ������ � ����, �� ����� ������ ��������� � ����� unordered_map'� �������� ��������� (��������, �������� ��� unordered_map � ������ Synchronized). ������ ������� ����������, ��� � ��� ���� Synchronized<unordered_map<int, int>>, � ������� �������� ��� ����� �� 1 �� 10000. ���������� �������, ��� ����� �� ������ ������ �� ���������� � ����� 10, � �� ������� � ��������, � ����� 6712, �� ��� ������ �������� ��� ��������� ����� � ��� �� ���������. ��� ��������� ������� ������, � ���������� ��������� ������� �� ����� �� ��������. ��� ����, ���� �� ����� ���������� � ����� 6712 ������������ �� ���������� �������, �� �������������, ����������, �����������.

������ ��������� ���� � ������� ��� ������� �� ��������� ����������� � ���������������� ������� ������ � �������� ������ �� ��� ��������� ���������. ����� ��� ��������� ������ ������� � ������ ������ ��� ������� ����� �������� � ���� � ��� �� ����������, � ������, ������ ����������� ��� ������������. ��� ���� ��� ��������� ����������� � ���� ������. ��� ���� �������� ������ ������ ConcurrentMap ��� � ����� �����������:

template <typename K, typename V, typename Hash = std::hash<K>>
class ConcurrentMap {
public:
  using MapType = unordered_map<K, V, Hash>;

  struct WriteAccess {
	V& ref_to_value;
  };

  struct ReadAccess {
	const V& ref_to_value;
  };

  explicit ConcurrentMap(size_t bucket_count);

  WriteAccess operator[](const K& key);
  ReadAccess At(const K& key) const;

  bool Has(const K& key) const;

  MapType BuildOrdinaryMap() const;

private:
  Hash hasher;
};

	����������� ������ ConcurrentMap<K, V> ��������� ���������� �����������, �� ������� ���� ������� �� ������������ ������.

	operator[] ������ ����� ���� ��� ��, ��� ����������� �������� � unordered_map � ���� ���� key ������������ � �������, �� ������ ���������� ������ ������ WriteAccess, ���������� ������ �� ��������������� ��� ��������; ���� �� key ����������� � �������, � ���� ���� �������� ���� (key, V()) � ������� ������ ������ WriteAccess, ���������� ������ �� ������ ��� ����������� ��������.

	����� At ������ ����� ���� ��� ��, ��� ����������� ����� � unordered_map � ���� ���� key ������������ � �������, �� ������ ���������� ������ ������ ReadAccess, ���������� ����������� ������ �� ��������������� ��� ��������; ���� �� key ����������� � �������, ����� At ������ ��������� ���������� std::out_of_range.

	��������� WriteAccess � ReadAccess ������ ����� ���� ��� ��, ��� � � ������� Synchronized, � ������������� ������ �� �������� ������� � ������������ ������������� ������� � ����.

	����� BuildOrdinaryMap ������ ������� ������ ����� ������� � ���������� ���� ������� �������. ��� ���� �� ������ ���� ����������������, �� ���� ��������� ��������, ����� ������ ������ ��������� �������� � ConcurrentMap. � ������� �� ������ �� ��������� ����� �� �++� � ���� ������ ����� BuildOrdinaryMap ������ �����������.

	����� Has ������ ��������������� ���������, ��� ���������� ���� ������������ � �������.

	������ ��������� �������� � Hash � ������������ ��� ����������� ������ ���� K. ��� ��������� ���������� std::hash � ��� �����, ������� ����� ����������� size_t operator()(const K& key) const.
*/