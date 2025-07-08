#if 0 //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/tree/main/week3/03%20Practice%20Assignment

#include <numeric>
#include <future>
#include <mutex>
#include <queue>
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

#ifdef MINE
template <typename T>
class Synchronized {
	mutable mutex mtx;
	T value;
public:
	explicit Synchronized(T initial = T()) : value(std::move(initial)) {}

	class Access {
	public:
		Access(T &value, mutex &mtx) : ref_to_value(value), lock(mtx) {}
		T &ref_to_value;
	private:
		lock_guard<mutex> lock;
	};

	Access GetAccess() { return {value, mtx}; }
	Access GetAccess() const { return {const_cast<T &>(value), mtx}; }
};

#else //GITHUB @ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week3/03%20Practice%20Assignment/solution.cpp
template <typename T>
class Synchronized {
	T value;
	mutable mutex m;
public:
	explicit Synchronized(T initial = T()) : value(move(initial)) {}

	template <typename U> //TEST!!
	struct Access {
		U &ref_to_value;
		lock_guard<mutex> guard;
	};

	Access<T> GetAccess() {	return {value, lock_guard(m)}; }
	Access<const T> GetAccess() const { return {value, lock_guard(m)}; } //TEST!!
};
#endif //MINE

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

vector<int> Consume(Synchronized<deque<int>> &common_queue) {
	vector<int> got;

	for (;;) {
		deque<int> q;

		{ // Мы специально заключили эти две строчки в операторные скобки, чтобы уменьшить размер критической секции. // Поток-потребитель захватывает мьютекс, перемещает всё содержимое общей очереди в свою локальную переменную и отпускает мьютекс. // После этого он обрабатывает объекты в очереди за пределами критической секции, // позволяя потоку-производителю параллельно помещать в очередь новые объекты. // Размер критической секции существенно влияет на быстродействие многопоточных программ.
			auto access = common_queue.GetAccess();
			q = move(access.ref_to_value);
		}

		for (int item : q) {
			if (item > 0) {
				got.push_back(item);
			} else {
				return got;
			}
		}
	}
}

void Log(const Synchronized<deque<int>> &common_queue, ostream &out) {
	for (int i = 0; i < 100; ++i) {
		out << "Queue size is " << common_queue.GetAccess().ref_to_value.size() << '\n';
	}
}

void TestProducerConsumer() {
	Synchronized<deque<int>> common_queue;
	ostringstream log;

	auto consumer = async(Consume, ref(common_queue));
	auto logger = async(Log, cref(common_queue), ref(log));

	const size_t item_count = 100000;
	for (size_t i = 1; i <= item_count; ++i) {
		common_queue.GetAccess().ref_to_value.push_back(i);
	}
	common_queue.GetAccess().ref_to_value.push_back(-1);

	vector<int> expected(item_count);
	iota(begin(expected), end(expected), 1);
	ASSERT_EQUAL(consumer.get(), expected);

	logger.get();
	const string logs = log.str();
	ASSERT(!logs.empty());
}

int main() {
	PRINT_FILE_LINE(); //MINE

	TestRunner tr;
	RUN_TEST(tr, TestConcurrentUpdate);
	RUN_TEST(tr, TestProducerConsumer);
}
#endif //1

/*
Замечание

Эта задача — продолжение задачи «Шаблон Synchronized» из «Красного пояса по C++». Ниже приведено её полное условие с необходимыми дополнениями. Так что если вы не проходили «Красный пояс», можете просто решать эту задачу с нуля.

Дополнительные требования по сравнению с «Красным поясом по С++»:

	нужно добавить константный метод GetAccess, который возвращает объект, содержащий константную ссылку на хранимый объект

Условие

Как известно, отсутствие синхронизации доступа нескольких потоков к одним и тем же данным может фатально сказаться на работе программы. Поэтому очень важно не забывать захватывать мьютекс при обращении к разделяемым данным. Но если у нас есть большой проект, в котором доступ к общим данным осуществляется из большого количества мест в коде, то не так уж и трудно забыть сделать это, внося очередные правки.

Чтобы защититься от такой забывчивости, можно написать специальную обёртку над данными, которая будет предоставлять к ним доступ только под мьютексом. В этой задаче вам надо разработать такую обёртку — шаблон класса Synchronized вот с таким интерфейсом:

template <typename T>
class Synchronized {
public:
  explicit Synchronized(T initial = T());

  Access1 GetAccess();
  Access2 GetAccess() const;
private:
  T value;
};

Типы Access1 и Access2 должны быть структурами, в которых есть поля T& ref_to_value и const T& ref_to_valueсоответственно. В обоих случаях поле ref_to_value должно ссылаться на поле value класса Synchronized. Кроме того, объекты классов Access1 и Access2 должны вести себя аналогично классу lock_guard: захватывать мьютекс в своём конструкторе и освобождать в деструкторе. Пример:

Synchronized<int> s_int;
{
  auto access = s_int.GetAccess();
  // Критическая секция начинается отсюда и продолжается до конца блока
  access.ref_to_value = 5;
}
ASSERT_EQUAL(s_int.GetAccess().ref_to_value, 5);

Вам можно (и даже нужно) добавлять необходимые поля в классы Access1, Access2 и шаблон Synchronized. Более подробные примеры использования шаблона Synchronized смотрите в заготовке решения.

Как видите, единственный способ получить доступ к полю value класса Synchronized — это обратиться к полю ref_to_value классов Access1 и Access2, которые гарантируют, что этот доступ осуществляется под мьютексом. Таким образом, если разделяемые данные обернуть в шаблон Synchronized, вы никогда не забудете захватить мьютекс при обращении к ним.
Примечание

Проверяющий код никак не закладывается на имена типов, возвращаемых методами GetAccess, поэтому вы можете назвать их не Access1 и Access2, а как-то более осмысленно.
*/

