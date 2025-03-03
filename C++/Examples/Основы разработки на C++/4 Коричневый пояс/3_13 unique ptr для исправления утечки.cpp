#if 0

#include <memory>
#include <queue>
#include <unordered_map>
#include <stdexcept>
#include "../../stdafx.h"
using namespace std;

template <class T>
class ObjectPool {
public:
	T *Allocate();
	T *TryAllocate();
	void Deallocate(T *object);
private:
	queue<unique_ptr<T>> free;
	unordered_map<T *, unique_ptr<T>> allocated;
};

template <typename T>
T *ObjectPool<typename T>::Allocate() {
	if (free.empty())
		free.push(make_unique<T>());
	auto ptr = std::move(free.front());
	free.pop();
	T *ret = ptr.get();
	allocated[ret] = std::move(ptr);
	return ret;
}

template <typename T>
T *ObjectPool<typename T>::TryAllocate() {
	if (free.empty())
		return nullptr;
	return Allocate();
}

template <typename T>
void ObjectPool<typename T>::Deallocate(T *object) {
	auto it = allocated.find(object);
	if (it == allocated.end())
		throw(invalid_argument(""));

	free.push(std::move(it->second));
	allocated.erase(it);
}

int counter = 0;

struct Counted {
	Counted() { ++counter; }
	~Counted() { --counter; }
};

void run() {
	ObjectPool<Counted> pool;
	cout << "Counter before loop = " << counter << endl;
	for (int i = 0; i < 1000; ++i) {
		cout << "Allocating object #" << i << endl;
		pool.Allocate();
	}
	cout << "Counter after loop = " << counter << endl;
}

int main() {
	PRINT_FILE_LINE(); //MINE

	run();
	cout << "Counter before exit = " << counter << endl;

	return 0;
}
#endif //1
