#ifdef ON

#include <iostream>
using namespace std;

#ifdef Reference_Counts
//MINE
#include "13_02_1.h"
using namespace std;

HasPtr p1("Hiya!");
//TEST! HasPtr p2(p1); //																																										p1 and p2 point to the same string
//TEST! HasPtr p3(p1); //																																										p1, p2, and p3 all point to the same string

#elif! Defining_a_Reference_Counted_Class
#include "13_02_2.h"

struct Mine {
	static size_t count;

	Mine() { 
		count = 1; 
	}
	
	Mine(const Mine &) {
		++count;
	}
};

size_t Mine::count = 0;

void mine1() {
	Mine m1;
	cout << m1.count << '\n';
	cout << Mine::count << '\n';
	
	Mine m2(m1);
	cout << m1.count << '\t' << m2.count << '\n';
	
	Mine m3;
	cout << Mine::count << '\n';
}

void mine2() {
	HasPtr hp1("HasPtr 1");
	cout << "*hp1.use = " << *hp1.use << '\n';
	
	{
		HasPtr hp2(hp1);
		cout << "*hp1.use = " << *hp1.use << "\t*hp2.use = " << *hp2.use << '\n';
	}
	
	HasPtr hp3;
	cout << "*hp1.use = " << *hp1.use << "\t*hp3.use = " << *hp3.use << '\n';
}
#endif

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//mine1();
	mine2();

	return 0;
}
#endif

#ifdef EX_13_28_1 // ch13/ex13_28.h @ https://github.com/Mooophy/Cpp-Primer/blob/master/ch13/ex13_28.h

#include <iostream>
using namespace std;

class TreeNode {
public:
	TreeNode() : value(string()), count(new int(1)), left(nullptr), right(nullptr) {}
	TreeNode(const TreeNode &rhs) : value(rhs.value), count(rhs.count), left(rhs.left), right(rhs.right) { ++*count; }
	TreeNode &operator=(const TreeNode &rhs);
	~TreeNode() {
		cout << "TreeNode desctructor\n"; //MINE
		if (--*count == 0) {
			delete left;
			delete right;
			delete count;
		}
	}
private:
	std::string value;
	int *count;
	TreeNode *left;
	TreeNode *right;
};

TreeNode &TreeNode::operator=(const TreeNode &rhs) {
	++*rhs.count;
	if (--*count == 0) {
		delete left;
		delete right;
		delete count;
	}
	value = rhs.value;
	left = rhs.left;
	right = rhs.right;
	count = rhs.count;
	return *this;
}

class BinStrTree {
public:
	BinStrTree() : root(new TreeNode()) {}
	BinStrTree(const BinStrTree &bst) : root(new TreeNode(*bst.root)) {}
	BinStrTree &operator=(const BinStrTree &bst);
	~BinStrTree() { 
		cout << "BinStrTree destructor\n"; //MINE
		delete root; 
	}
private:
	TreeNode *root;
};

BinStrTree &BinStrTree::operator=(const BinStrTree &bst) {
	TreeNode *new_root = new TreeNode(*bst.root);
	delete root;
	root = new_root;
	return *this;
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	BinStrTree t; //MINE

	return 0;
}
#endif

#ifdef EX_13_28_2 // ch13/13.28.cpp @ https://github.com/jaege/Cpp-Primer-5th-Exercises/blob/master/ch13/13.28.cpp

#include <iostream>
using namespace std;

#include <string>

class TreeNode { // Valuelike `TreeNode`. When we copy a `TreeNode`, we copy all the subtree from current node.
public:
	TreeNode() : value(), count(0), left(nullptr), right(nullptr) {}
	TreeNode(const std::string &s, int c) : value(s), count(c), left(nullptr), right(nullptr) {}
	TreeNode(const TreeNode &);
	~TreeNode();
	TreeNode &operator=(const TreeNode &);
	// insert // remove	// tranverse
private:
	std::string value;
	int count;
	TreeNode *left; // Note that the valid state for the `left` and `right` pointer is either `nullptr` or a subtree node. So that we must check these pointers every time before dereferencing them.
	TreeNode *right;

  /* First version: helper funtion for copy constructor and destructor *
	void copyTree(TreeNode *, const TreeNode *);
	void destroyTree(TreeNode *);
  /**/
};

