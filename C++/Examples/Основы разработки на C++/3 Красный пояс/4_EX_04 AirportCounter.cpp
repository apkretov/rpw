#if 0 //@ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/tree/main/Week_4/04%20Programming%20Assignment

#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <vector>
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

#ifndef MINE
template <typename TAirport> //TEST! // TAirport should be enum with sequential items and last item TAirport::Last_
class AirportCounter {
public:
	AirportCounter() = default; // конструктор по умолчанию: список элементов пока пуст

	template <typename TIterator> // конструктор от диапазона элементов типа TAirport
	AirportCounter(TIterator begin, TIterator end) { //TO DO: Clean Code.
		for (auto it = begin; it != end; ++it)
			++airports.at(static_cast<size_t>(*it));
	}

	size_t Get(TAirport airport) const { // получить количество элементов, равных данному
		return airports.at(static_cast<size_t>(airport));
	}

	void Insert(TAirport airport) {// добавить данный элемент
		++airports.at(static_cast<size_t>(airport));
	}

	void EraseOne(TAirport airport) { // удалить одно вхождение данного элемента
		if (airports.at(static_cast<size_t>(airport)) > 0) //TO DO: airports.at(airport) is called twice. Is a temporary variable needed or does the compiler optimizes this?
			--airports.at(static_cast<size_t>(airport));
	}

	void EraseAll(TAirport airport) { // удалить все вхождения данного элемента
		airports.at(static_cast<size_t>(airport)) = 0;
	}

	using Item = pair<TAirport, size_t>;
	using Items = array<Item, static_cast<size_t>(TAirport::Last_)>;
	Items GetItems() const { // получить некоторый объект, по которому можно проитерироваться, получив набор объектов типа Item - пар (аэропорт, количество), упорядоченных по аэропорту
		Items items;
		for (size_t i = 0; i < static_cast<size_t>(TAirport::Last_); ++i)
			items.at(i) = {static_cast<TAirport>(i), airports.at(i)};
		return items;
	}
private:
	array<size_t, static_cast<size_t>(TAirport::Last_)> airports{};
};

/*
File: C:\_\My_Docs\Misc\Projects\C++\Основы разработки на C++\3 Красный пояс\4_EX_04 AirportCounter.cpp Line : 208

Total tests duration : measuring duration started...
TestMoscow : measuring duration started...
TestMoscow : execution time = 3 milliseconds
TestMoscow OK
TestManyConstructions : measuring duration started...
TestManyConstructions : execution time = 18 558 milliseconds
TestManyConstructions OK
TestManyGetItems : measuring duration started...
TestManyGetItems : execution time = 31 186 milliseconds
TestManyGetItems OK
TestMostPopularAirport : measuring duration started...
TestMostPopularAirport : execution time = 4 207 milliseconds
TestMostPopularAirport OK
Total tests duration : execution time = 53 987 milliseconds

C : \_\My_Docs\Misc\Projects\C++\Основы разработки на C++\x64\Debug\3 Красный пояс.exe(process 13340) exited with code 0 (0x0).
Press any key to close this window . . .
*/

#else //GITHUB @ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/blob/main/Week_4/04%20Programming%20Assignment/Solution/airport_counter.cpp
template <typename TAirport>
class AirportCounter {
public:
	static const size_t SIZE = static_cast<size_t>(TAirport::Last_); //TEST!
	using Item = std::pair<TAirport, size_t>;
	using Items = std::array<Item, SIZE>;
public:
	AirportCounter();
	template <typename TIterator>
	AirportCounter(TIterator begin, TIterator end);

	size_t Get(TAirport airport) const;
	void Insert(TAirport airport);

	void EraseOne(TAirport airport);
	void EraseAll(TAirport airport);

	Items GetItems() const;
private:
	std::array<size_t, SIZE> airports;
};

template <typename TAirport>
AirportCounter<TAirport>::AirportCounter() {
	airports.fill(0); //TEST //																																	MINE This degrades performance.
}

