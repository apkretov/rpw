#include <memory>
#include <vector>
#include "../../stdafx.h"
#include "DuckMallard.h"
#include "DuckRedhead.h"
#include "DuckCall.h"
#include "DuckRubber.h"

#pragma region Duck reunion
int main() {
	print_file_line();

    std::vector<std::unique_ptr<Quackable>> ducks;
    
    ducks.push_back(std::make_unique<MallardDuck>());
    ducks.push_back(std::make_unique<RedheadDuck>());
    ducks.push_back(std::make_unique<DuckCall>());
    ducks.push_back(std::make_unique<RubberDuck>());
    
    for (const auto& duck : ducks) 
        duck->quack();
    
    return 0;
}
#pragma endregion //Duck reunion