#if 0 //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/tree/main/week1/02%20Programming%20Assingment

#undef MINE
#define ORIG

#include <forward_list>
#include <ranges>
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

struct IntHasher {
	size_t operator()(int value) const { return value; }
};

struct TestValue {
	int value;
	bool operator==(TestValue other) const { return value / 2 == other.value / 2; }
};

struct TestValueHasher {
	size_t operator()(TestValue value) const { return value.value / 2; }
};

#ifdef MINE
template <typename Type>
struct DefaultHasher {
	size_t operator()(const Type &value) const { return hash<Type>()(value); }
};

template <typename Type, typename Hasher = DefaultHasher<Type>>
#endif //MINE
#ifdef ORIG
template <typename Type, typename Hasher>
#endif //ORIG
class HashSet {
public:
	using BucketList = forward_list<Type>;
	explicit HashSet(size_t num_buckets, const Hasher &hasher = {});
	void Add(const Type &value);
	bool Has(const Type &value) const;
	void Erase(const Type &value) { buckets.at(GetBucketIndex(value)).remove(value); }
	const BucketList &GetBucket(const Type &value) const { return buckets.at(GetBucketIndex(value)); };
private:
	vector<BucketList> buckets;
	Hasher hasher_;
	size_t GetBucketIndex(const Type &value) const { return hasher_(value) % buckets.size(); }
};

template <typename Type, typename Hasher>
HashSet<Type, Hasher>::HashSet(size_t num_buckets, const Hasher &hasher) :
	buckets(num_buckets), 
#ifdef MINE
	hasher_(is_same_v<Hasher, DefaultHasher<Type>> ? DefaultHasher<Type>{} : hasher)
#endif //MINE
#ifdef ORIG
	hasher_(hasher)
#endif //ORIG

{}

template <typename Type, typename Hasher>
void HashSet<Type, Hasher>::Add(const Type &value) {
	BucketList &bucket_list = buckets.at(GetBucketIndex(value));
	auto value_iter = ranges::find_if(bucket_list, [&value](const Type &item) { return value == item; });
	if (value_iter == bucket_list.end()) 
		bucket_list.push_front(value);
}

template <typename Type, typename Hasher>
bool HashSet<Type, Hasher>::Has(const Type &value) const {
	auto bucket_list = GetBucket(value);
	auto value_iter = ranges::find_if(bucket_list, [&value](const Type &item) { return value == item; });
	return (value_iter != bucket_list.end());
}

#ifdef MINE
void TestMine() {
	HashSet<int> hs(5);
	hs.Add(10);
	hs.Add(20);
	hs.Add(30);

	cout << boolalpha << AS_KV(hs.Has(10)) << '\n';
	cout << boolalpha << AS_KV(hs.Has(20)) << '\n';
	cout << boolalpha << AS_KV(hs.Has(30)) << '\n';
	cout << boolalpha << AS_KV(hs.Has(40)) << "\n\n";

	hs.Erase(20);
	cout << boolalpha << AS_KV(hs.Has(10)) << '\n';
	cout << boolalpha << AS_KV(hs.Has(20)) << '\n';
	cout << boolalpha << AS_KV(hs.Has(30)) << '\n';
}
#endif //MINE

#ifdef ORIG
void TestSmoke() {
	HashSet<int, IntHasher> hash_set(2);
	hash_set.Add(3);
	hash_set.Add(4);

	ASSERT(hash_set.Has(3));
	ASSERT(hash_set.Has(4));
	ASSERT(!hash_set.Has(5));

	hash_set.Erase(3);

	ASSERT(!hash_set.Has(3));
	ASSERT(hash_set.Has(4));
	ASSERT(!hash_set.Has(5));

	hash_set.Add(3);
	hash_set.Add(5);

	ASSERT(hash_set.Has(3));
	ASSERT(hash_set.Has(4));
	ASSERT(hash_set.Has(5));
}

void TestEmpty() {
	HashSet<int, IntHasher> hash_set(10);
	for (int value = 0; value < 10000; ++value) {
		ASSERT(!hash_set.Has(value));
	}
}

void TestIdempotency() {
	HashSet<int, IntHasher> hash_set(10);
	hash_set.Add(5);
	ASSERT(hash_set.Has(5));
	hash_set.Add(5);
	ASSERT(hash_set.Has(5));
	hash_set.Erase(5);
	ASSERT(!hash_set.Has(5));
	hash_set.Erase(5);
	ASSERT(!hash_set.Has(5));
}

void TestEquivalence() {
	HashSet<TestValue, TestValueHasher> hash_set(10);
	hash_set.Add(TestValue{2});
	hash_set.Add(TestValue{3});

	ASSERT(hash_set.Has(TestValue{2}));
	ASSERT(hash_set.Has(TestValue{3}));

	const auto &bucket = hash_set.GetBucket(TestValue{2});
	const auto &three_bucket = hash_set.GetBucket(TestValue{3});
	ASSERT_EQUAL(&bucket, &three_bucket);

	ASSERT_EQUAL(1, distance(begin(bucket), end(bucket)));
	ASSERT_EQUAL(2, bucket.front().value);
}
#endif //ORIG

int main() {
	PRINT_FILE_LINE();

	TestRunner tr;
#ifdef ORIG
	RUN_TEST(tr, TestSmoke);
	RUN_TEST(tr, TestEmpty);
	RUN_TEST(tr, TestIdempotency);
	RUN_TEST(tr, TestEquivalence);
#endif //ORIG
#ifdef MINE
	RUN_TEST(tr, TestMine);
#endif //MINE

	return 0;
}
#endif //1

/*
Хеш-таблица

Теперь, когда вы знаете, как unordered-контейнеры устроены внутри, вам предлагается самостоятельно реализовать упрощённую версию хеш-таблицы. Реализуйте шаблон HashSet:

template <typename Type, typename Hasher>
class HashSet {
public:
  using BucketList = forward_list<Type>;

public:
  explicit HashSet(
	  size_t num_buckets,
	  const Hasher& hasher = {}
  );

  void Add(const Type& value);
  bool Has(const Type& value) const ;
  void Erase(const Type& value);
  const BucketList& GetBucket(const Type& value) const;
};

Требования:

	В любой момент времени в вашей хеш-таблице должно быть ровно num_buckets корзин. Рехеширование выполнять не нужно.

	Метод Add не должен менять содержимое таблицы, если элемент, равный данному, уже есть в таблице.

	Метод Has должен возвращать true тогда и только тогда, когда элемент, равный данному, есть в таблице.

	Метод Erase должен стирать элемент, равный данному, из таблицы, если он там есть, в противном случае он не должен менять содержимое таблицы.

	Метод GetBucket должен возвращать ссылку на бакет, который содержал бы данный элемент, вне зависимости от того, есть он в таблице или нет.

*/