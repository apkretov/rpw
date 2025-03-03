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
#include "3_EX_01 ��� ��������.h"
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
��� ��������
�������

�� �������� ����� ��������� �������, �������� ������� �������� ������������ �����, ��������, ������ (threads), TCP-���������� ��� ����������� � ���� ������. �������, ����� ����� ������ ���������� �� �����, ��� �� ���������, � ����������� � �������, ����� ����� ����������������. � ���� ������ ��� ��������� ����������� ����� ����� � ��� ���� �������� ������ ������ ObjectPool:

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

	������ ������ ObjectPool ������ ������������ ��� ������ ��������: ���������� � ������������, � ���������� ��� ������ �����.
	����� Allocate ������ �������� ���:

	���� ���� ���� �� ���� ������������ ������, �� ��� ���� ��������� � ��������� ���������� � ������� ��������� �� ���� � �������� ���������� �������
	���� �� ������������ �������� ���, �� �������� ����� ������, ���������� � ��������� ����������, � ��������� �� ���� ������������ � �������� ���������� �������

	����� TryAllocate �������� ����������, ������ ���� ������������ �������� ���, �� ������ ������ ���������� nullptr.
	����� Deallocate ��������� ������ �� ��������� ���������� � ��������� ������������; ���� ���������� ������ �� ���������� � ��������� ����������, ����� Deallocate ������ ������� ���������� invalid_argument.
	������ Allocate � TryAllocate ������ ���������� ������� � ������� FIFO, �.�. ��������� ������������ �������� ������ ������������ ����� �������: ������ [Try]Allocate ������ ��������� ������� �� � ������, � ����� Deallocate ������ �������� ������������� ������ � � �����.
	���������� ������� ObjectPool ������ ���������� ��� ������� ����, ��� ����������, ��� � ������������.

��������� �������:

object_pool.cpp
*/