#pragma once
#include "Person.h"
#include <stdexcept>
#include <memory>

/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/proxy/javaproxy

package headfirst.designpatterns.proxy.javaproxy;
 
import java.lang.reflect.*;
 
public class NonOwnerInvocationHandler implements InvocationHandler { 
	Person person;
 
	public NonOwnerInvocationHandler(Person person) {
		this.person = person;
	}
 
	public Object invoke(Object proxy, Method method, Object[] args) 
			throws IllegalAccessException {
  
		try {
			if (method.getName().startsWith("get")) {
				return method.invoke(person, args);
   			} else if (method.getName().equals("setGeekRating")) {
				return method.invoke(person, args);
			} else if (method.getName().startsWith("set")) {
				throw new IllegalAccessException();
			} 
        } catch (InvocationTargetException e) {
            e.printStackTrace();
        } 
		return null;
	}
}
*/

class NonOwnerProxy : public Person {
private:
    std::shared_ptr<Person> person;

public:
    explicit NonOwnerProxy(std::shared_ptr<Person> p) : person(p) {}

    std::string getName() const override { return person->getName(); }
    std::string getGender() const override { return person->getGender(); }
    std::string getInterests() const override { return person->getInterests(); }
    int getGeekRating() const override { return person->getGeekRating(); }

    void setName(const std::string&) override { 
        throw std::runtime_error("Non-owners can't modify the profile");
    }
    void setGender(const std::string&) override { 
        throw std::runtime_error("Non-owners can't modify the profile");
    }
    void setInterests(const std::string&) override { 
        throw std::runtime_error("Non-owners can't modify the profile");
    }
    void setGeekRating(int rating) override { 
        person->setGeekRating(rating);
    }
};