#pragma once
#include "Person.h"
#include <stdexcept>
#include <memory>

/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/proxy/javaproxy

package headfirst.designpatterns.proxy.javaproxy;
 
import java.lang.reflect.*;
 
public class OwnerInvocationHandler implements InvocationHandler { 
	Person person;
 
	public OwnerInvocationHandler(Person person) {
		this.person = person;
	}
 
	public Object invoke(Object proxy, Method method, Object[] args) 
			throws IllegalAccessException {
  
		try {
			if (method.getName().startsWith("get")) {
				return method.invoke(person, args);
   			} else if (method.getName().equals("setGeekRating")) {
				throw new IllegalAccessException();
			} else if (method.getName().startsWith("set")) {
				return method.invoke(person, args);
			} 
        } catch (InvocationTargetException e) {
            e.printStackTrace();
        } 
		return null;
	}
}
*/

class OwnerProxy : public Person {
private:
    std::shared_ptr<Person> person;

public:
    explicit OwnerProxy(std::shared_ptr<Person> p) : person(p) {}

    std::string getName() override { return person->getName(); }
    std::string getGender() override { return person->getGender(); }
    std::string getInterests() override { return person->getInterests(); }
    int getGeekRating() override { return person->getGeekRating(); }

    void setName(const std::string& name) override { person->setName(name); }
    void setGender(const std::string& gender) override { person->setGender(gender); }
    void setInterests(const std::string& interests) override { person->setInterests(interests); }
    void setGeekRating(int) override { 
        throw std::runtime_error("Owners can't set their own rating");
    }
};