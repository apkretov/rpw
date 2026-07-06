#ifdef MINE // A simple example of the gateway class pattern. Why? See the note below.

#include <mutex>
#include <iostream>
#include <thread>
#include "../../stdafx.h"
using namespace std;

class ProtectedData {
public:
	void set(int value) { data = value; }
	int get() const { return data; }
private:
	int data = 0;
};

class DataLockGateway {
public:
	DataLockGateway(mutex& mtx, ProtectedData& data) : lock(mtx), data(data) {} // Construct by locking the passed mutex and referencing data
	DataLockGateway(DataLockGateway&&) noexcept = default; // Movable but not copyable
	DataLockGateway& operator=(DataLockGateway&&) noexcept = default;
	void setData(int val) { data.set(val); } // Access to data through members
	int getData() const { return data.get(); }
private:
	unique_lock<mutex> lock; // While std::unique_lock is useful when you need to hold a mutex locked, its features aren't fully utilized in this particular use case. A simple std::lock_guard would be enough.
	ProtectedData& data;
};

ProtectedData sharedData;
mutex mtx;

DataLockGateway get_lock() { return DataLockGateway(mtx, sharedData); } // Safely access and modify protected data

void reader_thread_func() { // Function for a reader thread to safely access shared data
    auto reader_gateway = get_lock(); // Acquire lock through gateway
    cout << "Reader thread sees data: " << reader_gateway.getData() << '\n';
    // Lock is released when reader_gateway goes out of scope
}

int main() {
	print_file_line();
	{
		auto gateway = get_lock(); // Acquire lock through a gateway object
		gateway.setData(42); // Safely access and modify protected data
		cout << "Main thread set data to: " << gateway.getData() << '\n';
	} // Lock is released when gateway goes out of scope here

	jthread reader_thr(reader_thread_func); // Spawn a new thread that will access the data after the main thread has released the lock.
	reader_thr.join(); // Wait for the reader thread to complete its execution.
	// Other threads can now access the data safely

	return 0;
}
#endif //MINE

/*
Why bother with the gateway class pattern when there are so many alternatives? What's its specific use case and benefit?

Gateway class adds overhead (extra class, indirection), so alternatives like std::lock_guard or direct unique_lock are preferred for simplicity. But it shines in specific concurrency scenarios where alternatives fail.[46]
Specific Use Cases
•	Dynamic mutex selection: Mutex depends on runtime state (e.g., data ID → sharded mutex array). Direct lock can't hide this logic.
DataGateway gw(data_id);  // Internally picks mutex[data_id % N]

•	Encapsulate complex locking: Multiple mutexes, hierarchical locks (avoids deadlock), or conditional locking.
•	Policy-based locking: Lock only if needed, or upgrade from reader to writer lock.
•	Interface abstraction: Clients access data without knowing mutex details (encapsulation).
Textbook case: Mutex choice based on "program state or arguments" → gateway computes it once on construction.
Key Benefits (Worth the Bother)
•	Explicit scope control: Lock lifetime matches gateway variable (RAII perfection).
•	Encapsulation: Hides "how/which mutex" from client code.
•	Movable: Transfer ownership (via unique_lock).
•	Composable: Chain gateways for multi-lock protection.
•	Self-documenting: { DataGateway gw(data); ... } screams "locked scope".

When NOT to Bother
Scenario			Use Alternative
Single static mutex	std::lock_guard (zero cost)
Simple defer-lock	Direct unique_lock
No dynamic logic	Function returning unique_lock

Bottom line: Use gateway for locking complexity; otherwise, simpler RAII wins performance/simplicity. Seen in libraries like folly's fbmutex wrappers or sharded caches.
*/

#ifdef MINE_GATEWAY_1 // 1. Dynamic Mutex Selection: Gateway picks mutex by ID (sharded). Client unaware of sharding.

#include <array>
#include <mutex>
#include <print>
#include <thread>
#include "../../stdafx.h"

std::array<std::mutex, 4> shards;
std::array<int, 4> data;

