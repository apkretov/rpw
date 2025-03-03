#if 0 //@ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/tree/main/Week_4/02%20Practice%20Programming%20Assignment

#include <array>
#include <iostream>
#include <random>
#include <stdexcept>
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

template <typename T, size_t N> //@ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/blob/main/Week_4/02%20Practice%20Programming%20Assignment/Solution/stack_vector.h
class StackVector {
public:
	explicit StackVector(size_t a_size = 0);

	T &operator[](size_t index);
	const T &operator[](size_t index) const;

	auto begin();
	auto end();
	auto begin() const;
	auto end() const;

	size_t Size() const;
	size_t Capacity() const;

	void PushBack(const T &value);
	T PopBack();
private:
	std::array<T, N> data;
	size_t size;
};

template <typename T, size_t N>
StackVector<T, N>::StackVector(size_t a_size) : size(a_size) {
	if (size > N) throw std::invalid_argument("Too much");
}

template <typename T, size_t N>
T &StackVector<T, N>::operator[](size_t index) {
	return data[index];
}

template <typename T, size_t N>
const T &StackVector<T, N>::operator[](size_t index) const {
	return data[index];
}

template <typename T, size_t N>
auto StackVector<T, N>::begin() {
	return data.begin();
}

template <typename T, size_t N>
auto StackVector<T, N>::end() {
	return data.begin() + size;
}

template <typename T, size_t N>
auto StackVector<T, N>::begin() const {
	return data.begin();
}

template <typename T, size_t N>
auto StackVector<T, N>::end() const {
	return data.begin() + size;
}

template <typename T, size_t N>
size_t StackVector<T, N>::Size() const {
	return size;
}

template <typename T, size_t N>
size_t StackVector<T, N>::Capacity() const {
	return data.size();
}

template <typename T, size_t N>
void StackVector<T, N>::PushBack(const T &value) {
	if (size == data.size()) {
		throw std::overflow_error("Full");
	}
	data[size++] = value;
}

template <typename T, size_t N>
T StackVector<T, N>::PopBack() {
	if (size == 0) {
		throw std::underflow_error("Empty");
	}
	--size;
	return data[size];
}

void TestConstruction() {
	StackVector<int, 10> v;
	ASSERT_EQUAL(v.Size(), 0u);
	ASSERT_EQUAL(v.Capacity(), 10u);

	StackVector<int, 8> u(5);
	ASSERT_EQUAL(u.Size(), 5u);
	ASSERT_EQUAL(u.Capacity(), 8u);

	try {
		StackVector<int, 10> u(50);
		Assert(false, "Expect invalid_argument for too large size");
	}
	catch (invalid_argument &) {
	}
	catch (...) {
		Assert(false, "Unexpected exception for too large size");
	}
}

void TestPushBack() {
	StackVector<int, 5> v;
	for (size_t i = 0; i < v.Capacity(); ++i) {
		v.PushBack(i);
	}

	try {
		v.PushBack(0);
		Assert(false, "Expect overflow_error for PushBack in full vector");
	}
	catch (overflow_error &) {
	}
	catch (...) {
		Assert(false, "Unexpected exception for PushBack in full vector");
	}
}

void TestPopBack() {
	StackVector<int, 5> v;
	for (size_t i = 1; i <= v.Capacity(); ++i) {
		v.PushBack(i);
	}
	for (int i = v.Size(); i > 0; --i) {
		ASSERT_EQUAL(v.PopBack(), i);
	}

	try {
		v.PopBack();
		Assert(false, "Expect underflow_error for PopBack from empty vector");
	}
	catch (underflow_error &) {
	}
	catch (...) {
		Assert(false, "Unexpected exception for PopBack from empty vector");
	}
}

