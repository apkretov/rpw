#pragma region DuckSimulator
#include <memory>
#include <vector>
#include "MallardDuck.h"
#include "RedheadDuck.h"
#include "DuckCall.h"
#include "RubberDuck.h"

int main() {
    std::vector<std::unique_ptr<Quackable>> ducks;
    
    ducks.push_back(std::make_unique<MallardDuck>());
    ducks.push_back(std::make_unique<RedheadDuck>());
    ducks.push_back(std::make_unique<DuckCall>());
    ducks.push_back(std::make_unique<RubberDuck>());
    
    for (const auto& duck : ducks) {
        duck->quack();
    }
    
    return 0;
}
#pragma endregion //DuckSimulator