#ifdef PERPLEXITY

#undef MUTEX_AND_LOCK_GUARD
#define SIMPLE_MUTEX_AND_SIMPLE_LOCK_GUARD

#ifdef MUTEX_AND_LOCK_GUARD
/*
What are std::mutex & std::lock_guard?

Overview of std::mutex and std::lock_guard
In C++, std::mutex and std::lock_guard are essential components of the Standard Library that facilitate multithreading by managing access to shared resources.

std::mutex
	Definition: A std::mutex (short for "mutual exclusion") is a synchronization primitive that is used to protect shared data from being simultaneously accessed by multiple threads. It ensures that only one thread can lock the mutex at a time, preventing race conditions.
	Usage:
		To use a mutex, you typically create an instance of std::mutex.
		You can lock the mutex using the lock() method and unlock it with the unlock() method.

std::lock_guard
	Definition: std::lock_guard is a convenience class that provides a way to manage mutex locking and unlocking automatically. It locks the mutex when constructed and unlocks it when destroyed, ensuring that the mutex is properly released even if an exception occurs.
	Usage:
		You create a std::lock_guard object by passing a reference to a std::mutex. The lock is acquired upon creation, and it is released when the lock_guard goes out of scope.
*/
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex mtx; // Create a mutex

void printThreadId(int id) {
#ifndef WITHOUT_LOCK_GUARD
	mtx.lock(); // Lock the mutex
	cout << "Thread ID: " << id << endl; // Critical section
	mtx.unlock(); // Unlock the mutex
#else //WITH_LOCK_GUARD
	lock_guard<mutex> guard(mtx); // Lock the mutex automatically
	cout << "Thread ID: " << id << endl; // Critical section // Mutex is automatically unlocked when guard goes out of scope
#endif //WITH_LOCK_GUARD
}

int main() {
	thread t1(printThreadId, 1);
	thread t2(printThreadId, 2);

	t1.join();
	t2.join();
	return 0;
}
#endif //MUTEX_AND_LOCK_GUARD

#ifdef SIMPLE_MUTEX_AND_SIMPLE_LOCK_GUARD
/*
Simplified Mutex Example
This example demonstrates how threads are managed with a mutex to ensure that only one thread can access the critical section at a time.

Explanation
	Atomic Flag: The SimpleMutex class uses an atomic_flag to represent the lock state. This ensures that operations on the flag are atomic, preventing race conditions.
	Locking Mechanism: The lock() method employs a spinlock mechanism. It continuously checks if the lock is available (not set) and attempts to set it. If it's already locked, it keeps spinning (busy-waiting) until it can acquire the lock.
	Unlocking: The unlock() method simply clears the atomic flag, allowing other threads to acquire the lock.
	Thread Function: Each thread increments a shared resource while holding the mutex lock, ensuring that only one thread can modify the resource at a time.

	SimpleMutex Class: Implements a basic locking mechanism using an atomic_flag. The lock() method uses a spinlock to acquire the mutex, while the unlock() method releases it.
	
	SimpleLockGuard Class: Manages the locking and unlocking of the SimpleMutex. It locks the mutex upon construction and unlocks it when the object goes out of scope, ensuring proper resource management.

Conclusion
This example provides insight into how serialization is achieved through locking mechanisms in multithreaded programming. While actual operating system implementations will be more sophisticated and optimized for performance and fairness, this simplified version captures the essential concept of mutual exclusion and serialization of access to shared resources.
*/
#include <atomic>
#include <thread>
#include "../../stdafx.h"
using namespace std;

class SimpleMutex { // SimpleMutex class for locking mechanism
	atomic_flag lockFlag = ATOMIC_FLAG_INIT; // Atomic flag for lock state
public:
	void lock() {
		while (lockFlag.test_and_set(memory_order_acquire)) { // Spin until the lock is acquired
			// Busy-waiting
		}
	}

	void unlock() { lockFlag.clear(memory_order_release); } // Release the lock
};

class SimpleLockGuard { // SimpleLockGuard class for automatic mutex management
	SimpleMutex &mtx; // Reference to the mutex
public:
	SimpleLockGuard(SimpleMutex &m) : mtx(m) { mtx.lock(); } // Acquire the lock
	~SimpleLockGuard() { mtx.unlock(); } // Release the lock
};

SimpleMutex mutex; // Create an instance of SimpleMutex
int sharedResource = 0; // Shared resource

void threadFunction(int id) {
	SimpleLockGuard guard(mutex); // Automatically locks the mutex
	++sharedResource; // Critical section
	cout << "Thread " << id << " incremented resource to " << sharedResource << endl;
} // Mutex is automatically unlocked when guard goes out of scope

int main() {
	PRINT_FILE_LINE();

	thread t1(threadFunction, 1);
	thread t2(threadFunction, 2);

	t1.join();
	t2.join();

	return 0;
}
#endif //SIMPLE_MUTEX_AND_SIMPLE_LOCK_GUARD

#endif //PERPLEXITY