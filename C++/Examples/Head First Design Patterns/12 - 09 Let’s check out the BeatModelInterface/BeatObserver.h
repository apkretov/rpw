#pragma once

#pragma region Now lets have a look at the concrete BeatModel class //Now let's have a look at the concrete BeatModel class
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/combined/djview
package headfirst.designpatterns.combined.djview;
  
public interface BeatObserver {
	void updateBeat();
}
*/
class BeatObserver {
public:
    virtual void updateBeat() = 0;
    virtual ~BeatObserver() = default;
};
#pragma endregion //Now lets have a look at the concrete BeatModel class