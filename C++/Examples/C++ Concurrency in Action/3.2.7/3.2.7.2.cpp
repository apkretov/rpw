#ifndef MINE // A simple example of the gateway class pattern

#include <mutex>
#include <iostream>
#include "../../stdafx.h"
using namespace std;

class ProtectedData {
	int data_ = 0;
public:
	void set(int value) { data_ = value; }
	int get() const { return data_; }
};

class DataLockGateway {
	unique_lock<mutex> lock_; // While std::unique_lock is useful when you need to hold a mutex locked, its features aren’t fully utilized in this particular use case. A simple std::lock_guard would be enough.
	ProtectedData& data_;
public:
	DataLockGateway(mutex& mtx, ProtectedData& data) : lock_(mtx), data_(data) {} // Construct by locking the passed mutex and referencing data
	DataLockGateway(DataLockGateway&&) noexcept = default; // Movable but not copyable
	DataLockGateway& operator=(DataLockGateway&&) noexcept = default;
	void setData(int val) { data_.set(val); } // Access to data through members
	int getData() const { return data_.get(); }
};

ProtectedData sharedData;
mutex mtx;

DataLockGateway get_lock() { return DataLockGateway(mtx, sharedData); } // Safely access and modify protected data

int main() {
	print_file_line();
	{
		auto gateway = get_lock(); // Acquire lock through a gateway object
		gateway.setData(42); // Safely access and modify protected data
		cout << "Data: " << gateway.getData() << "\n";
	} // Lock is released when gateway goes out of scope here
	// Other threads can now access the data safely
	return 0;
}
#endif //MINE
