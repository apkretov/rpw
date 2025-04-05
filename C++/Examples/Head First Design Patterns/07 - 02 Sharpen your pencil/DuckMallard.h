#pragma once

#include <iostream> 
#include "Duck.h"
using std::cout;

#pragma region Heres a subclass of Duck, the MallardDuck //Here's a subclass of Duck, the MallardDuck
/* Java
public class MallardDuck implements Duck {
	public void quack() { System.out.println("Quack"); } // Simple implementations: the duck just prints out what it is doing.
	public void fly() { System.out.println("I'm flying"); }
}
*/
class MallardDuck final : public Duck {
public:
    void quack() override { cout << "Quack\n"; } // Simple implementations: the duck just prints out what it is doing.
    void fly() override { cout << "I'm flying\n"; }
};
#pragma endregion //Heres a subclass of Duck, the MallardDuck
