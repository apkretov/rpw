#if 0

#undef SHARED_PTR
#define WEAK_PTR

#include <map>
#include <memory>
//OFF #include "vld.h"
#include "../../stdafx.h"
using namespace std;

#pragma region Amazon Q
struct Widget {
	int id;
	Widget(int i = 0) : id(i) { cout << "Widget " << id << " created\n"; }
	~Widget() { cout << "Widget " << id << " destroyed\n"; }
};
#pragma endregion //Amazon Q

#ifdef SHARED_PTR
class Cache {
	map<string, shared_ptr<Widget>> map_;
public:
	shared_ptr<Widget> GetWidget(const string &name) {
		if (!map_[name])
			map_[name] = make_shared<Widget>(map_.size() + 1); //Amazon Q //ORIG: map_[name] = make_shared<Widget>();
		return map_[name];
	}
};
#endif //SHARED_PTR

#ifdef WEAK_PTR
class Cache {
	map<string, weak_ptr<Widget>> map_;
public:
	shared_ptr<Widget> GetWidget(const string &name) {
		auto ret = map_[name].lock();
		if (!ret) {
			ret = make_shared<Widget>(map_.size() + 1); //Amazon Q //ORIG: ret = make_shared<Widget>();
			map_[name] = ret;
		}
		return ret;
	}
};
#endif //WEAK_PTR

#pragma region Amazon Q
void LeakCachedMemory() {
	Cache cache;
	{
		auto widget1 = cache.GetWidget("button");
		auto widget2 = cache.GetWidget("label");

		auto same_button = cache.GetWidget("button");

		cout << "Widget1 id: " << widget1->id << endl;
		cout << "Same_button id: " << same_button->id << endl;
		cout << "Widget2 id: " << widget2->id << endl;

		cout << "widget1 and same_button are "
			<< (widget1 == same_button ? "same" : "different")
			<< endl;
	}   // Widgets won't be destroyed here because Cache holds shared_ptr
	auto new_button = cache.GetWidget("button");
	cout << "New_button id: " << new_button->id << endl;
	// This will return the same Widget, not create a new one
}

struct Node { // Example showing how weak_ptr helps avoid memory leaks with circular references
	shared_ptr<Node> next;
#ifndef ORIG
	weak_ptr<Node> prev; // Using weak_ptr prevents circular reference  
#else //MINE
	shared_ptr<Node> prev;
#endif //MINE
	int data;

	Node(int val) : data(val) {}
	~Node() { cout << "Destroying node with value: " << data << endl; }
};

void CreateCircularReference() {
	auto node1 = make_shared<Node>(1);
	auto node2 = make_shared<Node>(2);

	node1->next = node2; // Create circular reference
	node2->prev = node1; // weak_ptr doesn't increase ref count

	cout << "Nodes going out of scope..." << endl; // When nodes go out of scope:	// - With shared_ptr for prev: Memory leak! Neither node deleted	// - With weak_ptr for prev: Both nodes properly deleted
}
#pragma endregion //Amazon Q

int main() {
	PRINT_FILE_LINE();
	LeakCachedMemory();
	CreateCircularReference();
	return 0;
}
#endif //1
