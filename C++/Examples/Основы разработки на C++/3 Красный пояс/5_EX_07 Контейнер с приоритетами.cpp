#if 0 //@ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/tree/main/Week_5/07%20Programming%20Assignment

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

#ifdef MINE
template <typename T>
class PriorityCollection {
public:
	using Id = size_t;
	Id Add(T object); // �������� ������ � ������� ����������� � ������� ����������� � ������� ��� �������������
	template <typename ObjInputIt, typename IdOutputIt> void Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt ids_begin); // �������� ��� �������� ��������� [range_begin, range_end) � ������� �����������, ������� �������� �� �������������� � �������� [ids_begin, ...)
	bool IsValid(Id id) const; // ����������, ����������� �� ������������� ������-���� ����������� � ���������� �������
	const T &Get(Id id) const; // �������� ������ �� ��������������
	void Promote(Id id); // ��������� ��������� ������� �� 1
	pair<const T &, int> GetMax() const; // �������� ������ � ������������ ����������� � ��� ���������
	pair<T, int> PopMax(); // ���������� GetMax, �� ������� ������� �� ����������
private:
	static Id IdGenerator;
	map<Id, pair<T, int>> objects;

	struct priority_Id_order {
		bool operator()(const pair<int, Id> &lhs, const pair<int, Id> &rhs) const {
			if (lhs.first != rhs.first)
				return lhs.first > rhs.first;
			return lhs.second > rhs.second;
		}
	};
	set<pair<int, Id>, priority_Id_order> priorities;

};

template <typename T>
typename PriorityCollection<T>::Id PriorityCollection<T>::IdGenerator{};
#endif //MINE

#ifndef GITHUB //@ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/blob/main/Week_5/07%20Programming%20Assignment/Solution/priority_collection.cpp
template <typename T>
class PriorityCollection {
public:
	using Id = size_t;

	Id Add(T object);
	template <typename ObjInputIt, typename IdOutputIt>
	void Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt ids_begin);

	bool IsValid(Id id) const;
	const T &Get(Id id) const;
	void Promote(Id id);
	pair<const T &, int> GetMax() const;
	pair<T, int> PopMax();
private:
	int id = 0;
	set<pair<int, Id>> sorted_objects;
	vector<pair<T, int>> objects;
};

template <typename T>
typename PriorityCollection<T>::Id PriorityCollection<T>::Add(T object) {
	sorted_objects.emplace(0, id);
	objects.emplace_back(move(object), 0);
	return Id(id++);
}

template <typename T>
template <typename ObjInputIt, typename IdOutputIt>
void PriorityCollection<T>::Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt ids_begin) {
	while (range_begin != range_end) *ids_begin++ = Add(move(*range_begin++));
}

template <typename T>
bool PriorityCollection<T>::IsValid(Id id) const {
	return objects[id].second >= 0;
}

template <typename T>
const T &PriorityCollection<T>::Get(Id id) const {
	return objects[id].first;
}

template <typename T>
void PriorityCollection<T>::Promote(Id id) {
	auto new_priority = objects[id].second++;
	auto old_priority = new_priority++;
	sorted_objects.erase({old_priority, id});
	sorted_objects.insert({new_priority, id});
}

template <typename T>
pair<const T &, int> PriorityCollection<T>::GetMax() const {
	return objects[prev(end(sorted_objects))->second];
}

template <typename T>
pair<T, int> PriorityCollection<T>::PopMax() {
	auto id = prev(end(sorted_objects))->second;
	auto result = move(objects[id]);
	sorted_objects.erase({result.second, id});
	objects[id] = {T(), -1};
	return result;
}
#endif //GITHUB


class StringNonCopyable : public string {
public:
	using string::string;  // ��������� ������������ ������������ ������
	StringNonCopyable(const StringNonCopyable &) = delete;
	StringNonCopyable(StringNonCopyable &&) = default;
	StringNonCopyable &operator=(const StringNonCopyable &) = delete;
	StringNonCopyable &operator=(StringNonCopyable &&) = default;
};

void TestNoCopy() {
	PriorityCollection<StringNonCopyable> strings;
	const auto white_id = strings.Add("white");
	const auto yellow_id = strings.Add("yellow");
	const auto red_id = strings.Add("red");

	strings.Promote(yellow_id); // yellow_id -> 1
	for (int i = 0; i < 2; ++i) // red_id -> 2
		strings.Promote(red_id);
	strings.Promote(yellow_id); // yellow_id -> 2
	{
		const auto item = strings.PopMax(); // No red.
		ASSERT_EQUAL(item.first, "red");
		ASSERT_EQUAL(item.second, 2);
	}
	{
		const auto item = strings.PopMax(); // No yellow.
		ASSERT_EQUAL(item.first, "yellow");
		ASSERT_EQUAL(item.second, 2);
	}
	{
		const auto item = strings.PopMax(); // No white.
		ASSERT_EQUAL(item.first, "white");
		ASSERT_EQUAL(item.second, 0);
	}
}

