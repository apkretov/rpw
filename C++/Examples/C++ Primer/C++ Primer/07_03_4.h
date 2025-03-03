#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <exception>

class Screen;

#ifndef WINDOW_MGR_H
#define WINDOW_MGR_H

class Window_mgr {
public:
    using ScreenIndex = std::vector<Screen>::size_type; // location ID for each screen on the window
    void clear(ScreenIndex); // reset the Screen at the given position to all blanks
#ifndef Scope_and_Members_Defined_Outside_the_Class
	ScreenIndex addScreen(const Screen &s);
#endif
private:
    //ORIG std::vector<Screen> screens{Screen(24, 80, ' ')};
    std::vector<Screen> screens; //MINE
};

#endif

#ifndef SCREEN_H__MEMBER_FUNCTIONS_OF_CLASS_SCREEN
#define SCREEN_H__MEMBER_FUNCTIONS_OF_CLASS_SCREEN

class Screen__Member_Functions_of_Class_Screen {
public:
    typedef std::string::size_type pos;
    Screen__Member_Functions_of_Class_Screen() = default; // needed because Screen has another constructor

    Screen__Member_Functions_of_Class_Screen(pos ht, pos wd, char c) : // cursor initialized to 0 by its in-class initializer
        height(ht), width(wd), contents(ht *wd, c) {
    }

    char get() const { // get the character at the cursor // implicitly inline
        return contents[cursor];
    }

    //ORIG inline 
	char get(pos ht, pos wd) const; // explicitly inline

    Screen__Member_Functions_of_Class_Screen &move(pos r, pos c); // can be made inline later
    //ORIG private:
protected: //MINE 
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;
};
#endif

#ifndef SCREEN_H__MUTABLE_DATA_MEMBERS
#define SCREEN_H__MUTABLE_DATA_MEMBERS

class Screen__mutable_Data_Members : public Screen__Member_Functions_of_Class_Screen { //MINE
public:
    Screen__mutable_Data_Members() = default; //MINE

    Screen__mutable_Data_Members(pos ht, pos wd, char c) : Screen__Member_Functions_of_Class_Screen(ht, wd, c) {} //MINE

    void some_member() const;
private:
    mutable size_t access_ctr{}; // may change even in a const object
    // other members as before
};
#endif

#ifndef SCREEN_H__FUNCTIONS_THAT_RETURN_THIS
#define SCREEN_H__FUNCTIONS_THAT_RETURN_THIS

class Screen__Functions_That_Return_this : public Screen__mutable_Data_Members { //MINE
public:
    Screen__Functions_That_Return_this() = default;
    Screen__Functions_That_Return_this(pos ht, pos wd, char c) : Screen__mutable_Data_Members(ht, wd, c) {}
    Screen__Functions_That_Return_this &set(char);
    Screen__Functions_That_Return_this &set(pos, pos, char);
    // other members as before
    Screen__Functions_That_Return_this &move(pos r, pos c); //MINE
};
#endif

#ifndef SCREEN_H__OVERLOADING_BASED_ON_CONST
#define SCREEN_H__OVERLOADING_BASED_ON_CONST

class Screen__Overloading_Based_on_const : public Screen__Functions_That_Return_this {
public:
    Screen__Overloading_Based_on_const() = default; //MINE
    Screen__Overloading_Based_on_const(pos ht, pos wd, char c) : Screen__Functions_That_Return_this(ht, wd, c) {} //MINE

    Screen__Overloading_Based_on_const &display(std::ostream &os) { // display overloaded on whether the object is const or not
        do_display(os); return *this;
    }

    const Screen__Overloading_Based_on_const &display(std::ostream &os) const {
        do_display(os); return *this;
    }

    Screen__Overloading_Based_on_const &set(pos ht, pos wd, char c) { //MINE
        Screen__Functions_That_Return_this::set(ht, wd, c);
        return *this;
    }

    Screen__Overloading_Based_on_const &set(char c) { //MINE
        Screen__Functions_That_Return_this::set(c);
        return *this;
    }

private:
    void do_display(std::ostream &os) const { os << contents; } // function to do the work of displaying a Screen
    // other members as before
};
#endif

#ifndef SCREEN_H
#define SCREEN_H

class Screen : public Screen__Overloading_Based_on_const {
    friend void Window_mgr::clear(ScreenIndex); // Window_mgr::clear must have been declared before class Screen
    // . . . rest of the Screen class
public:
    Screen() = default; //MINE

    Screen(pos ht, pos wd, char c) : Screen__Overloading_Based_on_const(ht, wd, c) {} //MINE
};
#endif