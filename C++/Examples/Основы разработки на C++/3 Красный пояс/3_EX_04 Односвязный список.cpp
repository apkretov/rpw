#if 0 //@ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/blob/main/Week_3/04%20Programming%20Assignment/Solution/linked_list.cpp

#include <iostream>
#include <vector>
#include "../../stdafx.h"
using namespace std;

template <typename T>
class LinkedList {
public:
	struct Node {
		T value{};
		Node *next = nullptr;
	};
	~LinkedList();

	void PushFront(const T &value);
	void InsertAfter(Node *node, const T &value);
	void RemoveAfter(Node *node);
	void PopFront();

	Node *GetHead() { return head; }
	const Node *GetHead() const { return head; }
private:
	Node *head = nullptr;
};

template <typename T>
LinkedList<T>::~LinkedList() {
	while (head) {
		PopFront();
	}
}

template <typename T>
void LinkedList<T>::PushFront(const T &value) {
	Node *n_ptr = new Node{value};
	n_ptr->next = head;
	head = n_ptr;
}

template <typename T>
void LinkedList<T>::InsertAfter(Node *node, const T &value) {
	if (node == nullptr) {
		PushFront(value);
	} else {
		Node *n_ptr = new Node{value};
		n_ptr->next = node->next;
		node->next = n_ptr;
	}
}

template <typename T>
void LinkedList<T>::RemoveAfter(Node *node) {
	if (node == nullptr) {
		PopFront();
		return;
	} else {
		if (node->next == nullptr) {
			return;
		} else {
			Node *del_n_ptr = node->next;
			node->next = del_n_ptr->next;
			delete del_n_ptr;
		}
	}
}

template <typename T>
void LinkedList<T>::PopFront() {
	if (head) {
		Node *n_ptr = head->next;
		delete head;
		head = n_ptr;
	}
}

template <typename T>
vector<T> ToVector(const LinkedList<T> &list) {
	vector<T> result;
	for (auto node = list.GetHead(); node; node = node->next) {
		result.push_back(node->value);
	}
	return result;
}

int main() {
	PRINT_FILE_LINE();
	return 0;
}
#endif //1

/*
Односвязный список
Условие

Односвязный список — классический пример структуры данных, для реализации которой нужно пользоваться памятью в куче. В этой задаче вам нужно реализовать шаблон класса LinkedList, который представляет собой односвязный список и обладает следующим интерфейсом:

template <typename T>
class LinkedList {
public:
  struct Node {
	T value;
	Node* next = nullptr;
  };

  ~LinkedList();

  void PushFront(const T& value);
  void InsertAfter(Node* node, const T& value);
  void RemoveAfter(Node* node);
  void PopFront();

  Node* GetHead() { return head; }
  const Node* GetHead() const { return head; }

private:
  Node* head = nullptr;
};

	Метод GetHead возвращает указатель на голову списка, он используется для перебора элементов списка (см. шаблон ToVector в заготовке решения)
	Метод PushFront добавляет новый элемент в голову списка.
	Метод InsertAfter вставляет новый элемент в список так, чтобы он шёл после узла node. Если node == nullptr, метод эквивалентен PushFront
	Метод PopFront удаляет элемент из головы списка и освобождает выделенную под него память. Если список пуст, метод завершается корректно. Если после выполнения метода список стал пустым, метод GetHead должен возвращать nullptr
	Метод RemoveAfter должен удалять из списка элемент, который следует за узлом node, и освобождать выделенную под него память. Если node == nullptr, метод эквивалентен PopFront. Если node->next == nullptr, то метод должен корректно завершаться.
	Все методы, перечисленные выше, должны работать за O(1)
	Деструктор класса LinkedList освобождает всю память, выделенную для хранения элементов списка.

Файл с заготовкой решения

linked_list.cpp
*/