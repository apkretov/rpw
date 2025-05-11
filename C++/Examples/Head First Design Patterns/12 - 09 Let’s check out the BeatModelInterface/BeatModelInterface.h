#pragma once

#include <memory>

#pragma region Let's check out the BeatModelInterface before looking at the implementation

/* Java
public interface BeatModelInterface {
#pragma region Direct the model // These are the methods the controller will use to direct the model based on user interaction.
	void initialize(); // This gets called after the BeatModel is instantiated
	void on(); // These methods turn the beat generator on and off
	void off(); // These methods turn the beat generator on and off
	void setBPM(int bpm); // This method sets the beats per minute. After it is called, the beat frequency changes immediately
#pragma endregion //Direct the model
#pragma region Observers get state // These methods allow the view and the controller to get state and to become observers.
	int getBPM(); // The getBPM() method returns the current BPMs, or 0 if the generator is off
	void registerObserver(BeatObserver o); // We've split this into two kinds of observers: observers that want to be notified on every beat, and observers that just want to be notified with the beats per minute change
	void removeObserver(BeatObserver o); 
	void registerObserver(BPMObserver o); 
	void removeObserver(BPMObserver o); 
}
*/

class BeatObserver; //TO DO: Check if this is needed. If not, remove it.
class BPMObserver;

class BeatModelInterface {
public:
	virtual ~BeatModelInterface() = default;
#pragma region Direct the model // These are the methods the controller will use to direct the model based on user interaction.
	virtual void initialize() = 0; // This gets called after the BeatModel is instantiated
	virtual void on() = 0; // These methods turn the beat generator on and off
	virtual void off() = 0; // These methods turn the beat generator on and off
	virtual void setBPM(int bpm) = 0; // This method sets the beats per minute. After it is called, the beat frequency changes immediately
#pragma endregion //Direct the model 
#pragma region Observers get state // These methods allow the view and the controller to get state and to become observers.
	virtual int getBPM() const = 0; // The getBPM() method returns the current BPMs, or 0 if the generator is off
	virtual void registerObserver(std::shared_ptr<BeatObserver> o) = 0; //TO DO: Check how appropriate the pointer is. // We've split this into two kinds of observers: observers that want to be notified on every beat, and observers that just want to be notified with the beats per minute change 
	virtual void removeObserver(std::shared_ptr<BeatObserver> o) = 0;
	virtual void registerObserver(std::shared_ptr <BPMObserver> o) = 0;
	virtual void removeObserver(std::shared_ptr <BPMObserver> o) = 0;
#pragma endregion //Observers get state
};
#pragma endregion //Let's check out the BeatModelInterface before looking at the implementation