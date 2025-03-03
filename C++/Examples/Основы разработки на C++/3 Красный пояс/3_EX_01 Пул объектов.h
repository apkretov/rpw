#pragma once

#pragma region MINE

template <class T>
class ObjectPool {
	set<T *> allocated;
	queue<T *> deallocated;
	T *allocateFromDeallocated();
public:
	T *Allocate();
	T *TryAllocate();
	void Deallocate(T *object);
	~ObjectPool();
};

template <typename T>
T *ObjectPool<typename T>::Allocate() {
	if (!deallocated.empty())
		return allocateFromDeallocated();
	else {
		auto object = new(T);
		allocated.insert(object);
		return object;
	}
}

template <typename T>
T *ObjectPool<typename T>::TryAllocate() {
	if (!deallocated.empty())
		return allocateFromDeallocated();
	else
		return nullptr;
}

template <typename T>
void ObjectPool<typename T>::Deallocate(T *object) {
	if (!allocated.contains(object))
		throw(invalid_argument("Error: The deallocated object does not exist."));

	deallocated.push(object);
	allocated.erase(object);
}

template <typename T>
ObjectPool<typename T>::~ObjectPool() {
	ranges::for_each(allocated, default_delete<T>());

	while (!deallocated.empty()) {
		delete deallocated.front();
		deallocated.pop();
	}
}

template <typename T>
T *ObjectPool<typename T>::allocateFromDeallocated() {
	T *object = deallocated.front();
	allocated.insert(object);
	deallocated.pop();
	return object;
}
#pragma endregion //MINE 
