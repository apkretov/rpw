#pragma once

#include <iostream>
#include <memory>
#include <mutex>
using namespace std;

#pragma region 2. Move to an eagerly created instance rather than a lazily created one
/* Java
public class Singleton {
	private static Singleton uniqueInstance = new Singleton(); // Go ahead and create an instance of Singleton in a static initializer. This code is guaranteed to be thread safe!
	private Singleton() {}
	public static Singleton getInstance() { return uniqueInstance; } // We've already got an instance, so just return it.
}
*/
namespace Eager {
    class Singleton {
        static unique_ptr<Singleton> uniqueInstance; // Go ahead and create an instance of Singleton in a static initializer. This code is guaranteed to be thread safe!
        Singleton() {}
    public:
		friend unique_ptr<Singleton> std::make_unique<Singleton>();
#pragma region MINE
		Singleton(const Singleton &) = delete;
		void operator=(const Singleton &) = delete;
		Singleton(Singleton &&) = default;
		Singleton &operator=(Singleton &&) = default;
#pragma endregion //MINE

		static Singleton* getInstance() { // We've already got an instance, so just return it.
			cout << uniqueInstance.get() << ": Get the instance.\n"; //MINE
			return uniqueInstance.get(); 
		} 
    };

    unique_ptr<Singleton> Singleton::uniqueInstance = make_unique<Singleton>();
} //namespace Eager
#pragma endregion //2. Move to an eagerly created instance rather than a lazily created one
