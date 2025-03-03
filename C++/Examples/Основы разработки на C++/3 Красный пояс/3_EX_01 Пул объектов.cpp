#if 0 //@ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/tree/main/Week_3/01%20Programming%20Assignment

#include <queue>
#include <ranges>
#include <stdexcept>
#include <set>
//OFF #include "vld.h"
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

#define MINE
#undef GITHUB

//#ifdef MINE
//template <class T>
//class ObjectPool {
//	set<T *> allocated;
//	queue<T *> deallocated;
//	T *allocateFromDeallocated();
//public:
//	T *Allocate();
//	T *TryAllocate();
//	void Deallocate(T *object);
//	~ObjectPool();
//};
//
//template <typename T>
//T *ObjectPool<typename T>::Allocate() {
//	if (!deallocated.empty())
//		return allocateFromDeallocated();
//	else {
//		auto object = new(T);
//		allocated.insert(object);
//		return object;
//	}
//}
//
//template <typename T>
//T *ObjectPool<typename T>::TryAllocate() {
//	if (!deallocated.empty())
//		return allocateFromDeallocated();
//	else
//		return nullptr;
//}
//
//template <typename T>
//void ObjectPool<typename T>::Deallocate(T *object) {
//	if (!allocated.contains(object))
//		throw(invalid_argument("Error: The deallocated object does not exist."));
//
//	deallocated.push(object);
//	allocated.erase(object);
//}
//
//template <typename T>
//ObjectPool<typename T>::~ObjectPool() {
//	ranges::for_each(allocated, default_delete<T>());
//
//	while (!deallocated.empty()) {
//		delete deallocated.front();
//		deallocated.pop();
//	}
//}
//
//template <typename T>
//T *ObjectPool<typename T>::allocateFromDeallocated() {
//	T *object = deallocated.front();
//	allocated.insert(object);
//	deallocated.pop();
//	return object;
//}
//#endif //MINE

#ifdef MINE
#include "3_EX_01 Пул объектов.h"
#endif //MINE

#ifdef GITHUB //@ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/blob/main/Week_3/01%20Programming%20Assignment/Solution/object_pool.cpp
template <typename T>
class ObjectPool {
	set<T *> allocated_objects; //MINE
	deque<T *> released_objects; //MINE
public:
	T *Allocate() {
		if (!released_objects.empty()) {
			auto ro_ptr = released_objects.front();
			allocated_objects.insert(ro_ptr);
			released_objects.pop_front();
			return ro_ptr;
		}
		T *t_ptr = new T;
		allocated_objects.insert(t_ptr);
		return t_ptr;
	}

	T *TryAllocate() {
		if (released_objects.empty()) {
			return nullptr;
		}
		return Allocate();
	}

	void Deallocate(T *object) {
		if (allocated_objects.find(object) == allocated_objects.end()) {
			throw invalid_argument("");
		}
		released_objects.push_back(*allocated_objects.find(object));
		allocated_objects.erase(object);
	}

	~ObjectPool() {
		for_each(allocated_objects.begin(), allocated_objects.end(), default_delete<T>()); //TEST!
		for_each(released_objects.begin(), released_objects.end(), default_delete<T>());
	}
#ifdef ORIG
private:
	set<T *> allocated_objects;
	deque<T *> released_objects;
#endif //ORIG
};
#endif //GITHUB

void TestObjectPool() {
	ObjectPool<string> pool;

	auto p1 = pool.Allocate();
	auto p2 = pool.Allocate();
	auto p3 = pool.Allocate();

	*p1 = "first";
	*p2 = "second";
	*p3 = "third";

	pool.Deallocate(p2);
	ASSERT_EQUAL(*pool.Allocate(), "second");
	
	pool.Deallocate(p3);
	pool.Deallocate(p1);
	ASSERT_EQUAL(*pool.Allocate(), "third");
	ASSERT_EQUAL(*pool.Allocate(), "first");

	pool.Deallocate(p1);
}

int main() {
	PRINT_FILE_LINE();

	TestRunner tr;
	RUN_TEST(tr, TestObjectPool);

	return 0;
}
#endif //1 @

/*
Пул объектов
Условие

На практике часто возникают объекты, создание которых занимает значительное время, например, потоки (threads), TCP-соединения или подключения к базе данных. Поэтому, когда такой объект становится не нужен, его не разрушают, а откладывают в сторону, чтобы потом переиспользовать. В этой задаче вам предстоит реализовать такую схему — вам надо написать шаблон класса ObjectPool:

template <class T>
class ObjectPool {
public:
  T* Allocate();
  T* TryAllocate();

  void Deallocate(T* object);

  ~ObjectPool();

private:
  ...
};

	Объект класса ObjectPool должен поддерживать два набора объектов: выделенные и освобождённые, — изначально оба набора пусты.
	Метод Allocate должен работать так:

	если есть хотя бы один освобождённый объект, то его надо перенести в множество выделенных и вернуть указатель на него в качестве результата функции
	если же освобождённых объектов нет, то создаётся новый объект, помещается в множество выделенных, и указатель на него возвращается в качестве результата функции

	Метод TryAllocate работает аналогично, однако если освобождённых объектов нет, он должен просто возвращать nullptr.
	Метод Deallocate переносит объект из множества выделенных в множество освобождённых; если переданный объект не содержится в множестве выделенных, метод Deallocate должен бросать исключение invalid_argument.
	Методы Allocate и TryAllocate должны возвращать объекты в порядке FIFO, т.е. множество освобождённых объектов должно представлять собой очередь: методы [Try]Allocate должны извлекать объекты из её начала, а метод Deallocate должен помещать освобождаемый объект в её конец.
	Деструктор объекта ObjectPool должен уничтожать все объекты пула, как выделенные, так и освобождённые.

Заготовка решения:

object_pool.cpp
*/