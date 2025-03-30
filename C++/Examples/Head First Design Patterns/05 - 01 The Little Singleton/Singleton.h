#pragma once

/* Java
public class Singleton {
	private static Singleton uniqueInstance;
	// other useful instance variables here
	private Singleton() {}
	public static Singleton getInstance() {
		if (uniqueInstance == null) 
			uniqueInstance = new Singleton();
		return uniqueInstance;
	}
	// other useful methods here
}
*/
class Singleton {
private:
    static Singleton* uniqueInstance;
    // other useful instance variables here
    Singleton() {}
public:
    static Singleton* getInstance() {
        if (uniqueInstance == nullptr)
            uniqueInstance = new Singleton();
        return uniqueInstance;
    }
    // other useful methods here
};

Singleton* Singleton::uniqueInstance = nullptr; // Initialize the static member