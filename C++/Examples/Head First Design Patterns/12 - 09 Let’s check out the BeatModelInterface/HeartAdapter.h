#pragma once

#include <memory>
#include "BeatModelInterface.h"
#include "HeartModelInterface.h"

#pragma region Now let's have a look at the concrete BeatModel class
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/combined/djview
public class HeartAdapter implements BeatModelInterface {
	HeartModelInterface heart;
 
	public HeartAdapter(HeartModelInterface heart) {
		this.heart = heart;
	}

    public void initialize() {}
  
    public void on() {}
  
    public void off() {}
   
	public int getBPM() {
		return heart.getHeartRate();
	}
  
    public void setBPM(int bpm) {}
   
	public void registerObserver(BeatObserver o) {
		heart.registerObserver(o);
	}
    
	public void removeObserver(BeatObserver o) {
		heart.removeObserver(o);
	}
     
	public void registerObserver(BPMObserver o) {
		heart.registerObserver(o);
	}
  
	public void removeObserver(BPMObserver o) {
		heart.removeObserver(o);
	}
}
*/
class HeartAdapter : public BeatModelInterface {
    std::shared_ptr<HeartModelInterface> heart;

public:
    explicit HeartAdapter(std::shared_ptr<HeartModelInterface> heart) : heart(heart) {}

    void initialize() override {}
    void on() override {}
    void off() override {}
    
    int getBPM() override { return heart->getHeartRate(); }
    void setBPM(int bpm) override {}

    void registerObserver(BeatObserver& o) override { heart->registerObserver(o); }
    void removeObserver(BeatObserver& o) override { heart->removeObserver(o); }
    void registerObserver(BPMObserver& o) override { heart->registerObserver(o); }
    void removeObserver(BPMObserver& o) override { heart->removeObserver(o); }
};
#pragma endregion //Now let's have a look at the concrete BeatModel class