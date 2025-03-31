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
	MyClass(MyClass &&) = default;
	MyClass &operator=(MyClass &&) = default;
#pragma endregion //MINE
};
#pragma endregion //The Little Singleton