int main() {
	PRINT_FILE_LINE();

	TestRunner tr;
	RUN_TEST(tr, TestNoCopy);
	return 0;
}
#endif //1

// ��� ������� ���������� ��������� � ���������� ������������ ����������� ���������� �������� � ��������� ���, ������� ��� �������� ����� ���������.
// Custom Comparators : If you require a stable ordering for elements with equal priority (i.e., maintaining their insertion order), you can 
// implement a custom comparator that includes an additional identifier(like a counter) to break ties based on insertion order. For example, you 
// could modify your data structure to include an index that increments with each insertion.

//��������� � ������������
//�������
//
//���������� ��������� ��������� PriorityCollection, ����������� ������� ������� ������������� ����, � ����� ��������� � ���� ��������� ��������:
//
//	�������� ������� � ������� �����������;
//	�������� ����� ��������� � �������� ������������;
//	��������� �� 1 ��������� ��������� ��������;
//	������� �� ���������� ������� � ������������ �����������.
//
//��������� ���������� �������� ����������� � ��� ����������� � ���������, ����� ���������� ���������� �� ����� ��������� ��� �������. ������� �����, ����������� ��������, ��� ������� �� ��� ������ ������� ����� �������������, ������� ����� ����� ������������ ��� ������ ������ �������.
//
//��� �������������� � PriorityCollection::Id � �� ������ ������� ��������������. �� ������ ���� ����� ����������: ��������, ������, ���������� ��� ����������. ������� ����������� � ������������� ���� Id �� ������ ����� � ������� �������.
//
//template <typename T>
//class PriorityCollection {
//public:
//  using Id = /* ���, ������������ ��� ��������������� */;
//
//  // �������� ������ � ������� �����������
//  // � ������� ����������� � ������� ��� �������������
//  Id Add(T object);
//
//  // �������� ��� �������� ��������� [range_begin, range_end)
//  // � ������� �����������, ������� �������� �� ��������������
//  // � �������� [ids_begin, ...)
//  template <typename ObjInputIt, typename IdOutputIt>
//  void Add(ObjInputIt range_begin, ObjInputIt range_end,
//	  IdOutputIt ids_begin);
//
//  // ����������, ����������� �� ������������� ������-����
//  // ����������� � ���������� �������
//  bool IsValid(Id id) const;
//
//  // �������� ������ �� ��������������
//  const T &Get(Id id) const;
//
//  // ��������� ��������� ������� �� 1
//  void Promote(Id id);
//
//  // �������� ������ � ������������ ����������� � ��� ���������
//  pair<const T &, int> GetMax() const;
//
//  // ���������� GetMax, �� ������� ������� �� ����������
//  pair<T, int> PopMax();
//
//private:
//	// ��������� ���� � ������
//};
//
//��������
//
//�� ������ ���������� �� ��, ��� ��� ��������� ���� T ���������� ����������� � ��������� �� == , != � < .��� �������� ��� ���������� ����� ����������� ���������.
//	�������������, ��� ��� ����������� �������� ��������, ������ ����������� � ����� ����������� ������� ����� ���� �������� �����.
//	������ Get � Promote ������ ���������� �� �������� � ����� ������ ������ IsValid ���������������.
//	������ GetMax � PopMax ���������� ������ ��� ������� ��������� � ����������.
//	��� ������� ���������� ��������� � ���������� ������������ ����������� ���������� �������� � ��������� ���, ������� ��� �������� ����� ���������.
//
//	���� � ���������� �������
//
//	priority_collection_2.cpp
//	�����������
//
//	��������� ������ ������������ 10 ^ 6 �������� �� ����� ��� �� 1 �������.�������������, ��� ��������� ����� ����������, � �������� ���������� ������ ������ ������ Add, ����� �� ����������� 10 ^ 6.
//	���������
//
//	���� ������ �������� ������������� ���������, �� ������ ��������������� �����������.��� ������� ������� ����� ������, �� � ����� �� �������� ������ ������ �� �������� ������ �������.
//
//	�� ����� ��������� ��� ��������� �����.����������� �� ���������������.
//
//	priority - collection - 1.pdf
//
//	priority - collection - 2.pdf
//
//	priority - collection - 3.pdf
//
//	priority - collection - 4.pdf
