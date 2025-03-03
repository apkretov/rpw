#pragma once

#include <queue>
#include <set>
#include <stdexcept>

template <class T>
class ObjectPool {
public:
	T *Allocate();
	T *TryAllocate();
	void Deallocate(T *object);
	~ObjectPool();
private:
	std::queue<T *> free;
	std::set<T *> allocated;
};

template <typename T>
T *ObjectPool<typename T>::TryAllocate() {
	if (free.empty())
		return nullptr;
	return Allocate();
}

template <typename T>
void ObjectPool<typename T>::Deallocate(T *object) {
	if (allocated.find(object) == allocated.end())
		throw(std::invalid_argument(""));

	allocated.erase(object);
	free.push(object);
}

template <typename T>
ObjectPool<typename T>::~ObjectPool() {
	for (auto x : allocated)
		delete x;

	while (!free.empty()) {
		auto x = free.front();
		free.pop();
		delete x;
	}
}
