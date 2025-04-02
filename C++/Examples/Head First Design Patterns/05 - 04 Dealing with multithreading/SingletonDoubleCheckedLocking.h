#pragma once
#include <atomic>
#include <mutex>
using namespace std;

#pragma region 3. Use “double-checked locking” to reduce the use of synchronization in getInstance()
/* Java
public class Singleton {
	private volatile static Singleton uniqueInstance; // The volatile keyword ensures that multiple threads handle the uniqueInstance variable correctly when it is being initialized to the Singleton instance.
	private Singleton() {}

	public static Singleton getInstance() { // Check for an instance and if there isn't one, enter a synchronized block.
			if (uniqueInstance == null) { // Note we only synchronize the first time through!
				synchronized(Singleton.class) {
					if (uniqueInstance == null) // Once in the block, check again and if still null, create an instance.
						uniqueInstance = new Singleton(); 
				}
			}
		return uniqueInstance;
	}
}
*/
namespace DoubleCheckedLocking {
	class Singleton {
		static atomic<Singleton *> uniqueInstance; // atomic, the C++ equivalent to Java's volatile keyword in this context, ensures that multiple threads handle the uniqueInstance variable correctly when it is being initialized to the Singleton instance.
		static mutex mtx;
		Singleton() {}

#pragma region TRAE
		class Deleter { //TEST! //																															The nested deleter class is used to delete the Singleton instance when the program terminates.
		public:
			~Deleter() {
				Singleton *ptr = uniqueInstance.load(memory_order_relaxed);
				delete ptr;
			}
		};
		static Deleter deleter;  // Static deleter instance
#pragma endregion //TRAE
	public:
#pragma region MINE
		Singleton(const Singleton &) = delete;
		void operator=(const Singleton &) = delete;
		Singleton(Singleton &&) = default;
		Singleton &operator=(Singleton &&) = default;
#pragma endregion //MINE

		static Singleton *getInstance() { // Check for an instance and if there isn't one, enter a synchronized block.
			Singleton *tmp = uniqueInstance.load(memory_order_relaxed);	
			atomic_thread_fence(memory_order_acquire);
			if (tmp == nullptr) { // Note we only synchronize the first time through!
				lock_guard<mutex> lock(mtx);
				tmp = uniqueInstance.load(memory_order_relaxed);
				if (tmp == nullptr) { // Once in the block, check again and if still null, create an instance.
					tmp = new Singleton;
					atomic_thread_fence(memory_order_release);
					uniqueInstance.store(tmp, memory_order_relaxed); 
				}
			}
			cout << tmp << ": Get the instance.\n"; //MINE
			return tmp;
		}
	};

	atomic<Singleton *> Singleton::uniqueInstance{nullptr};
	mutex Singleton::mtx;
	Singleton::Deleter Singleton::deleter;
}
#pragma endregion //3. Use “double-checked locking” to reduce the use of synchronization in getInstance()
