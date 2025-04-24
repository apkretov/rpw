#pragma region Duck reunion
#include "DuckSimulator.h"
#include "MallardDuck.h"
#include "RedheadDuck.h"
#include "DuckCall.h"
#include "RubberDuck.h"
#include <iostream>
#include <memory>

void DuckSimulator::simulate() {
    std::unique_ptr<Quackable> mallardDuck = std::make_unique<MallardDuck>();
    std::unique_ptr<Quackable> redheadDuck = std::make_unique<RedheadDuck>();
    std::unique_ptr<Quackable> duckCall = std::make_unique<DuckCall>();
    std::unique_ptr<Quackable> rubberDuck = std::make_unique<RubberDuck>();

    std::cout << "\nDuck Simulator" << std::endl;

    simulate(mallardDuck.get());
    simulate(redheadDuck.get());
    simulate(duckCall.get());
    simulate(rubberDuck.get());
}

void DuckSimulator::simulate(Quackable* duck) {
    duck->quack();
}

int main() {
    DuckSimulator simulator;
    simulator.simulate();
    return 0;
}
#pragma endregion //Duck reunion