class ShardGateway {
	std::unique_lock<std::mutex> lock;	
	/* MINE std::scoped_lock<std::mutex> lock;	Why not just std::scoped_lock?
												std::scoped_lock "works" due to copy elision (NRVO) — 
												compiler builds ShardGateway directly in caller's stack. 
												No move happens.

												But fragile:
												-fno-elide-constructors → compile error
												std::optional<ShardGateway> opt = get_shard(5); → fails
												std::vector.emplace_back(get_shard(5)); → fails
												scoped_lock is deliberately non-movable (by design).

												Use unique_lock for portable gateways that work everywhere.*/
	int& value;
public:
	explicit ShardGateway(int id) : lock(shards[id % 4]), value(data[id % 4]) {}
	int get() const { return value; }
	void set(int v) { value = v; }
};

ShardGateway get_shard(int id) { return ShardGateway(id); }

int main() {
	print_file_line();

	std::jthread t1([] {
		auto gw1 = get_shard(5);  // Locks shards[1]
		gw1.set(42);
		std::print("Thread {}: {}\n", std::this_thread::get_id(), gw1.get()); // 42
	});

	std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work.
	auto gw2 = get_shard(9);  // Locks shards[1] (different thread OK)
	std::print("Main thread {}: {}\n", std::this_thread::get_id(), gw2.get()); // 42 (same shard, but different thread can access after t1 releases lock)
}
#endif //MINE_GATEWAY_1

#ifdef MINE_GATEWAY_2 // 2. Encapsulate Complex Locking: Gateway locks 2 mutexes atomically (deadlock - free).

#include <mutex>
#include <iostream>
#include "../../stdafx.h"

std::mutex mtxA;
std::mutex mtxB;
int acctA = 100;
int acctB = 200;

class TransferGateway {
	std::scoped_lock<std::mutex, std::mutex> sl{mtxA, mtxB}; // Locks both mtxA and mtxB atomically (deadlock-free)
public:
	void transfer(int amount) const {
		if (acctA >= amount) {
			acctA -= amount;
			acctB += amount;
		}
	}
};

int main() {
	print_file_line();

	TransferGateway gw;
	std::cout << "Before transfer: " << acctA << " " << acctB << "\n"; // 100 200
	gw.transfer(50);
	std::cout << "After transfer: " << acctA << " " << acctB << "\n"; // 50 250
}
#endif // MINE_GATEWAY_2

#ifdef MINE_GATEWAY_3 // 3. Policy-Based Locking: Gateway locks only when needed (read-only optimization).

#include <mutex>
#include <iostream>

std::mutex mtx;
int data = 0;

class SmartGateway {
	std::unique_lock<std::mutex> lock{mtx, std::defer_lock};
	bool needs_lock;
public:
	explicit SmartGateway(bool write_mode) : needs_lock(write_mode) {
		if (needs_lock) 
			lock.lock();
	}

	int read() const { return ::data; }
	void write(int v) const { ::data = v; } // Assumes lock held
};

int main() {
	SmartGateway read(false); // No lock!
	std::cout << read.read() << "\n"; // Fast read

	SmartGateway write(true); // Locks
	write.write(42);
	std::cout << write.read() << "\n"; // Longer read under lock
}
#endif //MINE_GATEWAY_3	

#ifndef MINE_GATEWAY_4 // 4. Interface Abstraction: Client sees clean API, hides all mutex details.

#include <mutex>
#include <iostream>
#include "../../stdafx.h"

class BankAccount {
	std::mutex mtx;
	int balance = 0;
public:
	class Access {
		std::unique_lock<std::mutex> lock;
		int& bal;
	public:
		explicit Access(BankAccount& acc) : lock(acc.mtx), bal(acc.balance) {}
		int get() const { return bal; }
		void deposit(int x) { bal += x; }
	};

	Access access() { return Access(*this); }
};

int main() {
	print_file_line();

	BankAccount acct;
	{
		auto acc = acct.access();  // "I'm locked now"
		acc.deposit(100);
		std::cout << acc.get() << "\n";  // 100
	}  // Auto unlock

	{
		auto acc = acct.access();  // "I'm locked again"
		std::cout << acc.get() << "\n";  // 100
		acc.deposit(100);
		std::cout << acc.get() << "\n";  // 200
	}  // Auto unlock
}
#endif //MINE_GATEWAY_4