#pragma once

#include <iostream>
#include <memory>
#include <mutex>
using namespace std;

#pragma region Dealing with multithreading
/* Java
public class Singleton {
	private static Singleton uniqueInstance;
	// other useful instance variables here
	private Singleton() {}
	public static synchronized Singleton getInstance() { // By adding the synchronized keyword to getInstance(), we force every thread to wait its turn before it can enter the method.That is, no two threads may enter the method at the same time.
		if (uniqueInstance == null) {
			uniqueInstance = new Singleton();
		}
		return uniqueInstance;
	}
	// other useful methods here
}
*/
namespace Lazy {
	class Singleton {
		static unique_ptr<Singleton> uniqueInstance;
		static mutex mtx;
		// other useful instance variables here
		Singleton() {} // Private constructor
	public:
		friend unique_ptr<Singleton> std::make_unique<Singleton>();
#pragma region MINE
		Singleton(const Singleton &) = delete;
		void operator=(const Singleton &) = delete;
		Singleton(Singleton &&) = default;
		Singleton &operator=(Singleton &&) = default;
#pragma endregion //MINE

		static Singleton *getInstance() {
			lock_guard<mutex> lock(mtx); // Lock the mutex to ensure thread safety
			if (uniqueInstance == nullptr)
				uniqueInstance = make_unique<Singleton>();
			cout << uniqueInstance.get() << ": Get the instance.\n"; //MINE
			return uniqueInstance.get();
		}
		// other useful methods here
	};

	unique_ptr<Singleton> Singleton::uniqueInstance = nullptr; // Initialize static members
	mutex Singleton::mtx;
} //namespace Lazy
#pragma endregion //Dealing with multithreading
