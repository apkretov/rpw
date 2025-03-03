#pragma once

#undef MINE
#define GITHUB

#include <map>
#include <string>
#include <unordered_map> 
#include <unordered_set>
using std::map;
using std::multimap;
using std::string;
using std::unordered_map;
using std::unordered_set;

struct Record {
	string id;
	string title;
	string user;
	int timestamp;
	int karma;
};

#ifdef MINE
class Database {
	unordered_map<string, Record> records;
	unordered_map<string, unordered_set<string>> user_ids;
	map<int, string> timestamp_ids;
	map<int, unordered_set<string>> karma_ids;
	template <typename MapType, typename KeyType> void EraseIds(MapType &id_map, const KeyType &key, const string &id);
	template<typename MapType, typename Callback> void RangeByMap(MapType &id_map, int low, int high, Callback callback) const;
public:
	bool Put(const Record &record);
	const Record *GetById(const string &id) const;
	bool Erase(const string &id);
	template <typename Callback> void RangeByTimestamp(int low, int high, Callback callback) const { RangeByMap(timestamp_ids, low, high, callback); }
	template <typename Callback> void RangeByKarma(int low, int high, Callback callback) const { RangeByMap(karma_ids, low, high, callback); }
	template <typename Callback> void AllByUser(const string &user, Callback callback) const;
};

bool Database::Put(const Record &record) {
	if (!records.try_emplace(record.id, record).second)  //@ https://en.cppreference.com/w/cpp/container/map/try_emplace
		return false;

	user_ids[record.user].emplace(record.id);
	timestamp_ids[record.timestamp] = record.id;
	karma_ids[record.karma].emplace(record.id);

	return true;
}

const Record *Database::GetById(const string &id) const {
	auto iter = records.find(id); //@ https://cplusplus.com/reference/unordered_map/unordered_map/find/
	if (iter != records.end())
		return &iter->second;
	else
		return nullptr;
}

template <typename MapType, typename KeyType>
void Database::EraseIds(MapType &ids_map, const KeyType &key, const string &id) {
	auto &ids_set = ids_map.at(key);
	ids_set.erase(id);
	if (ids_set.empty())
		ids_map.erase(key);
}

bool Database::Erase(const string &id) {
	auto ptr = GetById(id);
	if (ptr == nullptr)
		return false;

	EraseIds(user_ids, ptr->user, id);
	timestamp_ids.erase(ptr->timestamp);
	EraseIds(karma_ids, ptr->karma, id);
	records.erase(id);

	return true;
}

template<typename MapType, typename Callback>
void Database::RangeByMap(MapType &id_map, int low, int high, Callback callback) const {
	for (auto iter = id_map.lower_bound(low); iter != id_map.upper_bound(high); ++iter)
		for (const auto &id : iter->second)
			if (!callback(records.at(id)))
				return;
}

template <typename Callback>
void Database::AllByUser(const string &user, Callback callback) const {
	if (auto iter = user_ids.find(user); iter != user_ids.end())
		for (const auto &id : iter->second)
			if (!callback(records.at(id)))
				return;
}
#endif //MINE

#ifdef GITHUB //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week1/06%20Programming%20Assignment/solution.cpp
class Database {
	template<typename Type>
	using Index = multimap<Type, const Record *>;

	struct Data {
		Record record;
		Index<int>::iterator timestamp_iter; //TEST!
		Index<int>::iterator karma_iter;
		Index<string>::iterator user_iter;
	};
	/*
	Do the references to the items of the std::unordered_map remain valid (reference invalidation)?

	In C++, references to items in an `std::unordered_map` can become invalidated under certain conditions. Here’s a detailed explanation of reference invalidation in the context of `std::unordered_map`:

	## Reference Invalidation in `std::unordered_map`

	### Valid References
	- **Insertion**: Adding new elements to an `std::unordered_map` does not invalidate existing references, iterators, or pointers to elements. This is because the underlying structure allows for dynamic resizing without affecting the existing elements.
	- **Access**: References to existing elements remain valid as long as those elements are not erased or the map is not rehashed.

	### Invalid References
	- **Erasure**: If an element is removed from the `std::unordered_map`, any references, iterators, or pointers to that element become invalid. This is a critical point to consider when managing references in your code.
	- **Rehashing**: When the load factor of the `std::unordered_map` exceeds its maximum threshold, it will rehash its contents to a larger bucket array. During this process, all references, iterators, and pointers to elements are invalidated. This includes references to elements that were not directly affected by the rehashing.

	### Summary
	To maintain valid references while using `std::unordered_map`, be cautious about:
	1. **Avoiding erasure** of elements if you need to keep references valid.
	2. **Monitoring capacity changes**: If you expect that many insertions may occur, consider reserving space in advance using `reserve()` to minimize the risk of rehashing.

	Understanding these behaviors is essential for writing robust C++ code that utilizes `std::unordered_map`.
	*/

