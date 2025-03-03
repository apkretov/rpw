#if 0 //@ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/tree/main/Week_5/10%20Practice%20Programming%20Assignment

#include <future>
#include <mutex>
#include <numeric>
#include <queue>
#include <thread>
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

template <typename T>
class Synchronized {
	mutex mtx;
	T value;
public:
	explicit Synchronized(T initial = T()) : value(std::move(initial)) {} //GITHUB //MINE: value(initial) //TEST!

	class Access {
	public:
		/*
		Improved Exception Safety: By initializing ref_to_value first, if an exception occurs during its construction, the lock_guard will not be created at all. This means that there would be no mutex held unnecessarily, thus preventing potential deadlocks or resource leaks.
		Clearer Intent: This approach makes it clear that ref_to_value is prioritized in terms of initialization, which can help future developers understand the intended usage and dependencies between class members.

		If the lock_guard is initialized before the reference to ref_to_value, the potential issues are:
		Exception Safety: If an exception occurs during the initialization of ref_to_value, the lock_guard has already been constructed and locked the mutex. This can lead to a situation where the mutex is held but not released properly if the constructor fails. The lock will be released when the lock_guard goes out of scope, but since it was already initialized, it might create a deadlock scenario if not handled correctly.
		Uninitialized Members: If ref_to_value relies on certain conditions being met (e.g., valid state or memory allocation), initializing it after locking might lead to accessing uninitialized or invalid memory.
		*/
		//Access(mutex &mtx, T &value) : ref_to_value(value), lock(mtx) {} //TEST!!
		Access(T &value, mutex &mtx) : ref_to_value(value), lock(mtx) {} //TEST!!
		T &ref_to_value;
	private:
		lock_guard<mutex> lock; 
	};

	//Access GetAccess() { return Access{mtx, value}; } //GITHUB return {mtx, value}; //TEST
	Access GetAccess() { return {value, mtx}; } //GITHUB //MINE: return Access{value, mtx}; //TEST
};

void TestConcurrentUpdate() {
	Synchronized<string> common_string;
	const size_t add_count = 50000;
	auto updater = [&common_string, add_count] {
		for (size_t i = 0; i < add_count; ++i) {
			auto access = common_string.GetAccess();
			access.ref_to_value += 'a';
		}
	};

	auto f1 = async(updater);
	auto f2 = async(updater);
	f1.get();
	f2.get();
	ASSERT_EQUAL(common_string.GetAccess().ref_to_value.size(), 2 * add_count);
}

void TestMine() {
	Synchronized<string> common_string;
	const size_t add_count = 1000;
	auto updater = [&common_string, add_count](char ch) {
		for (size_t i = 0; i < add_count; ++i)
			common_string.GetAccess().ref_to_value += ch;
	};

	auto f1 = async(updater, 'A');
	auto f2 = async(updater, 'a');
	f1.get();
	f2.get();
	ASSERT_EQUAL(common_string.GetAccess().ref_to_value.size(), 2 * add_count);
	cout << common_string.GetAccess().ref_to_value << '\n';
}

vector<int> Consume(Synchronized<deque<int>> &common_queue) {
	static size_t total_size;
	vector<int> got;
	for (;;) {
		deque<int> q;
		{ // Мы специально заключили эти две строчки в операторные скобки, чтобы уменьшить размер критической секции. // Поток-потребитель захватывает мьютекс, перемещает всё содержимое общей очереди в свою локальную переменную и отпускает мьютекс. // После этого он обрабатывает объекты в очереди за пределами критической секции, // позволяя потоку-производителю параллельно помещать в очередь новые объекты. // Размер критической секции существенно влияет на быстродействие многопоточных программ.
			auto access = common_queue.GetAccess();
			cout << AS_KV(access.ref_to_value.size()) << '\t'; //MINE
			q = move(access.ref_to_value);
			cout << AS_KV(access.ref_to_value.size()) << '\t'; //MINE
			total_size += q.size(); //MINE
			cout << AS_KV(q.size()) << ' ' << AS_KV(total_size) << '\n'; //MINE
		}
		for (int item : q) {
			if (item > 0)
				got.push_back(item);
			else {
				cout << AS_KV(got.size()) << '\n'; //MINE
				return got;
			}
		}
	}
}

void TestProducerConsumer() {
	Synchronized<deque<int>> common_queue;
	auto consumer = async(Consume, ref(common_queue));
	this_thread::sleep_for(chrono::milliseconds(10)); //MINE: Pause before starting the producer.

	const size_t item_count = 100000;
	for (size_t i = 1; i <= item_count; ++i)
		common_queue.GetAccess().ref_to_value.push_back(i);
	common_queue.GetAccess().ref_to_value.push_back(-1);

	vector<int> expected(item_count);
	iota(begin(expected), end(expected), 1);
	ASSERT_EQUAL(consumer.get(), expected);
}

int main() {
	PRINT_FILE_LINE();

	TestRunner tr;
	RUN_TEST(tr, TestMine);
	RUN_TEST(tr, TestConcurrentUpdate);
	RUN_TEST(tr, TestProducerConsumer);
}
#endif //1

/*
Шаблон Synchronized
Условие

Мы уже не раз видели, что отсутствие синхронизации доступа нескольких потоков к одним и тем же данным может фатально сказаться на работе программы. Поэтому очень важно не забывать захватывать мьютекс при обращении к разделяемым данным. Но если у нас есть большой проект, в котором доступ к общим данным осуществляется из большого количества мест в коде, то не так уж и трудно забыть сделать это, внося очередные правки.

Чтобы защититься от такой забывчивости, можно написать специальную обёртку над данными, которая будет предоставлять к ним доступ только под мьютексом. В этой задаче вам надо разработать такую обёртку — шаблон класса Synchronized вот с таким интерфейсом:

template <typename T>
class Synchronized {
public:
  explicit Synchronized(T initial = T());

  struct Access {
	T& ref_to_value;
  };

  Access GetAccess();
private:
  T value;
};

Тип Access должен быть структурой, в которой есть поле T& ref_to_value, ссылающееся на поле value класса Synchronized. Кроме того объект класса Access должен вести себя аналогично классу lock_guard: захватывать мьютекс в своём конструкторе и освобождать в деструкторе. Пример:

Synchronized<int> s_int;
{
  auto access = s_int.GetAccess();
  // Критическая секция начинается отсюда и продолжается до конца блока
  access.ref_to_value = 5;
}
ASSERT_EQUAL(s_int.GetAccess().value, 5);

Вам можно (и даже нужно) добавлять необходимые поля в класс Access и шаблон Synchronized. Более подробные примеры использования шаблона Synchronized смотрите в заготовке решения.

Как видите, единственный способ получить доступ к полю value класса Synchronized — это обратиться к полю ref_to_value класса Access, который гарантирует, что этот доступ осуществляется под мьютексом. Таким образом, если разделяемые данные обернуть в шаблон Synchronized, вы никогда не забудете захватить мьютекс при обращении к ним.
Файл с заготовкой решения

synchronized.cpp
*/