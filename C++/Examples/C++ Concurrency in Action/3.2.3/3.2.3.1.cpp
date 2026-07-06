#ifdef MINE_UNSAFE //## Unsafe Race in Doubly Linked List Delete (minimal changes)

#include <iostream> //** Problem** : Individual node mutexes fail; concurrent delete races on prev/next.
#include <mutex>
#include <memory>
#include <thread>
#include <vector>
#include <chrono>
#include "../../stdafx.h"

struct Node {
	explicit Node(int d) : data(d) {}
	int data;
	std::shared_ptr<Node> prev;
	std::shared_ptr<Node> next;
	std::mutex mtx; // per-node mutex (insufficient by itself)
};

class SafeList { // now unsafe: per-node locking is used but inconsistent
	std::shared_ptr<Node> head; // removed list-wide mutex
public:
	void push_front(int data) {
		auto new_node = std::make_shared<Node>(data);
		if (head) { // only lock the old head (if any) while linking; head assignment is unprotected
			std::scoped_lock lk(head->mtx);
			new_node->next = head;
			head->prev = new_node; // modifies head->prev while only head is locked
		} else {
			new_node->next = nullptr;
		}
		head = new_node; // race: head changed without global protection
	}

	bool erase(int data) {
		auto curr = head;
		while (curr) {
			std::scoped_lock lk(curr->mtx); // lock only curr
			if (curr->data == data) {
				if (curr->prev) {
					std::scoped_lock lk2(curr->prev->mtx); // lock prev while updating its next, but we don't lock next
					curr->prev->next = curr->next;
				} else {
					head = curr->next; // head assignment unprotected
				}
				if (curr->next)
					curr->next->prev = curr->prev; // updates next->prev without locking next
				return true;
			}
			curr = curr->next; // moving to next without locking it first => TOCTOU
		}
		return false;
	}

	std::vector<int> snapshot() { // thread-unsafe snapshot due to no global lock
		std::vector<int> out;
		auto curr = head;
		while (curr) {
			std::scoped_lock lk(curr->mtx); // lock node briefly while reading its data, but pointer traversal is still racy
			out.push_back(curr->data);
			curr = curr->next; // next may change concurrently
		}
		return out;
	}
};

static void print_snapshot(std::mutex& cout_mtx, const char* tag, int op_val, bool ok, const std::vector<int>& snap) {
	std::lock_guard lg(cout_mtx);
	if (op_val >= 0) {
		if (ok)
			std::cout << tag << " " << op_val << " succeeded -> [";
		else
			std::cout << tag << " " << op_val << " failed    -> [";
	} else
		std::cout << tag << " -> [";
	for (size_t j = 0; j < snap.size(); ++j) {
		if (j) std::cout << ',';
		std::cout << snap[j];
	}
	std::cout << "]\n";
}

int main() {
	print_file_line();

	SafeList list;
	constexpr int N = 5;
	std::mutex cout_mtx;

	print_snapshot(cout_mtx, "Initial", -1, true, list.snapshot());
	{
		std::jthread producer([&list, &cout_mtx]() {
			for (int i = 0; i < N; ++i) {
				list.push_front(i);
				auto snap = list.snapshot();
				print_snapshot(cout_mtx, "Producer pushed", i, true, snap);
				std::this_thread::sleep_for(std::chrono::microseconds(10));
			}
		});

		std::jthread remover([&list, &cout_mtx]() {
			for (int i = 0; i < N; ++i) {
				bool removed = list.erase(i);
				auto snap = list.snapshot();
				print_snapshot(cout_mtx, "Remover erase", i, removed, snap);
				std::this_thread::sleep_for(std::chrono::microseconds(15));
			}
		});
	} // jthreads joined here

	print_snapshot(cout_mtx, "Final list", -1, true, list.snapshot());

	std::cout << "Concurrent push/erase finished (may crash or corrupt state)\n";

	return 0;
}
#endif //MINE_UNSAFE

#ifndef MINE_SAFE //## Race in Doubly Linked List Delete
//** Problem** : Individual node mutexes fail; concurrent delete races on prev/next.
//* *Fixed * *: Single list mutex protects whole operation. (Code shows safe version; race version omitted for simplicity.)

#include <iostream>
#include <mutex>
#include <memory>
#include <thread>
#include <vector>
#include <chrono>
#include "../../stdafx.h"

struct Node {
	explicit Node(int d) : data(d) {}
	int data;
	std::shared_ptr<Node> prev;
	std::shared_ptr<Node> next;
};

class SafeList {
	std::mutex mtx;
	std::shared_ptr<Node> head;
public:
	void push_front(int data) {
		std::scoped_lock lock(mtx);
		auto new_node = std::make_shared<Node>(data);
		new_node->next = head;
		if (head)
			head->prev = new_node;
		head = new_node;
	}

	bool erase(int data) {
		std::scoped_lock lock(mtx);
		auto curr = head;
		while (curr) {
			if (curr->data == data) {
				if (curr->prev)
					curr->prev->next = curr->next;
				else
					head = curr->next;
				if (curr->next)
					curr->next->prev = curr->prev;
				return true;
			}
			curr = curr->next;
		}
		return false;
	}

	std::vector<int> snapshot() { // Thread-safe snapshot of current list contents (front -> back).
		std::vector<int> out;
		std::scoped_lock lock(mtx);
		auto curr = head;
		while (curr) {
			out.push_back(curr->data);
			curr = curr->next;
		}
		return out;
	}
};

static void print_snapshot(std::mutex& cout_mtx, const char* tag, int op_val, bool ok, const std::vector<int>& snap) {
	std::lock_guard lg(cout_mtx);
	if (op_val >= 0) {
		if (ok)
			std::cout << tag << " " << op_val << " succeeded -> [";
		else
			std::cout << tag << " " << op_val << " failed    -> [";
	} else
		std::cout << tag << " -> [";
	for (size_t j = 0; j < snap.size(); ++j) {
		if (j) std::cout << ',';
		std::cout << snap[j];
	}
	std::cout << "]\n";
}

int main() {
	print_file_line();

	SafeList list;
	constexpr int N = 5;
	std::mutex cout_mtx;

	print_snapshot(cout_mtx, "Initial", -1, true, list.snapshot()); // print initial empty list

	{
		std::jthread producer([&list, &cout_mtx]() {
			for (int i = 0; i < N; ++i) {
				list.push_front(i);
				auto snap = list.snapshot();
				print_snapshot(cout_mtx, "Producer pushed", i, true, snap);
				std::this_thread::sleep_for(std::chrono::microseconds(10));
			}
		});

		std::jthread remover([&list, &cout_mtx]() {
			for (int i = 0; i < N; ++i) {
				bool removed = list.erase(i);
				auto snap = list.snapshot();
				print_snapshot(cout_mtx, "Remover erase", i, removed, snap);
				std::this_thread::sleep_for(std::chrono::microseconds(15));
			}
		});
	} // jthreads are joined here

	print_snapshot(cout_mtx, "Final list", -1, true, list.snapshot()); // final list

	std::cout << "Concurrent push/erase finished (no crash)\n";

	return 0;
}
#endif //MINE_SAFE
