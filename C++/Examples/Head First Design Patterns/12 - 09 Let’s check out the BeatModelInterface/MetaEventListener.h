#pragma once

#pragma region Now lets have a look at the concrete BeatModel class //Now let's have a look at the concrete BeatModel class
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/combined/djview
public interface MetaEventListener {
    void beatEvent();
}
*/
class MetaEventListener { // This is needed for the MIDI code.
public:
    virtual ~MetaEventListener() = default;
    virtual void beatEvent() = 0;
};
#pragma endregion //Now lets have a look at the concrete BeatModel class