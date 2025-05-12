#pragma once

#pragma region Now let's have a look at the concrete BeatModel class
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/combined/djview
public interface Sequencer {
    void start();
    void stop();
    void setTempoInBPM(int bpm);
}
*/
class Sequencer {
public:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void setTempoInBPM(int bpm) = 0;
    virtual ~Sequencer() = default;
};
#pragma endregion //Now let's have a look at the concrete BeatModel class