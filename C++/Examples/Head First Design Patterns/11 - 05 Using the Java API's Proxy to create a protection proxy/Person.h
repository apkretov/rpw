#pragma once
#include <string>

/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/proxy/javaproxy

package headfirst.designpatterns.proxy.javaproxy;

public interface Person {
 
	String getName();
	String getGender();
	String getInterests();
	int getGeekRating();
 
    void setName(String name);
    void setGender(String gender);
    void setInterests(String interests);
    void setGeekRating(int rating); 
 
}
*/

class Person {
public:
    virtual ~Person() = default;
    
    virtual std::string getName() = 0;
    virtual std::string getGender() = 0;
    virtual std::string getInterests() = 0;
    virtual int getGeekRating() = 0;
    
    virtual void setName(const std::string& name) = 0;
    virtual void setGender(const std::string& gender) = 0;
    virtual void setInterests(const std::string& interests) = 0;
    virtual void setGeekRating(int rating) = 0;
};