#pragma once

#include <memory>
using namespace std;

#pragma region Dissecting the classic Singleton Pattern implementation
/* Java
public class Singleton { // Let's rename MyClass to Singleton.
	private static Singleton uniqueInstance; // We have a static variable to hold our one instance of the class Singleton.
	// other useful instance variables here
	private Singleton() {} // Our constructor is declared private; only Singleton can instantiate this class!
	public static Singleton getInstance() { // The getInstance() method gives us a way to instantiate the class and also to return an instance of it.
		if (uniqueInstance == null) // uniqueInstance holds our ONE instance; remember, it is a static variable.
			uniqueInstance = new Singleton(); // If uniqueInstance is null, then we haven't created the instance yet... // ...and, if it doesn't exist, we instantiate Singleton through its private constructor and assign it to uniqueInstance. Note that if we never need the instance, it never gets created; this is lazy instantiation.
		return uniqueInstance; // If uniqueInstance wasn't null, then it was previously created. We just fall through to the return statement.
	}
	// other useful methods here
}
*/
class Singleton { // Let's rename MyClass to Singleton.
private:
	static unique_ptr<Singleton> uniqueInstance; // We have a static variable to hold our one instance of the class Singleton.
	// other useful instance variables here
	Singleton() {} // Our constructor is declared private; only Singleton can instantiate this class!
public:
	friend unique_ptr<Singleton> std::make_unique<Singleton>(); //TEST!! // This is a friend declaration, which allows make_unique to access the private constructor of Singleton.

	static Singleton *getInstance() { // The getInstance() method gives us a way to instantiate the class and also to return an instance of it.
		if (uniqueInstance == nullptr) // uniqueInstance holds our ONE instance; remember, it is a static variable.
			uniqueInstance = make_unique<Singleton>(); //TEST! // If uniqueInstance is null, then we haven't created the instance yet... // ...and, if it doesn't exist, we instantiate Singleton through its private constructor and assign it to uniqueInstance. Note that if we never need the instance, it never gets created; this is lazy instantiation.
#pragma region MINE
		cout << "Singleton::getInstance()\n";
#pragma endregion //MINE
		return uniqueInstance.get(); // If uniqueInstance wasn't null, then it was previously created. We just fall through to the return statement.
	}
#pragma region MINE
	Singleton(const Singleton &) = delete;
	void operator=(const Singleton &) = delete;
	Singleton(Singleton &&) = default;
	Singleton &operator=(Singleton &&) = default;
#pragma endregion //MINE
	// other useful methods here
};

unique_ptr<Singleton> Singleton::uniqueInstance = nullptr; // Initialize the static member 
#pragma endregion //Dissecting the classic Singleton Pattern implementation
