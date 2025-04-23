#pragma once
#include "Person.h"

/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/proxy/javaproxy

package headfirst.designpatterns.proxy.javaproxy;

public class PersonImpl implements Person { // The PersonBeanImpl implements the PersonBean interface
	String name; // The instance variables.
	String gender;
	String interests;
	int rating;
	int ratingCount = 0;
  
	public String getName() { // All the getter methods; they each return	the appropriate instance variable...
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
  
 
	public void setName(String name) {
		this.name = name;
	}
 
	public void setGender(String gender) {
		this.gender = gender;
	} 
  
	public void setInterests(String interests) {
		this.interests = interests;
	} 
  
	public void setGeekRating(int rating) {
		this.rating += rating;	
		ratingCount++;
	}
}
*/
class PersonImpl : public Person { // The PersonBeanImpl implements the PersonBean interface
private:
    std::string name; // The instance variables.
    std::string gender;
    std::string interests;
    int rating = 0;
    int ratingCount = 0;

public:
    std::string getName() const override { return name; } // All the getter methods; they each return	the appropriate instance variable...
    std::string getGender() const override { return gender; }
    std::string getInterests() const override { return interests; }

    int getGeekRating() const override { // ...except for getHotOrNotRating(), which computes the average of the ratings by dividing the ratings by the ratingCount.
        if (ratingCount == 0) return 0;
        return (rating/ratingCount); 
    }

    void setName(const std::string& name) override { this->name = name; }
    void setGender(const std::string& gender) override { this->gender = gender; }
    void setInterests(const std::string& interests) override { this->interests = interests; }
    void setGeekRating(int rating) override { 
        this->rating += rating;
        ratingCount++;
    }
};