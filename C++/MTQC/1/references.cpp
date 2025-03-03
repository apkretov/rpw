//4.2 — Global variables and linkage @ http://www.learncpp.com/cpp-tutorial/42-global-variables/

//Internal and external linkage via the static and extern keywords
//If we want to make a global variable internal (able to be used only within a single file), we can use the static keyword to do so:
static int g_x; // g_x is static, and can only be used within this file
int main() {
	return 0;
}
//Similarly, if we want to make a global variable external(able to be used anywhere in our program), we can use the extern keyword to do so:
extern double g_y(9.8); // g_y is external, and can be used by other files
int main() {
	return 0;
}
//By default, non - const variables declared outside of a block are assumed to be external. However, const variables declared outside of a block are assumed to be internal.

//Function linkage
//Functions have the same linkage property that variables do.Functions always default to external linkage, but can be set to internal linkage via the static keyword:
static int add(int x, int y) { // This function is declared as static, and can now be used only within this file. Attempts to access it via a function prototype will fail.
	return x + y;
}
//Function forward declarations don’t need the extern keyword.The compiler is able to tell whether you’re defining a function or a function prototype by whether you 
//supply a function body or not.

//File scope vs. global scope
//global.cpp:
int g_x(2); // external linkage by default
//main.cpp:
#include <iostream>
extern int g_x; // forward declaration for g_x -- g_x can be used beyond this point in this file
int main() {
	std::cout << g_x; // should print 2
	return 0;
}
//g_x has file scope within global.cpp -- it can not be directly seen outside of global.cpp.Note that even though it’s used in main.cpp, main.cpp isn’t seeing g_x, it’s 
//seeing the forward declaration of g_x(which also has file scope).The linker is responsible for linking up the definition of g_x in global.cpp with the use of g_x in 
//main.cpp.

//Global symbolic constants
//We can avoid this problem by turning these constants into const global variables, and changing the header file to hold only the variable forward declarations :
//constants.cpp :
namespace Constants {
	extern const double pi(3.14159); // actual global variables
	extern const double avogadro(6.0221413e23);
	extern const double my_gravity(9.2); // m/s^2 -- gravity is light on this planet
}
//constants.h:
#ifndef CONSTANTS_H
#define CONSTANTS_H
namespace Constants {
	extern const double pi; // forward declarations only
	extern const double avogadro;
	extern const double my_gravity;
}
#endif
//Use in the code file stays the same :
#include "constants.h"
double circumference = 2 * radius * Constants::pi;
//Now the symbolic constants will get instantiated only once(in constants.cpp), instead of once every time constants.h is #included, and the other uses will simply refer 
//to the version in constants.cpp.Any changes made to constants.cpp will require recompiling only constants.cpp.