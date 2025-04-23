#pragma once

#include "Person.h"
#include <stdexcept>
#include <memory>

#pragma region Exercise
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
	using string = std::string;
	Person* person;  // Changed from std::shared_ptr<Person>
public:
	explicit NonOwnerProxy(Person* p) : person(p) {}  // Changed from shared_ptr to raw pointer

	string getName() const override { return person->getName(); }
	string getGender() const override { return person->getGender(); }
	string getInterests() const override { return person->getInterests(); }
	int getGeekRating() const override { return person->getGeekRating(); }

	void setName(const string &) override { throw std::runtime_error("Non-owners can't modify the profile"); }
	void setGender(const string &) override { throw std::runtime_error("Non-owners can't modify the profile"); }
	void setInterests(const string &) override { throw std::runtime_error("Non-owners can't modify the profile"); }
	void setGeekRating(int rating) override { person->setGeekRating(rating); }
};
#pragma endregion //Exercise
