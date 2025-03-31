#pragma once

#pragma region The Little Singleton
/* Java
publicMyClass{
	private MyClass() {}
}
*/
class MyClass {
	MyClass() {}
public:
	static MyClass &getInstance() {
		static MyClass instance;
#pragma region MINE
		cout << "MyClass::getInstance()\n";
#pragma endregion //MINE
		return instance;
	}

#pragma region MINE
	MyClass(const MyClass &) = delete;
	void operator=(const MyClass &) = delete;
	MyClass(MyClass &&) = default; //TEST // While deleting only copy controls would work due to the suppression of move operations, explicitly deleting both makes the intent clearer and provides better protection against future modifications.
	MyClass &operator=(MyClass &&) = default;
#pragma endregion //MINE
};
#pragma endregion //The Little Singleton
