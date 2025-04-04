#pragma once

#include <iostream>
#include "Turkey.h"
using std::cout;

#pragma region Now its time to meet the newest fowl on the block //Now it's time to meet the newest fowl on the block
/* Java
public class WildTurkey implements Turkey {
	public void gobble() { System.out.println("Gobble gobble"); } // Here's a concrete implementation of Turkey; like Duck, it just prints out its actions.
	public void fly() { System.out.println("I'm flying a short distance"); }
}
*/
class WildTurkey final : public Turkey {
public:
    void gobble() override { cout << "Gobble gobble\n"; } // Here's a concrete implementation of Turkey; like Duck, it just prints out its actions.
    void fly() override { cout << "I'm flying a short distance\n"; }
};
#pragma endregion //Now its time to meet the newest fowl on the block