#pragma once

#pragma region Now let's have a look at the concrete BeatModel class
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/combined/djview
package headfirst.designpatterns.combined.djview;
  
public interface BPMObserver {
	void updateBPM();
}
*/
class BPMObserver {
public:
    virtual void updateBPM() = 0;
    virtual ~BPMObserver() = default;
};
#pragma endregion //Now let's have a look at the concrete BeatModel class