#ifndef CAR_H
#define CAR_H

#include "Engine.h"
#include "Doors.h"
#include "Key.h"

/* Java
 public class Car {  // Here's a component of this class. We can call its methods.
	 Engine engine;
	 // other instance variables

	 public Car() { 
		 // initialize engine, etc.
	 }

	 public void start(Key key) {
		 Doors doors = new Doors(); // Here we're creating a new object, its methods are legal.

		 boolean authorized = key.turns(); // You can call a method on an object passed as a parameter.

		 if (authorized) {
			 engine.start(); // You can call a method on a component of the object
			 updateDashboardDisplay();  // You can call a local method within the object.
			 doors.lock();  // You can call a method on an object you create or instantiate.
		 }
	 }

	 public void updateDashboardDisplay() {
		 // update display
	 }
 }
 */
class Car {
    Engine engine;  // Here's a component of this class. We can call its methods.
    // other instance variables
public:
	Car() = default; // initialize engine, etc.  

    void start(Key key) {
        Doors doors; // Here we're creating a new object, its methods are legal.
        bool authorized = key.turns(); // You can call a method on an object passed as a parameter. 

        if (authorized) {
            engine.start(); // You can call a method on a component of the object
            updateDashboardDisplay();  // You can call a local method within the object.
            doors.lock();  // You can call a method on an object you create or instantiate.
        }
    }

    void updateDashboardDisplay() {} // update display
};
#endif // CAR_H