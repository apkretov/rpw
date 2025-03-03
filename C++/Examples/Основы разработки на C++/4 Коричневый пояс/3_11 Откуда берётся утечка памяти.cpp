#if 0

#include "../../stdafx.h"
#include "3_10 Обнаружение утечки памяти в ObjectPool 1.h"
#include "3_10 Обнаружение утечки памяти в ObjectPool 2.h"
using namespace std;

template <typename T>
T *ObjectPool<typename T>::Allocate() {
	if (free.empty())
		free.push(new T);
	else {
		auto ret = free.front();
		free.pop();
		try {
			allocated.insert(ret);
		}
		catch (const bad_alloc &) {
			delete ret;
			throw;
		}
		return ret;
	}
}

int main() {
	PRINT_FILE_LINE(); //MINE

	run();
	cout << "Counter before exit = " << counter << endl;

	return 0;
}
#endif //1
