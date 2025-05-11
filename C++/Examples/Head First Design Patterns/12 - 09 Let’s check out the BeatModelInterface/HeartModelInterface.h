#pragma once

#include "BeatObserver.h"
#include "BPMObserver.h"

#pragma region Now let's have a look at the concrete BeatModel class
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/combined/djview
package headfirst.designpatterns.combined.djview;

public interface HeartModelInterface {
	int getHeartRate();
	void registerObserver(BeatObserver o);
	void removeObserver(BeatObserver o);
	void registerObserver(BPMObserver o);
	void removeObserver(BPMObserver o);
}
*/
class HeartModelInterface {
public:
    virtual int getHeartRate() = 0;
    virtual void registerObserver(BeatObserver& o) = 0;
    virtual void removeObserver(BeatObserver& o) = 0;
    virtual void registerObserver(BPMObserver& o) = 0;
    virtual void removeObserver(BPMObserver& o) = 0;
    virtual ~HeartModelInterface() = default;
};
#pragma endregion //Now let's have a look at the concrete BeatModel class