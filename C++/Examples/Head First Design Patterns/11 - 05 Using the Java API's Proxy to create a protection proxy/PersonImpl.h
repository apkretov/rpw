#pragma once
#include "Person.h"

#pragma region The PersonBean implementation
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/proxy/javaproxy
package headfirst.designpatterns.proxy.javaproxy;

public class PersonImpl implements Person { // The PersonBeanImpl implements the PersonBean interface
	String name; // The instance variables.
	String gender;
	String interests;
	int rating;
	int ratingCount = 0;

	public String getName() { // All the getter methods; they each return the appropriate instance variable...
		return name;
	}

	public String getGender() {
		return gender;
	}

	public String getInterests() {
		return interests;
	}

	public int getGeekRating() { // ...except for getHotOrNotRating(), which computes the average of the ratings by dividing the ratings by the ratingCount.
		if (ratingCount == 0) return 0;
		return (rating/ratingCount);
	}


	public void setName(String name) { // And here's all the setter methods, which set the corresponding instance variable.
		this.name = name;
	}

	public void setGender(String gender) {
		this.gender = gender;
	}

	public void setInterests(String interests) {
		this.interests = interests;
	}

	public void setGeekRating(int rating) { // Finally, the setHotOrNotRating() method increments the total ratingCount and adds the rating to the running total.
		this.rating += rating;
		ratingCount++;
	}
}
*/
class PersonImpl : public Person { // The PersonBeanImpl implements the PersonBean interface
	using string = std::string;
	string name; // The instance variables.
	string gender;
	string interests;
	int rating = 0;
	int ratingCount = 0;
public:
	string getName() const override { return name; } // All the getter methods; they each return	the appropriate instance variable...
	string getGender() const override { return gender; }
	string getInterests() const override { return interests; }

	int getGeekRating() const override { // ...except for getHotOrNotRating(), which computes the average of the ratings by dividing the ratings by the ratingCount.
		if (ratingCount == 0)
			return 0;
		return (rating / ratingCount);
	}

	void setName(const string &name) override { this->name = name; } // And here's all the setter methods, which set the corresponding instance variable.
	void setGender(const string &gender) override { this->gender = gender; }
	void setInterests(const string &interests) override { this->interests = interests; }

	void setGeekRating(int rating) override { // Finally, the setHotOrNotRating() method increments the total ratingCount and adds the rating to the running total.
		this->rating += rating;
		ratingCount++;
	}
};
#pragma endregion //The PersonBean implementation
