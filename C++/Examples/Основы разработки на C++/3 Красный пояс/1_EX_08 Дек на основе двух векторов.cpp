#if 0 //@ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/blob/main/Week_1/08%20Programming%20Assignment/Solution/deque_via_two_vectors.cpp

#include <iostream>
#include <vector>
#include "../../stdafx.h"
using namespace std;

template <typename T>
class Deque {
public:
	Deque() = default;

	void PushFront(const T &value) {
		front.push_back(value);
	}

	void PushBack(const T &value) {
		back.push_back(value);
	}

	bool Empty() const {
		return (front.empty() && back.empty());
	}

	size_t Size() const {
		return (front.size() + back.size());
	}

	const T &Front() const { //TEST
		if (front.empty()) {
			return back.front();
		}
		return front.back();
	}

	T &Front() {
		if (front.empty()) { //TEST
			//ORIG return const_cast<T &>(std::as_const(back).front());
			return back.front(); //MINE
		}
		//ORIG return const_cast<T &>(std::as_const(front).back()); //TEST! GPT: The Role of const_cast and std::as_const: std::as_const creates a const reference to an object; const_cast is used to remove the constness from a reference.
		return front.back(); //MINE GPT: Your proposed implementation is indeed better because it is simpler, more readable, and avoids unnecessary complexity and potential pitfalls associated with const_cast.
	}

	const T &Back() const {
		if (back.empty()) {
			return front.front();
		}
		return back.back();
	}

	T &Back() {
		if (back.empty()) {
			//ORIG return const_cast<T &>(std::as_const(front).front());
			return front.front(); //MINE
		}
		//ORIG return const_cast<T &>(std::as_const(back).back());
		return back.back(); //MINE
	}

	const T &At(const size_t index) const {
		if (index >= Size()) {
			throw std::out_of_range("out_of_range");
		}

		if (index < front.size()) {
			return front[(front.size() - 1) - index];
		}
		return back[index - front.size()];
	}

	T &At(const size_t index) {
		if (index >= Size()) {
			throw std::out_of_range("out_of_range");
		}

		if (index < front.size()) {
			return const_cast<T &>(std::as_const(front)[(front.size() - 1) - index]);
		}
		return const_cast<T &>(std::as_const(back)[index - front.size()]);
	}

	const T &operator[](size_t index) const {
		if (index < front.size()) {
			return front[(front.size() - 1) - index];
		}
		return back[index - front.size()];
	}

	T &operator[](size_t index) {
		if (index < front.size()) {
			return const_cast<T &>(std::as_const(front)[(front.size() - 1) - index]);
		}
		return const_cast<T &>(std::as_const(back)[index - front.size()]);
	}
private:
	std::vector<T> front;
	std::vector<T> back;
};

int main() {
	PRINT_FILE_LINE(); //MINE

	Deque<int> d;
	d.PushFront(42);
	cout << d.Front() << '\n';
	d.Front() = 111;
	cout << d.Front() << '\n';
}
#endif //1

/*
Дек на основе двух векторов
Условие

Напишите шаблонный класс Deque, содержащий следующий набор методов:

	конструктор по умолчанию;
	константный метод Empty, возвращающий true, если дек не содержит ни одного элемента;
	константный метод Size, возвращающий количество элементов в деке;
	T& operator[](size_t index) и const T& operator[](size_t index) const;
	константный и неконстантный метод At(size_t index), генерирующий стандартное исключение out_of_range, если индекс больше или равен количеству элементов в деке;
	константные и неконстантные версии методов Front и Back, возвращающих ссылки на первый и последний элемент дека соответственно;
	методы PushFront и PushBack.

Неконстантные версии методов должны позволять изменять соответствующий элемент дека.

Для реализации заведите внутри класса Deque два вектора: в один осуществляйте вставку в методе PushFront, а в другой — в методе PushBack
Замечание
Заголовочный файл, который вы пришлёте на проверку, не должен подключать файлы , , , . Если у вас будет подключен один из этих файлов, вы получите ошибку компиляции.
*/