template <typename TAirport>
template <typename TIterator>
AirportCounter<TAirport>::AirportCounter(TIterator begin, TIterator end) {
	airports.fill(0); //TEST //																																	MINE This degrades performance.
	while (begin != end) {
		Insert(*begin);
		begin++;
	}
}

template <typename TAirport>
size_t AirportCounter<TAirport>::Get(TAirport airport) const {
	return airports[static_cast<size_t>(airport)];
}

template <typename TAirport>
void AirportCounter<TAirport>::Insert(TAirport airport) {
	++airports[static_cast<size_t>(airport)];
}

template <typename TAirport>
void AirportCounter<TAirport>::EraseOne(TAirport airport) {
	--airports[static_cast<size_t>(airport)];
}

template <typename TAirport>
void AirportCounter<TAirport>::EraseAll(TAirport airport) {
	airports[static_cast<size_t>(airport)] = 0;
}

template <typename TAirport>
typename AirportCounter<TAirport>::Items AirportCounter<TAirport>::GetItems() const {
	Items items;
	for (size_t i = 0; i < airports.size(); ++i) {
		items[i] = {static_cast<TAirport>(i), airports[i]};
	}
	return items;
}

/*
File: C:\_\My_Docs\Misc\Projects\C++\Основы разработки на C++\3 Красный пояс\4_EX_04 AirportCounter - Mine.cpp  Line : 296

Total tests duration : measuring duration started...
TestMoscow : measuring duration started...
TestMoscow : execution time = 3 milliseconds
TestMoscow OK
TestManyConstructions : measuring duration started...
TestManyConstructions : execution time = 29 936 milliseconds
TestManyConstructions OK
TestManyGetItems : measuring duration started...
TestManyGetItems : execution time = 44 851 milliseconds
TestManyGetItems OK
TestMostPopularAirport : measuring duration started...
TestMostPopularAirport : execution time = 4 385 milliseconds
TestMostPopularAirport OK
Total tests duration : execution time = 79 218 milliseconds

C : \_\My_Docs\Misc\Projects\C++\Основы разработки на C++\x64\Debug\3 Красный пояс.exe(process 14060) exited with code 0 (0x0).
Press any key to close this window . . .
*/
#endif //GITHUB

void TestMoscow() {
	LOG_DURATION(__func__);

	enum class MoscowAirport {
		VKO,
		SVO,
		DME,
		ZIA,
		Last_
	};

	const vector<MoscowAirport> airports = {
		MoscowAirport::SVO,
		MoscowAirport::VKO,
		MoscowAirport::ZIA,
		MoscowAirport::SVO,
	};
	AirportCounter<MoscowAirport> airport_counter(begin(airports), end(airports));

	ASSERT_EQUAL(airport_counter.Get(MoscowAirport::VKO), 1);
	ASSERT_EQUAL(airport_counter.Get(MoscowAirport::SVO), 2);
	ASSERT_EQUAL(airport_counter.Get(MoscowAirport::DME), 0);
	ASSERT_EQUAL(airport_counter.Get(MoscowAirport::ZIA), 1);

	using Item = AirportCounter<MoscowAirport>::Item;
	vector<Item> items;
	for (const auto &item : airport_counter.GetItems()) {
		items.push_back(item);
	}
	ASSERT_EQUAL(items.size(), 4);

#define ASSERT_EQUAL_ITEM(idx, expected_enum, expected_count) \
  do { \
    ASSERT_EQUAL(static_cast<size_t>(items[idx].first), static_cast<size_t>(MoscowAirport::expected_enum)); \
    ASSERT_EQUAL(items[idx].second, expected_count); \
  } while (false)

	ASSERT_EQUAL_ITEM(0, VKO, 1);
	ASSERT_EQUAL_ITEM(1, SVO, 2);
	ASSERT_EQUAL_ITEM(2, DME, 0);
	ASSERT_EQUAL_ITEM(3, ZIA, 1);

	airport_counter.Insert(MoscowAirport::VKO);
	ASSERT_EQUAL(airport_counter.Get(MoscowAirport::VKO), 2);

	airport_counter.EraseOne(MoscowAirport::SVO);
	ASSERT_EQUAL(airport_counter.Get(MoscowAirport::SVO), 1);

	airport_counter.EraseAll(MoscowAirport::VKO);
	ASSERT_EQUAL(airport_counter.Get(MoscowAirport::VKO), 0);
}

