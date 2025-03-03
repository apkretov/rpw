#if 0 //@ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/tree/main/Week_4/02%20Practice%20Programming%20Assignment

#include <algorithm>
#include <deque>
#include <list>
#include <map>
#include <ranges>
#include <stdexcept>
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

#ifndef MINE
class Translator {
public:
	void Add(string_view source, string_view target);
	string_view TranslateForward(string_view source) const;
	string_view TranslateBackward(string_view target) const;
private:
	list<string> words1; // Only one copy of each word can be stored.
	list<string> words2;
	map<string_view, string_view> dict1; // Store pointers for both forward & backward translations.
	map<string_view, string_view> dict2;
	string_view Translate(string_view word, const list<string> &words, const map<string_view, string_view> &dict) const;
};

void Translator::Add(string_view source, string_view target) {
	words1.emplace_front(source);
	words2.emplace_front(target);

	string_view src = words1.front();
	string_view trg = words2.front();

	dict1[src] = trg; //TO DO: Prevent duplicates stored in words???
	dict2[trg] = src;
}

inline string_view Translator::TranslateForward(string_view source) const {
	return Translate(source, words1, dict1);
}

inline string_view Translator::TranslateBackward(string_view target) const {
	return Translate(target, words2, dict2);
}

inline string_view Translator::Translate(string_view word, const list<string> &words, const map<string_view, string_view> &dict) const {
	try {
		auto word_ptr = ranges::find(words, word);
		if (word_ptr == words.cend())
			return "";
		else
			return dict.at(*word_ptr);
	}
	catch (const out_of_range &e) {
		cerr << "out_of_range error: " << e.what() << '\n';
		throw;
	}
}

#else //GITHUB @ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/blob/main/Week_4/03%20Practice%20Programming%20Assignment/Solution/translator.cpp
class Translator {
public:
	void Add(string_view source, string_view target);
	string_view TranslateForward(string_view source) const;
	string_view TranslateBackward(string_view target) const;
private:
	string_view GetClonedView(string_view s);
	static string_view Translate(const map<string_view, string_view> &dict, string_view s);

	map<string_view, string_view> forward_dict;
	map<string_view, string_view> backward_dict;
	deque<string> data;
};

void Translator::Add(string_view source, string_view target) {
	const string_view source_view = GetClonedView(source);
	const string_view target_view = GetClonedView(target);
	forward_dict[source_view] = target_view;
	backward_dict[target_view] = source_view;
}

string_view Translator::TranslateForward(string_view source) const {
	return Translate(forward_dict, source);
}

string_view Translator::TranslateBackward(string_view target) const {
	return Translate(backward_dict, target);
}

string_view Translator::GetClonedView(string_view s) {
	for (const auto *map_ptr : {&forward_dict, &backward_dict}) { //TEST!
		if (const auto it = map_ptr->find(s); it != map_ptr->end()) {
			return it->first;
		}
	}
	return data.emplace_back(s);
}

string_view Translator::Translate(const map<string_view, string_view> &dict, string_view s) {
	if (const auto it = dict.find(s); it != dict.end()) {
		return it->second;
	} else {
		return {};
	}
}
#endif //GITHUB

void TestSimple() {
	Translator translator;
	translator.Add(string("okno"), string("window"));
	translator.Add(string("stol"), string("table"));

	ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
	ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
	ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
#ifdef OFF
#endif //OFF
}

int main() {
	PRINT_FILE_LINE();

	try {
		TestRunner tr;
		RUN_TEST(tr, TestSimple);
	}
	catch (const exception &e) {
		cerr << "exception error: " << e.what() << '\n';
	}
	return 0;
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