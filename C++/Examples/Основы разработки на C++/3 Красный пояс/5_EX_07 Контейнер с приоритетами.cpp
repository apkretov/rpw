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
	Id Add(T object); // Добавить объект с нулевым приоритетом с помощью перемещения и вернуть его идентификатор
	template <typename ObjInputIt, typename IdOutputIt> void Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt ids_begin); // Добавить все элементы диапазона [range_begin, range_end) с помощью перемещения, записав выданные им идентификаторы в диапазон [ids_begin, ...)
	bool IsValid(Id id) const; // Определить, принадлежит ли идентификатор какому-либо хранящемуся в контейнере объекту
	const T &Get(Id id) const; // Получить объект по идентификатору
	void Promote(Id id); // Увеличить приоритет объекта на 1
	pair<const T &, int> GetMax() const; // Получить объект с максимальным приоритетом и его приоритет
	pair<T, int> PopMax(); // Аналогично GetMax, но удаляет элемент из контейнера
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
	using string::string;  // Позволяет использовать конструкторы строки
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

// При наличии нескольких элементов с одинаковым максимальным приоритетом необходимо выбирать и извлекать тот, который был добавлен позже остальных.
// Custom Comparators : If you require a stable ordering for elements with equal priority (i.e., maintaining their insertion order), you can 
// implement a custom comparator that includes an additional identifier(like a counter) to break ties based on insertion order. For example, you 
// could modify your data structure to include an index that increments with each insertion.

//Контейнер с приоритетами
//Условие
//
//Реализуйте шаблонный контейнер PriorityCollection, позволяющий хранить объекты некопируемого типа, а также совершать с ними следующие операции:
//
//	добавить элемент с нулевым приоритетом;
//	добавить набор элементов с нулевыми приоритетами;
//	увеличить на 1 приоритет заданного элемента;
//	извлечь из контейнера элемент с максимальным приоритетом.
//
//Поскольку добавление элемента заключается в его перемещении в контейнер, метод увеличения приоритета не может принимать сам элемент. Поэтому метод, добавляющий элементы, для каждого из них должен вернуть некий идентификатор, который затем можно использовать для вызова других методов.
//
//Тип идентификатора — PriorityCollection::Id — вы должны выбрать самостоятельно. Он должен быть легко копируемым: например, числом, указателем или итератором. Примеры определения и использования типа Id вы можете найти в шаблоне решения.
//
//template <typename T>
//class PriorityCollection {
//public:
//  using Id = /* тип, используемый для идентификаторов */;
//
//  // Добавить объект с нулевым приоритетом
//  // с помощью перемещения и вернуть его идентификатор
//  Id Add(T object);
//
//  // Добавить все элементы диапазона [range_begin, range_end)
//  // с помощью перемещения, записав выданные им идентификаторы
//  // в диапазон [ids_begin, ...)
//  template <typename ObjInputIt, typename IdOutputIt>
//  void Add(ObjInputIt range_begin, ObjInputIt range_end,
//	  IdOutputIt ids_begin);
//
//  // Определить, принадлежит ли идентификатор какому-либо
//  // хранящемуся в контейнере объекту
//  bool IsValid(Id id) const;
//
//  // Получить объект по идентификатору
//  const T &Get(Id id) const;
//
//  // Увеличить приоритет объекта на 1
//  void Promote(Id id);
//
//  // Получить объект с максимальным приоритетом и его приоритет
//  pair<const T &, int> GetMax() const;
//
//  // Аналогично GetMax, но удаляет элемент из контейнера
//  pair<T, int> PopMax();
//
//private:
//	// Приватные поля и методы
//};
//
//Гарантии
//
//Вы можете полагаться на то, что для элементов типа T определены перемещение и сравнение на == , != и < .Все операции над элементами имеют константную сложность.
//	Гарантируется, что все добавляемые элементы различны, однако добавленный и затем извлечённый элемент может быть добавлен вновь.
//	Методы Get и Promote всегда вызываются от валидных с точки зрения метода IsValid идентификаторов.
//	Методы GetMax и PopMax вызываются только при наличии элементов в контейнере.
//	При наличии нескольких элементов с одинаковым максимальным приоритетом необходимо выбирать и извлекать тот, который был добавлен позже остальных.
//
//	Файл с заготовкой решения
//
//	priority_collection_2.cpp
//	Ограничения
//
//	Контейнер должен обрабатывать 10 ^ 6 запросов не более чем за 1 секунду.Гарантируется, что суммарная длина диапазонов, с которыми вызывается вторая версия метода Add, также не превосходит 10 ^ 6.
//	Подсказки
//
//	Если задача вызывает непреодолимые трудности, вы можете воспользоваться подсказками.Они помогут быстрее сдать задачу, но в итоге вы получите меньше пользы от процесса поиска решения.
//
//	Не нужно открывать все подсказки сразу.Используйте их последовательно.
//
//	priority - collection - 1.pdf
//
//	priority - collection - 2.pdf
//
//	priority - collection - 3.pdf
//
//	priority - collection - 4.pdf