/* First version: copy constructor and destructor *
void TreeNode::copyTree(TreeNode *lhs, const TreeNode *rhs) {
  // Both lhs and rhs must NOT be nullptr
  lhs->value = rhs->value;
  lhs->count = rhs->count;
  if (rhs->left) {
	lhs->left = new TreeNode;  // call default constructor of `TreeNode`
	copyTree(lhs->left, rhs->left);
  } else
	lhs->left = nullptr;
  if (rhs->right) {
	lhs->right = new TreeNode;  // call default constructor of `TreeNode`
	copyTree(lhs->right, rhs->right);
  } else
	lhs->right = nullptr;
}

void TreeNode::destroyTree(TreeNode *n) {
  // n can be a nullptr
  if (!n) return;
  destroyTree(n->left);
  n->left = nullptr;
  destroyTree(n->right);
  n->right = nullptr;
  delete n;  // This statement will cause delete subtree multiple times if we
			 // forget to assign n->left and n->right to nullptr.
}

TreeNode::TreeNode(const TreeNode &n) {
  copyTree(this, &n);
}

TreeNode::~TreeNode() {
  destroyTree(left);
  destroyTree(right);
}
/**/

TreeNode::TreeNode(const TreeNode &n) : value(n.value), count(n.count), left(nullptr), right(nullptr) { /* Second version: without helper function */
	if (n.left)
		left = new TreeNode(*n.left);  // recursively call copy constructor
	if (n.right)
		right = new TreeNode(*n.right);  // recursively call copy constructor
}

TreeNode::~TreeNode() { // Note that when left or right is nullptr, delete will do nothing, so that the recursion will be stopped.
	delete left;  // recursively call destructor on left subtree node
	delete right;  // recursively call destructor on right subtree node
}

TreeNode &TreeNode::operator=(const TreeNode &n) {
	value = n.value;
	count = n.count;

	TreeNode *tmp = nullptr;
	if (n.left)
		tmp = new TreeNode(*n.left);  // recursively call copy constructor
	delete left;  // recursively call destructor
	left = tmp;

	tmp = nullptr;
	if (n.right)
		tmp = new TreeNode(*n.right);  // recursively call copy constructor
	delete right;  // recursively call destructor
	right = tmp;

	return *this;
}
/**/

// Two versions of `BinStrTree` are defined here. The first version is
// valuelike version, while the second verison is pointerlike version. The
// class declarations of these two versions are the same except the pointerlike
// version adds a data member for reference count, while the defitions of
// copy-control members are different.

/* First Version: Valuelike `BinStrTree` *
// When we copy a `BinStrTree`, we copy all the subtree from `root` node.
class BinStrTree {
public:
  BinStrTree(const TreeNode &r = TreeNode()) : root(new TreeNode(r)) {}
  BinStrTree(const BinStrTree &);

  ~BinStrTree();

  BinStrTree &operator=(const BinStrTree &);

private:
  TreeNode *root;
  // Note that the valid state for the `root` pointer is always a pointer to an
  // existing tree node, and `nullptr` is not a valid state. So that we can
  // dereference this pointer without checking if it's a null pointer in copy
  // constructor and copy-assignment operator. (Class Invariant)
};

BinStrTree::BinStrTree(const BinStrTree &rhs)
	: root(new TreeNode(*rhs.root)) {}  // recursively call copy constructor

BinStrTree::~BinStrTree() {
  delete root;  // recursively call destructor of `TreeNode`
}

BinStrTree &BinStrTree::operator=(const BinStrTree &t) {
  TreeNode *tmp = new TreeNode(*t.root);
  delete root;
  root = tmp;

  return *this;
}
/**/

/* Second version: Pointerlike `BinStrTree` */
// When we copy a `BinStrTree`, the copyed object point to the same tree as the
// original object.
class BinStrTree {
public:
	BinStrTree(const TreeNode &r = TreeNode())
		: root(new TreeNode(r)), use(new std::size_t(1)) {
	}
	BinStrTree(const BinStrTree &);

	~BinStrTree();

	BinStrTree &operator=(const BinStrTree &);

private:
	TreeNode *root;
	// Note that the valid state for the `root` pointer is always a pointer to an
	// existing tree node, and `nullptr` is not a valid state. So that we can
	// dereference this pointer without checking if it's a null pointer in copy
	// constructor and copy-assignment operator. (Class Invariant)
	std::size_t *use;
};

BinStrTree::BinStrTree(const BinStrTree &rhs)
	: root(new TreeNode(*rhs.root)), use(rhs.use) {
	++*use;
}
// recursively call copy constructor

BinStrTree::~BinStrTree() {
	if (--*use == 0) {
		delete root;  // recursively call destructor of `TreeNode`
		delete use;
	}
}

BinStrTree &BinStrTree::operator=(const BinStrTree &t) {
	++*t.use;
	if (--*use == 0) {
		delete root;
		delete use;
	}
	root = t.root;
	use = t.use;

	return *this;
}
/**/

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	TreeNode node; // TODO test class `TreeNode`

	BinStrTree bst; // TODO test class `BinStrTree`

	return 0;
}
#endif