#pragma once

#include "Person.h"
#include <stdexcept>
#include <memory>

#pragma region Creating Invocation Handlers continued...
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/proxy/javaproxy
package headfirst.designpatterns.proxy.javaproxy;

import java.lang.reflect.*; // InvocationHandler is part of the java.lang.reflect package, so we need to import it.

public class OwnerInvocationHandler implements InvocationHandler { // All invocation handlers implement the InvocationHandler interface.
	Person person;

	public OwnerInvocationHandler(Person person) { // We're passed the	Real Subject in the constructor and we keep a reference to it.
		this.person = person;
	}

	public Object invoke(Object proxy, Method method, Object[] args) // Here's the invoke method that gets called every time a method is invoked on the proxy.
			throws IllegalAccessException {

		try {
			if (method.getName().startsWith("get")) { // If the method is a getter, we go ahead and invoke it on the real subject.
				return method.invoke(person, args);
			} else if (method.getName().equals("setGeekRating")) { // Otherwise, if it is the setHotOrNotRating() method we disallow it by throwing a IllegalAccessException.
				throw new IllegalAccessException();
			} else if (method.getName().startsWith("set")) { // Because we are the owner any other set method is fine and we go ahead and invoke it on the real subject.
				return method.invoke(person, args);
			}
		} catch (InvocationTargetException e) { // This will happen if the real subject throws an exception.
			e.printStackTrace();
		}
		return null; // If any other method is called, we're just going to return null rather than take a chance.
	}
}
*/
class OwnerProxy : public Person {
	using string = std::string;
	PersonPtr person;
public:
	explicit OwnerProxy(PersonPtr p) : person(p) {} // We're passed the	Real Subject in the constructor and we keep a reference to it.

	string getName() const override { return person->getName(); } // If the method is a getter, we go ahead and invoke it on the real subject.
	string getGender() const override { return person->getGender(); }
	string getInterests() const override { return person->getInterests(); }
	int getGeekRating() const override { return person->getGeekRating(); }

	void setName(const string &name) override { person->setName(name); } // Because we are the owner any other set method is fine and we go ahead and invoke it on the real subject.
	void setGender(const string &gender) override { person->setGender(gender); }
	void setInterests(const string &interests) override { person->setInterests(interests); }
	void setGeekRating(int) override { throw std::runtime_error("Owners can't set their own rating"); } // Otherwise, if it is the setHotOrNotRating() method we disallow it by throwing a IllegalAccessException.
};
#pragma endregion //Creating Invocation Handlers continued...