enum class SmallCountryAirports {
	Airport_1,
	Airport_2,
	Airport_3,
	Airport_4,
	Airport_5,
	Airport_6,
	Airport_7,
	Airport_8,
	Airport_9,
	Airport_10,
	Airport_11,
	Airport_12,
	Airport_13,
	Airport_14,
	Airport_15,
	Last_
};

void TestManyConstructions() {
	LOG_DURATION(__func__);

	default_random_engine rnd(20180623);
	uniform_int_distribution<size_t> gen_airport(
		0, static_cast<size_t>(SmallCountryAirports::Last_) - 1
	);

	array<SmallCountryAirports, 2> airports;
	for (auto &x : airports) {
		x = static_cast<SmallCountryAirports>(gen_airport(rnd));
	}

	uint64_t total = 0;
	for (int step = 0; step < 100'000'000; ++step) {
		AirportCounter<SmallCountryAirports> counter(begin(airports), end(airports));
		total += counter.Get(SmallCountryAirports::Airport_1);
	}
	ASSERT(total < 1000); // Assert to use variable total so that compiler doesn't optimize it out
}

enum class SmallTownAirports {
	Airport_1,
	Airport_2,
	Last_
};

void TestManyGetItems() {
	LOG_DURATION(__func__);

	default_random_engine rnd(20180701);
	uniform_int_distribution<size_t> gen_airport(
		0, static_cast<size_t>(SmallTownAirports::Last_) - 1
	);

	array<SmallTownAirports, 2> airports;
	for (auto &x : airports) {
		x = static_cast<SmallTownAirports>(gen_airport(rnd));
	}

	uint64_t total = 0;
	for (int step = 0; step < 100'000'000; ++step) {
		AirportCounter<SmallTownAirports> counter(begin(airports), end(airports));
		total += counter.Get(SmallTownAirports::Airport_1);
		for (const auto [airport, count] : counter.GetItems()) {
			total += count;
		}
	}
	ASSERT(total > 0); // Assert to use variable total so that compiler doesn't optimize it out
}

void TestMostPopularAirport() {
	LOG_DURATION(__func__);

	default_random_engine rnd(20180624);
	uniform_int_distribution<size_t> gen_airport(0, static_cast<size_t>(SmallCountryAirports::Last_) - 1);

	array<pair<SmallCountryAirports, SmallCountryAirports>, 1000> dayly_flight_report;
	for (auto &x : dayly_flight_report) {
		x = {
		  static_cast<SmallCountryAirports>(gen_airport(rnd)),
		  static_cast<SmallCountryAirports>(gen_airport(rnd))
		};
	}

	const int days_to_explore = 365 * 500;
	vector<SmallCountryAirports> most_popular(days_to_explore);
	for (int day = 0; day < days_to_explore; ++day) {
		AirportCounter<SmallCountryAirports> counter;
		for (const auto &[source, dest] : dayly_flight_report) {
			counter.Insert(source);
			counter.Insert(dest);
		}

		const auto items = counter.GetItems();
		most_popular[day] = max_element(begin(items), end(items), [](auto lhs, auto rhs) { return lhs.second < rhs.second; })->first;
	}

	ASSERT(all_of(begin(most_popular), end(most_popular), [&](SmallCountryAirports a) {	return a == most_popular.front(); }));
}

int main() {
	PRINT_FILE_LINE();

	TestRunner tr;
	LOG_DURATION("Total tests duration"); // По условию, суммарное время работы всех тестов не должно превышать двух секунд. Если ваше время будет лишь чуть больше двух секунд, попробуйте отправить ваше решение в тестирующую систему. Возможно, там более мощное железо, и ваше решение будет принято.
	RUN_TEST(tr, TestMoscow);			  // Кроме того, не забудьте включить оптимизации при компиляции кода.
	RUN_TEST(tr, TestManyConstructions);
	RUN_TEST(tr, TestManyGetItems);
	RUN_TEST(tr, TestMostPopularAirport);

	return 0;
}
#endif //1

