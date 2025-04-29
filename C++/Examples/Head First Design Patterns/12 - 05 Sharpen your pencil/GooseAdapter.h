#pragma once

#include <string>
#include "Quackable.h"
#include "Goose.h"

#pragma region We need a goose adapter
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/combining/adapter
package headfirst.designpatterns.combining.adapter;

public class GooseAdapter implements Quackable {
	Goose goose;
 
	public GooseAdapter(Goose goose) {
		this.goose = goose;
	}
 
	public void quack() {
		goose.honk();
	}

	public String toString() {
		return "Goose pretending to be a Duck";
	}
}
*/
class GooseAdapter : public Quackable {
	Goose goose;
public:
	GooseAdapter(const Goose& goose) : goose(goose) {}
	void quack() override { goose.honk(); }
	std::string toString() const { return "Goose pretending to be a Duck"; }
};
#pragma endregion //We need a goose adapter