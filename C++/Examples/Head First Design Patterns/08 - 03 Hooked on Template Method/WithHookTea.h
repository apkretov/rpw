#pragma once

#include <string>
#include <iostream>
#include "WithHookCaffeineBeverage.h"
using std::cin;
using std::cout;
using std::getline;
using std::string;

#pragma region MINE
class TeaWithHook : public CaffeineBeverageWithHook {
public:
    TeaWithHook() = default;
    ~TeaWithHook() = default;
    void brew() override { cout << "Steeping the tea\n"; }
    void addCondiments() override { cout << "Adding Lemon\n"; }
    
    bool customerWantsCondiments() override {            
        string answer = getUserInput();
        if (answer[0] == 'y' || answer[0] == 'Y') 
            return true;                  
        return false;
    }

private:
    string getUserInput() {             
        string answer;
        cout << "Would you like lemon with your tea (y/n)? ";
        if (!(getline(cin, answer))) 
            return "no";
        return answer;
    }
};
#pragma endregion //MINE