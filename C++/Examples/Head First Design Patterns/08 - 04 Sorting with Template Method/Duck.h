#pragma once

#include <string>
using std::string;
using std::to_string;

#pragma region Comparing Ducks and Ducks
/* Java
public class Duck implements Comparable {
    String name;
    int weight;

    public Duck(String name, int weight) {
        this.name = name;
        this.weight = weight;
    }

    public String toString() {
        return name + " weighs " + weight;
    }

    public int compareTo(Object object) {
        Duck otherDuck = (Duck)object;

        if (this.weight < otherDuck.weight)
            return -1;
        else if (this.weight == otherDuck.weight)
            return 0;
        else
            return 1;
    }
}
*/
class Duck {
    string name_; // Our Ducks have a name and a weight
    int weight_;
public:
    Duck(string name, int weight) : name_(name), weight_(weight) {} // Remember, we need to implement the Comparable interface since we aren't really subclassing
    string toString() const { return name_ + " weighs " + to_string(weight_); } // We're keepin' it simple; all Ducks do is print their name and weight!

    int compareTo(Duck* otherDuck) const { // compareTo() takes another Duck to compare THIS Duck to
        if (this->weight_ < otherDuck->weight_)
            return -1;
        else if (this->weight_ == otherDuck->weight_) // Here's where we specify how Ducks compare. If THIS Duck weighs less than otherDuck then we return -1; if they are equal, we return 0; and if THIS Duck weighs more, we return 1
            return 0;
        else
            return 1;
    }
};
#pragma endregion //Comparing Ducks and Ducks