int main() {
	PRINT_FILE_LINE();

	{
		TestRunner tr;
		RUN_TEST(tr, TestConstruction);
		RUN_TEST(tr, TestPushBack);
		RUN_TEST(tr, TestPopBack);
	}

	cerr << "Running benchmark..." << endl;
	const size_t max_size = 2500;

	default_random_engine re;
	uniform_int_distribution<int> value_gen(1, max_size);

	vector<vector<int>> test_data(50000);
	for (auto &cur_vec : test_data) {
		cur_vec.resize(value_gen(re));
		for (int &x : cur_vec) {
			x = value_gen(re);
		}
	}

	{
		LOG_DURATION("vector w/o reserve");
		for (auto &cur_vec : test_data) {
			vector<int> v;
			for (int x : cur_vec) {
				v.push_back(x);
			}
		}
	}
	{
		LOG_DURATION("vector with reserve");
		for (auto &cur_vec : test_data) {
			vector<int> v;
			v.reserve(cur_vec.size());
			for (int x : cur_vec) {
				v.push_back(x);
			}
		}
	}
	{
		LOG_DURATION("StackVector");
		for (auto &cur_vec : test_data) {
			StackVector<int, max_size> v;
			for (int x : cur_vec) {
				v.PushBack(x);
			}
		}
	}
	cerr << "Done" << endl;
}
#endif //1

/*
StackVector
Условие

В блоке про модель памяти мы говорили, что динамическая память нужна для хранения тех объектов, которые должны жить дольше, чем создавшая их функция. Кроме того мы говорили, что можно создать такой вектор, который не использует память из кучи, а хранит все свои объекты на стеке. В этой задаче вам предстоит это сделать. Вы совсем недавно познакомились с контейнером array, который хранит все свои данные на стеке. Реализуйте интерфейс вектора поверх него. Более формально, реализуйте шаблон класса template <typename T, size_t N> StackVector<T, N>, где T — тип элемента вектора, а N — его максимальная вместимость. Класс StackVector должен иметь следующий интерфейс:

template <typename T, size_t N>
class StackVector {
public:
  explicit StackVector(size_t a_size = 0);

  T& operator[](size_t index);
  const T& operator[](size_t index) const;

  ??? begin();
  ??? end();
  ??? begin() const;
  ??? end() const;

  size_t Size() const;
  size_t Capacity() const;

  void PushBack(const T& value);
  T PopBack();
};

	Метод GetHead возвращает указатель на голову списка, он используется для перебора элементов списка (см. шаблон ToVector в заготовке решения)
	Метод Size должен возвращать текущее количество объектов в векторе
	Конструктор принимает размер вектора (по аналогии со стандартным вектором). Если аргумент конструктора оказался больше вместимости вектора, конструктор должен выбрасывать исключение invalid_argument
	Методы begin/end должны возвращать итераторы на начало и текущий конец вектора; их тип не указан, вы должны выбрать его самостоятельно
	Метод PushBack добавляет новый элемент в конец вектора. Если текущий размер вектора равен его вместимости, метод PushBack должен выбрасывать стандартное исключение overflow_error overflow_error
	Методы begin/end должны возвращать итераторы на начало и текущий конец вектора; их тип не указан, вы должны выбрать его самостоятельно
	Метод PopBack уменьшает размер вектора на один и возвращает элемент вектора, который был последним. Если вектор пуст, метод PopBack должен выбрасывать стандартное исключение underflow_error

Интерфейс класса StackVector описан в файле stack_vector.h, приложенном к этой задаче. Часть требований к нему сформулирована в виде юнит-тестов в файле stack_vector.cpp.

Обратите внимание, как отличается поведение метода PushBack в классе StackVector от метода PushBack в классе SimpleVector, который вы реализовывали ранее в блоке про модель памяти. SimpleVector::PushBack выделял дополнительную память в куче, если размер вектора оказывался равен ёмкости. В случае с классом StackVector мы должны на этапе компиляции задать максимальную ёмкость вектора и, если она оказывается исчерпана, нам больше неоткуда взять память, и мы просто бросаем исключение. В этом состоит недостаток реализации вектора на стеке по сравнению с обычным вектором.

С другой стороны, файл stack_vector.cpp содержит бенчмарк, который демонстрирует преимущество StackVector перед обычным вектором. Этот бенчмарк моделирует ситуацию, когда мы считываем из потока количество объектов N, а затем добавляем в вектор N объектов с помощью метода push_back (тестовые данные разложены в vector<vector>, чтобы исключить из бенчмарка время, необходимое на парсинг). Когда вы реализуете шаблон StackVector, сравните его производительность с вектором.

На проверку пришлите заголовочный файл с реализацией шаблона StackVector.
Заготовка решения

stack_vector.h

stack_vector.cpp
Замечание
Заголовочный файл, который вы пришлёте на проверку, не должен подключать файлы , , <forward_list>, , . Если у вас будет подключён один из этих файлов, вы получите ошибку компиляции.
*/