#pragma once

#include <string>
#include <iostream>
#include "WithHookCaffeineBeverage.h"
using std::cin;
using std::cout;
using std::getline;
using std::string;

#pragma region Coffee With Hook
/* Java
public class CoffeeWithHook extends CaffeineBeverageWithHook {
    public void brew() {
        System.out.println("Dripping Coffee through filter");
    }

    public void addCondiments() {
        System.out.println("Adding Sugar and Milk");
    }

    public boolean customerWantsCondiments() { // Here's where you override the hook and provide your own functionality
        String answer = getUserInput();
        
        if (answer.toLowerCase().startsWith("y")) { // Get the user's input on the condiment decision and return true or false depending on the input
            return true;
        } else {
            return false;
        }
    }

    private String getUserInput() { // This code asks the user if he'd like milk and sugar and gets his input from the command line
        String answer = null;
        
        System.out.print("Would you like milk and sugar with your coffee (y/n)? ");
        
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        try {
            answer = in.readLine();
        } catch (IOException ioe) {
            System.err.println("IO error trying to read your answer");
        }
        if (answer == null) {
            return "no";
        }
        return answer;
    }
}
*/
class CoffeeWithHook : public CaffeineBeverageWithHook {
public:
    CoffeeWithHook() = default;
    ~CoffeeWithHook() = default;
    void brew() override { cout << "Dripping Coffee through filter\n"; }
    void addCondiments() override { cout << "Adding Sugar and Milk\n"; }
    
    bool customerWantsCondiments() override { // Here's where you override the hook and provide your own functionality
        string answer = getUserInput();
        if (answer[0] == 'y' || answer[0] == 'Y') 
			return true; // Get the user's input on the condiment decision and return true or false depending on the input
        return false;
    }

private:
    string getUserInput() { // This code asks the user if he'd like milk and sugar and gets his input from the command line
        string answer;
        cout << "Would you like milk and sugar with your coffee (y/n)? ";
        if (!(getline(cin, answer))) 
			return "no";
        return answer;
    }
};

#pragma endregion //Coffee With Hook