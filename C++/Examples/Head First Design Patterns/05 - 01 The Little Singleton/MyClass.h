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
		return instance;
	}

	MyClass(const MyClass &) = delete;
	void operator=(const MyClass &) = delete;
	MyClass(MyClass &&) = default;
	MyClass &operator=(MyClass &&) = default;
};
#pragma endregion //The Little Singleton
