#pragma once

#pragma region Now lets have a look at the concrete BeatModel class //Now let's have a look at the concrete BeatModel class
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/combined/djview
public interface MetaEventListener {
    void beatEvent();
}
*/
class MetaEventListener {
public:
    virtual void beatEvent() = 0;
    virtual ~MetaEventListener() = default;
};
#pragma endregion //Now lets have a look at the concrete BeatModel class