/*
AirportCounter
Условие

Вам необходимо разработать простейшую систему сбора статистики вылетов для небольших авиакомпаний. Высокоуровневые требования выглядят следующим образом:

	Система сбора статистики должна представлять собой класс AirportCounter, умеющий в произвольный момент времени для заданного аэропорта вернуть текущее количество вылетов из него.
	Набор возможных аэропортов фиксирован в виде enum и потому не может изменяться в рамках одного сеанса работы системы статистики, то есть в рамках одного экземпляра AirportCounter. Таким образом, класс AirportCounter необходимо шаблонизировать типом этого enum: если назвать такой enum TAirport, получим шаблонный класс AirportCounter.
	Гарантируется (по крайней мере, обещано заказчиком), что по enum аэропортов можно будет легко определить количество элементов в нём, а также перебрать сами элементы. А именно, любой используемый enum будет иметь вид enum class SomeCityAirport { Airport1, Airport2, ..., AirportN, Last_ };, то есть будет содержать некоторое количество элементов-аэропортов и элемент Last_ в качестве последнего. Поскольку в этом enum не будут заданы числовые значения для элементов, можно полагаться на то, что они будут пронумерованы подряд от 0 до N-1, а выражение static_cast<uint32_t>(SomeCityAirport::Last_) будет содержать количество аэропортов (N).
	Класс должен уметь конструироваться по списку аэропортов вылета, а также позволять обновлять этот список: добавить вылет из какого-то аэропорта, удалить один вылет (например, ошибочно добавленный) или удалить из истории все вылеты из некоторого аэропорта.

Тестирование

Прежде чем перейти к более детальному описанию интерфейса класса, опишем процесс тестирования задачи.

Вам будут даны все тесты, на которых будет проверяться шаблонный класс AirportCounter. Ваша задача — добиться не только корректной работы на этих тестах, но и уложиться на них в 2 секунды. (Считайте, что заказчик предоставил вам подробнейшие сценарии использования вашего класса, которые затем были преобразованы в конкретные бенчмарки.)

Таким образом, вы должны выбрать способ реализации класса, ориентируясь лишь на конкретные бенчмарки.

Отметим, что данные бенчмарки составлены на основе реального примера из высоконагруженного сервиса, замедление которого даже на десятки процентов недопустимо. Именно поэтому в этой задаче важно не только спроектировать решение с приемлемой асимптотической сложностью, но и «разогнать» его на конкретных примерах.

template <typename TAirport>
class AirportCounter {
public:
  // конструктор по умолчанию: список элементов пока пуст
  AirportCounter();

  // конструктор от диапазона элементов типа TAirport
  template <typename TIterator>
  AirportCounter(TIterator begin, TIterator end);

  // получить количество элементов, равных данному
  size_t Get(TAirport airport) const;

  // добавить данный элемент
  void Insert(TAirport airport);

  // удалить одно вхождение данного элемента
  void EraseOne(TAirport airport);

  // удалить все вхождения данного элемента
  void EraseAll(TAirport airport);

  using Item = pair<TAirport, size_t>;

  // получить некоторый объект, по которому можно проитерироваться,
  // получив набор объектов типа Item - пар (аэропорт, количество),
  // упорядоченных по аэропорту
  ??? GetItems() const;

private:
  // ???
};

Файл с заготовкой решения и тестами

airport_counter.cpp
Подсказки

Если задача вызывает непреодолимые трудности, вы можете воспользоваться подсказками. Они помогут быстрее сдать задачу, но в итоге вы получите меньше пользы от процесса поиска решения.

Не нужно открывать все подсказки сразу. Используйте их последовательно.

airport-counter-1.pdf

airport-counter-2.pdf
*/