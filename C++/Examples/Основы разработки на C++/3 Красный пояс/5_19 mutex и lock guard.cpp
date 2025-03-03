#if 0

#include <future>
#include <iostream>
#include <mutex>
#include "../../stdafx.h"
using namespace std;

#undef ACCOUNT_VER2
#define ACCOUNT_VER3

#ifdef ACCOUNT_VER2
struct Account { //VER2 history added.
	int balance = 0;
	vector<int> history;

	bool Spend(int value) {
		if (value <= balance) {
			balance -= value;
			history.push_back(value);
			return true;
		}
		return false;
	}
};
#endif //ACCOUNT_VER2

#ifdef ACCOUNT_VER3
struct Account { //VER3 mutex added.
	int balance = 0;
	vector<int> history;
	mutex m;

	bool Spend(int value) {
		lock_guard g{m}; //ORIG lock_guard<mutex> g(m);
		if (value <= balance) {
			balance -= value;
			history.push_back(value);
			return true;
		}
		return false;
	}
};
#endif //ACCOUNT_VER3

int SpendMoney(Account &account) {
	int total_spent = 0;
	for (int i = 0; i < 100'000; ++i)
		if (account.Spend(1))
			++total_spent;
	return total_spent;
}

int main(int argc, char *argv[]) {
	PRINT_FILE_LINE();

	Account family_account{100'000};
	auto husband = async(SpendMoney, ref(family_account));
	auto wife = async(SpendMoney, ref(family_account));
	auto son = async(SpendMoney, ref(family_account));
	auto daughter = async(SpendMoney, ref(family_account));


#ifdef ORIG
	int spent = husband.get() + wife.get() + son.get() + daughter.get();
#else //MINE
	struct FamilySpent {
		int husband;
		int wife;
		int son;
		int daughter;
	};
	FamilySpent fs{husband.get(), wife.get(), son.get(), daughter.get()};
	cout << AS_KV(fs.husband) << '\n' 
		<< AS_KV(fs.wife) << '\n' 
		<< AS_KV(fs.son) << '\n' 
		<< AS_KV(fs.daughter) << '\n';
	int spent = fs.husband + fs.wife + fs.son + fs.daughter;
#endif //MINE
	cout << "Total spent: " << spent << endl //TEST //																										MINE: Total spent: 306464		Balance : 0
		<< "Balance: " << family_account.balance << endl;

	return 0;
}
#endif //1

#ifdef PERPLEXITY //In summary, while std::scoped_lock provides enhanced functionality for managing multiple locks and preventing deadlocks, std::lock_guard remains a valuable tool in scenarios that prioritize simplicity, performance for single locks, compatibility with legacy code, or specific use cases where only one mutex is involved.

#ifdef LOCK_GUARD //Explanation of Deadlock //Thread A locks mutex1 and then tries to lock mutex2. //Thread B locks mutex2 and then tries to lock mutex1. //If both threads reach their respective sleep statements at the same time, they will end up waiting indefinitely for each other to release the locks, resulting in a deadlock.

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

mutex mutex1;
mutex mutex2;

void threadA() {
	lock_guard<mutex> guard1(mutex1); // Lock mutex1
	cout << "Thread A acquired mutex1\n";
	this_thread::sleep_for(chrono::milliseconds(100)); // Simulate work
	lock_guard<mutex> guard2(mutex2); // Attempt to lock mutex2
	cout << "Thread A acquired both locks\n";
}

void threadB() {
	lock_guard<mutex> guard1(mutex2); // Lock mutex2
	cout << "Thread B acquired mutex2\n";
	this_thread::sleep_for(chrono::milliseconds(100)); // Simulate work
	lock_guard<mutex> guard2(mutex1); // Attempt to lock mutex1
	cout << "Thread B acquired both locks\n";
}

int main() {
	thread t1(threadA);
	thread t2(threadB);

	t1.join();
	t2.join();

	return 0;
}
#endif // LOCK_GUARD

#ifdef SCOPED_LOCK //Explanation of Deadlock Prevention //In this version, both threads attempt to lock mutex1 and mutex2 using std::scoped_lock. //Since std::scoped_lock locks both mutexes in a single operation, it prevents the situation where one thread holds one lock while waiting for another, and vice versa.

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

mutex mutex1;
mutex mutex2;

void threadA() {
	scoped_lock lock(mutex1, mutex2); // Lock both mutexes at once
	cout << "Thread A acquired both locks\n";
}

void threadB() {
	scoped_lock lock(mutex1, mutex2); // Lock both mutexes at once
	cout << "Thread B acquired both locks\n";
}

int main() {
	thread t1(threadA);
	thread t2(threadB);

	t1.join();
	t2.join();

	return 0;
}
#endif //SCOPED_LOCK

#endif //PERPLEXITY
