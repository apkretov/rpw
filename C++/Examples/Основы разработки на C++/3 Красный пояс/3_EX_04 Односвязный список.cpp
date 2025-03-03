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
����������� ������
�������

����������� ������ � ������������ ������ ��������� ������, ��� ���������� ������� ����� ������������ ������� � ����. � ���� ������ ��� ����� ����������� ������ ������ LinkedList, ������� ������������ ����� ����������� ������ � �������� ��������� �����������:

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

	����� GetHead ���������� ��������� �� ������ ������, �� ������������ ��� �������� ��������� ������ (��. ������ ToVector � ��������� �������)
	����� PushFront ��������� ����� ������� � ������ ������.
	����� InsertAfter ��������� ����� ������� � ������ ���, ����� �� ��� ����� ���� node. ���� node == nullptr, ����� ������������ PushFront
	����� PopFront ������� ������� �� ������ ������ � ����������� ���������� ��� ���� ������. ���� ������ ����, ����� ����������� ���������. ���� ����� ���������� ������ ������ ���� ������, ����� GetHead ������ ���������� nullptr
	����� RemoveAfter ������ ������� �� ������ �������, ������� ������� �� ����� node, � ����������� ���������� ��� ���� ������. ���� node == nullptr, ����� ������������ PopFront. ���� node->next == nullptr, �� ����� ������ ��������� �����������.
	��� ������, ������������� ����, ������ �������� �� O(1)
	���������� ������ LinkedList ����������� ��� ������, ���������� ��� �������� ��������� ������.

���� � ���������� �������

linked_list.cpp
*/