	unordered_map<string, Data> storage;
	Index<int> timestamp_index; //TEST!
	Index<int> karma_index;
	Index<string> user_index;
public:
	bool Put(const Record &record) {
		auto [it, inserted] = storage.insert(
			{record.id, Data {record, {}, {}, {}}}
		);
		if (!inserted) {
			return false;
		}
		auto &data = it->second;
		const Record *ptr = &data.record;
		data.timestamp_iter = timestamp_index.insert({record.timestamp, ptr}); //TEST!
		data.karma_iter = karma_index.insert({record.karma, ptr});
		data.user_iter = user_index.insert({record.user, ptr});
		return true;
	}

	const Record *GetById(const string &id) const {
		auto it = storage.find(id);
		if (it == storage.end()) {
			return nullptr;
		}
		return &it->second.record;
	}

	bool Erase(const string &id) {
		auto it = storage.find(id);
		if (it == storage.end()) {
			return false;
		}
		const auto &data = it->second;
		timestamp_index.erase(data.timestamp_iter);
		karma_index.erase(data.karma_iter);
		user_index.erase(data.user_iter);
		storage.erase(it);
		return true;
	}

	template<typename Callback>
	void RangeByTimestamp(int low, int high, Callback callback) const {
		auto it_begin = timestamp_index.lower_bound(low); //TEST!
		auto it_end = timestamp_index.upper_bound(high);
		for (auto it = it_begin; it != it_end; ++it) {
			if (!callback(*it->second)) {
				break;
			}
		}
	}

	template<typename Callback>
	void RangeByKarma(int low, int high, Callback callback) const { //TO DO: Create a single template function for this and the above one.
		auto it_begin = karma_index.lower_bound(low);
		auto it_end = karma_index.upper_bound(high);
		for (auto it = it_begin; it != it_end; ++it) {
			if (!callback(*it->second)) {
				break;
			}
		}
	}

	template<typename Callback>
	void AllByUser(const string &user, Callback callback) const {
		auto [it_begin, it_end] = user_index.equal_range(user);
		for (auto it = it_begin; it != it_end; ++it) {
			if (!callback(*it->second)) {
				break;
			}
		}
	}
};
/*
The line
auto it_begin = timestamp_index.lower_bound(low);
relies on unordered_map items' pointers' validity. Is the pointer invalidation not an issue here ever?

The code you've provided implements a simple database using C++ structures, including `unordered_map` and `multimap`. Your concern about pointer
validity when using `unordered_map` and `multimap` is valid, especially regarding how data is managed during insertions and deletions.

### Pointer Validity in the Context of Your Database

1. * *Pointer Invalidation * *:
-When you store a pointer to a `Record` in the `multimap`, you must ensure that the `Record` remains valid for as long as the pointer is used.
In your implementation, the pointer is obtained from the `Data` structure which contains the `Record`. If the `Record` is modified or if its
containing `Data` is erased from the `unordered_map`, the pointer will become invalid.
- Specifically, in your `Erase` function, when you remove an entry from the `storage`, you also erase entries from your index
maps(`timestamp_index`, `karma_index`, and `user_index`).This means that any pointers pointing to that erased `Record` will now be dangling
pointers.

	2. * *Multimap Behavior * *:
-The iterators returned by `multimap::insert` are valid until either the element they point to is removed or the map itself is modified in a way
that affects that element(e.g., erasing it).However, since you are storing pointers to elements that may be erased, this can lead to invalid
access.

### Recommendations for Improvement

To ensure pointer validity and improve performance, consider the following suggestions :

#### 1. Use Smart Pointers
Instead of using raw pointers, consider using smart pointers(e.g., `shared_ptr<Record>` or `unique_ptr<Record>`) for managing the
lifetime of your records. This will help avoid dangling pointers and manage memory more effectively.

	```cpp
#include <memory>

	struct Data {
	shared_ptr<Record> record; // Use shared_ptr for automatic memory management
	Index<int>::iterator timestamp_iter;
	Index<int>::iterator karma_iter;
	Index<string>::iterator user_iter;
};
```

#### 2. Store Records in a Container
Instead of storing records directly in the `Data` structure, consider keeping all records in a separate container(like a vector) and store indices
or references in your maps. This way, you can manage the lifetime of records more effectively.

```cpp
class Database {
	vector<Record> records; // Store records here
	unordered_map<string, size_t> storage; // Map IDs to indices in records
	// Other members remain unchanged...

public:
	bool Put(const Record &record) {
		records.push_back(record); // Add record to vector
		size_t index = records.size() - 1; // Get index of new record
		storage[record.id] = index; // Map ID to index

		// Insert into indexes...
		return true;
	}

	const Record *GetById(const string &id) const {
		auto it = storage.find(id);
		if (it == storage.end()) {
			return nullptr;
		}
		return &records[it->second]; // Return pointer to record in vector
	}

	bool Erase(const string &id) {
		auto it = storage.find(id);
		if (it == storage.end()) {
			return false;
		}
		size_t index = it->second;

		// Remove from indexes...

		storage.erase(it);
		return true;
	}
};
```

#### 3. Optimize Iteration Over Indexes
If you frequently perform range queries, ensure that your indexes are optimized for those operations. Consider using data structures that provide
better performance for range queries if necessary.

### Conclusion

By addressing pointer validity through smart pointers or by restructuring how you store records, you can significantly enhance both safety and
maintainability of your code. Additionally, optimizing data structures based on usage patterns will further improve performance.
*/
#endif //GITHUB