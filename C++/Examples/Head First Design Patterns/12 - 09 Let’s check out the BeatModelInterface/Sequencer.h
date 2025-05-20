#pragma once

#include <iostream>

#pragma region Now lets have a look at the concrete BeatModel class //Now let's have a look at the concrete BeatModel class
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/combined/djview
public interface Sequencer {
    void start();
    void stop();
    void setTempoInBPM(int bpm);
}
*/
class Sequencer {
public:
    virtual ~Sequencer() = default;
	virtual void start() { std::cout << "Sequencer started!\n"; }
    virtual void stop() { std::cout << "Sequencer stopped!\n"; }
	virtual void setTempoInBPM(int bpm) { std::cout << "Tempo set to " << bpm << " BPM.\n"; }
};
#pragma endregion //Now lets have a look at the concrete BeatModel class