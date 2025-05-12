#pragma once

#pragma region Now let's have a look at the concrete BeatModel class
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/combined/djview
package headfirst.designpatterns.combined.djview;
  
public interface BeatObserver {
	void updateBeat();
}
*/
class BeatObserver {
public:
    virtual ~BeatObserver() = default;
    virtual void updateBeat() = 0;
};
#pragma endregion //Now let's have a look at the concrete BeatModel class