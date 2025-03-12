#pragma once

/* Java
public interface Subject{
	public void registerObserver(Observer o); // Both of these methods take an Observer as an argument; that is, the Observer to be registered or removed.
	public void removeObserver(Observer o);
	public void notifyObservers(); // This method is called to notify all observers when the Subject’s state has changed.
}

public interface Observer{ // The Observer interface is implemented by all observers, so they all have to implement the update() method. Here we’re following Mary and Sue’s lead and passing the measurements to the observers.
	public void update(float temp, float humidity, float pressure); // These are the state values the Observers get from the Subject when a weather measurement changes.
}

public interface DisplayElement { // The DisplayElement interface just includes one method, display(), that we will call when the display element needs to be displayed.
	public void display();
}
*/

struct Observer { // The Observer interface is implemented by all observers, so they all have to implement the update() method. Here we’re following Mary and Sue’s lead and passing the measurements to the observers.
	virtual void update(double temp, double humidity, double pressure) = 0; // These are the state values the Observers get from the Subject when a weather measurement changes.
};

struct Subject {
	virtual void registerObserver(Observer *o) = 0; // Both of these methods take an Observer as an argument; that is, the Observer to be registered or removed.
	virtual void removeObserver(Observer *o) = 0;
	virtual void notifyObservers() = 0; // This method is called to notify all observers when the Subject’s state has changed.
};
