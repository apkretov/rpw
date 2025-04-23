#pragma once
#include "Person.h"

/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/proxy/javaproxy

package headfirst.designpatterns.proxy.javaproxy;

public class PersonImpl implements Person {
	String name;
	String gender;
	String interests;
	int rating;
	int ratingCount = 0;
  
	public String getName() {
		return name;	
	} 
  
	public String getGender() {
		return gender;
	}
  
	public String getInterests() {
		return interests;
	}
   
	public int getGeekRating() {
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

class PersonImpl : public Person {
private:
    std::string name;
    std::string gender;
    std::string interests;
    int rating = 0;
    int ratingCount = 0;

public:
    std::string getName() override { return name; }
    std::string getGender() override { return gender; }
    std::string getInterests() override { return interests; }
    int getGeekRating() override { 
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