#if 0 //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week1/03%20Programming%20Assignment/README.md

#undef GITHUB_1
#undef GITHUB_2
#define GITHUB_3

#include <cassert>
#include <deque>
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

struct Node {
	Node(int v, Node *p) : value(v), parent(p) {}
	int value;
	Node *left = nullptr;
	Node *right = nullptr;
	Node *parent;
};

class NodeBuilder {
	deque<Node> nodes;
public:
	Node *CreateRoot(int value) {
		nodes.emplace_back(value, nullptr);
		return &nodes.back();
	}

	Node *CreateLeftSon(Node *me, int value) {
		assert(me->left == nullptr);
		nodes.emplace_back(value, me);
		me->left = &nodes.back();
		return me->left;
	}

	Node *CreateRightSon(Node *me, int value) {
		assert(me->right == nullptr);
		nodes.emplace_back(value, me);
		me->right = &nodes.back();
		return me->right;
	}
};

#ifdef GITHUB_1 //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week1/03%20Programming%20Assignment/set_iterator_next.cpp
Node *Next(Node *me) { 
	if (me->parent == nullptr && me->left == nullptr && me->right == nullptr) {
		return nullptr;
	}
	if (me->right != nullptr) {
		Node *node = me->right;
		while (node) {
			if (node->left != nullptr) {
				if (node->left->value > me->value) {
					node = node->left;
					continue;
				} else {
					return node;
				}
			} else {
				return node;
			}
		}
	} else if (me->right == nullptr && me->parent->left == me) {
		return me->parent;
	} else if (me->right == nullptr && me->parent->right == me) {
		Node *node = me->parent;
		while (node) {
			if (node->value > me->value) {
				return node;
			} else {
				if (node->parent != nullptr) {
					node = node->parent;
					continue;
				} else {
					return nullptr;
				}
			}
		}
	}
	return nullptr;
}
#endif //GITHUB_1

#ifdef GITHUB_2 //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week1/03%20Programming%20Assignment/solution.h
inline Node *SearchDown(Node *me) {
	if (me == nullptr)
		return nullptr;

	if (me->left == nullptr)
		return me;

	return SearchDown(me->left);
}


inline Node *SearchUp(Node *me, int value) {
	if (me == nullptr)
		return nullptr;

	if (me->value > value)
		return me;

	return SearchUp(me->parent, value);
}



inline Node *Next(Node *me) {
	if (me->right)
		return SearchDown(me->right);

	return SearchUp(me->parent, me->value);
}
#endif //GITHUB_2

#ifdef GITHUB_3 //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week1/03%20Programming%20Assignment/solution.cpp
Node *GetLeftest(Node *me) {
	assert(me);
	while (me->left) {
		me = me->left;
	}
	return me;
}

Node *Next(Node *me) {
	assert(me);

	if (me->right) {
		return GetLeftest(me->right);
	}

	if (me->parent && me->parent->left == me) {
		return me->parent;
	}

	while (me->parent && me == me->parent->right) {
		me = me->parent;
	}
	return me->parent;
}
#endif //GITHUB_3

void Test1() {
	NodeBuilder nb;

	Node *root = nb.CreateRoot(50);
	ASSERT_EQUAL(root->value, 50);

	Node *l = nb.CreateLeftSon(root, 2);
	Node *min = nb.CreateLeftSon(l, 1);
	Node *r = nb.CreateRightSon(l, 4);
	ASSERT_EQUAL(min->value, 1);
	ASSERT_EQUAL(r->parent->value, 2);

	nb.CreateLeftSon(r, 3);
	nb.CreateRightSon(r, 5);

	r = nb.CreateRightSon(root, 100);
	l = nb.CreateLeftSon(r, 90);
	nb.CreateRightSon(r, 101);

	nb.CreateLeftSon(l, 89);
	r = nb.CreateRightSon(l, 91);

	ASSERT_EQUAL(Next(l)->value, 91);
	ASSERT_EQUAL(Next(root)->value, 89);
	ASSERT_EQUAL(Next(min)->value, 2);
	ASSERT_EQUAL(Next(r)->value, 100);

	while (min) {
		cout << min->value << '\n';
		min = Next(min);
	}
}

void TestRootOnly() {
	NodeBuilder nb;
	Node *root = nb.CreateRoot(42);
	ASSERT(Next(root) == nullptr);
};

int main() {
	PRINT_FILE_LINE();

	TestRunner tr;
	RUN_TEST(tr, Test1);
	RUN_TEST(tr, TestRootOnly);
	return 0;
}
#endif //1

/*
set::iterator++

�� ������� ��� ���� ���������� � ���������� ���������� ����������� map � set. ������ map � set ����������� ��� �������� ������� ������.

����� �� ������ � ���, ��� ������������ ����� ������ � ������� ����������.

� ������ ������ �� ����� �������� �� � ����������� set, �� � ����������� �������� ������� ������, ��������� �� ��������� ������:

struct Node {
  int value;
  Node* left;
  Node* right;
  Node* parent;
};

���:

	value - ��������, ���������� � �������;

	left � right - ��������� �� �������� ������� (��� ����� nullptr ��� ������� ������);

	parent - ��������� �� ������������ ������� (����� nullptr ��� ����� ������).

��������, ��� ��� ������ ������ �� ���������� �� ����������� ��������, � ������ ��������� �� ������� Node*.

��� ��������� ����������� �������

Node* Next(Node* node);

, ������������ ��������� �� ��������� �� ����������� �������� �������.

������� ������ ������� nullptr � ������, ���� ������� ������� -- ��������� � ������.
*/