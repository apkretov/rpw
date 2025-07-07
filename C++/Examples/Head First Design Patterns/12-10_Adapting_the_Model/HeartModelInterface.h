#pragma once

#include "ObserverBeat.h"
#include "ObserverBPM.h"

class HeartModelInterface {
public:
    virtual int getHeartRate() const = 0;
    virtual void registerObserver(BeatObserver* o) = 0;
    virtual void removeObserver(BeatObserver* o) = 0;
    virtual void registerObserver(BPMObserver* o) = 0;
    virtual void removeObserver(BPMObserver* o) = 0;
};
