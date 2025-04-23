#pragma once
#include <string>

/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/proxy/javaproxy

package headfirst.designpatterns.proxy.javaproxy;

public interface Person { // This is the interface; we'll get to the implementation in just a sec...
 
	String getName(); // Here we can get information about the person’s name, gender, interests and HotOrNot rating (1 - 10).
	String getGender();
	String getInterests();
	int getGeekRating();
 
    void setName(String name); // We can also set the same information through the respective method calls.
    void setGender(String gender);
    void setInterests(String interests);
    void setGeekRating(int rating); // setHotOrNotRating() takes an integer and adds it to the running average for this person.
 
}
*/
class Person { // This is the interface; we'll get to the implementation in just a sec...
public:
    virtual ~Person() = default;
    
    virtual std::string getName() const = 0; // Here we can get information about the person’s name, gender, interests and HotOrNot rating (1 - 10).
    virtual std::string getGender() const = 0;
    virtual std::string getInterests() const = 0;
    virtual int getGeekRating() const = 0;
    
    virtual void setName(const std::string& name) = 0; // We can also set the same information through the respective method calls.
    virtual void setGender(const std::string& gender) = 0;
    virtual void setInterests(const std::string& interests) = 0;
    virtual void setGeekRating(int rating) = 0; // setHotOrNotRating() takes an integer and adds it to the running average for this person.
};