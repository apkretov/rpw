#pragma once

#include "BeatObserver.h"
#include "BPMObserver.h"

#pragma region Now lets have a look at the concrete BeatModel class //Now let's have a look at the concrete BeatModel class
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/combined/djview
package headfirst.designpatterns.combined.djview;
  
public interface BeatModelInterface {
	void initialize();
	void on();
	void off();
    void setBPM(int bpm);
	int getBPM();
	void registerObserver(BeatObserver o);
	void removeObserver(BeatObserver o);
	void registerObserver(BPMObserver o);
	void removeObserver(BPMObserver o);
}
*/
class BeatModelInterface {
public:
    virtual void initialize() = 0;
    virtual void on() = 0;
    virtual void off() = 0;
    virtual void setBPM(int bpm) = 0;
    virtual int getBPM() const = 0;
    virtual void registerObserver(BeatObserver* o) = 0;
    virtual void removeObserver(BeatObserver* o) = 0;
    virtual void registerObserver(BPMObserver* o) = 0;
    virtual void removeObserver(BPMObserver* o) = 0;
    virtual ~BeatModelInterface() = default;
};
#pragma endregion //Now lets have a look at the concrete BeatModel class