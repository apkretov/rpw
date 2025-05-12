#pragma once

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
#ifdef TRAE
	virtual void start() = 0;
	virtual void stop() = 0;
	virtual void setTempoInBPM(int bpm) = 0;
#else //MINE
	virtual void start() {};
    virtual void stop() {};
	virtual void setTempoInBPM(int bpm) {};
#endif //MINE
};
#pragma endregion //Now lets have a look at the concrete BeatModel class