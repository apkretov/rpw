#pragma once

#include <vector>
#include <memory>
#include <thread>
#include <random>
#include "HeartModelInterface.h"

#pragma region Now let's have a look at the concrete BeatModel class
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/combined/djview
public class HeartModel implements HeartModelInterface, Runnable {
	ArrayList<BeatObserver> beatObservers = new ArrayList<BeatObserver>();
	ArrayList<BPMObserver> bpmObservers = new ArrayList<BPMObserver>();
	int time = 1000;
	int bpm = 90;
	Random random = new Random(System.currentTimeMillis());
	Thread thread;

	public HeartModel() {
		thread = new Thread(this);
		thread.start();
	}

	public void run() {
		int lastrate = -1;

		for(;;) {
			int change = random.nextInt(10);
			if (random.nextInt(2) == 0) {
				change = 0 - change;
			}
			int rate = 60000/(time + change);
			if (rate < 120 && rate > 50) {
				time += change;
				notifyBeatObservers();
				if (rate != lastrate) {
					lastrate = rate;
					notifyBPMObservers();
				}
			}
			try {
				Thread.sleep(time);
			} catch (Exception e) {}
		}
	}

	public int getHeartRate() {
		return 60000/time;
	}

	public void registerObserver(BeatObserver o) {
		beatObservers.add(o);
	}

	public void removeObserver(BeatObserver o) {
		int i = beatObservers.indexOf(o);
		if (i >= 0) {
			beatObservers.remove(i);
		}
	}

	public void notifyBeatObservers() {
		for(int i = 0; i < beatObservers.size(); i++) {
			BeatObserver observer = (BeatObserver)beatObservers.get(i);
			observer.updateBeat();
		}
	}

	public void registerObserver(BPMObserver o) {
		bpmObservers.add(o);
	}

	public void removeObserver(BPMObserver o) {
		int i = bpmObservers.indexOf(o);
		if (i >= 0) {
			bpmObservers.remove(i);
		}
	}

	public void notifyBPMObservers() {
		for(int i = 0; i < bpmObservers.size(); i++) {
			BPMObserver observer = (BPMObserver)bpmObservers.get(i);
			observer.updateBPM();
		}
	}
}
*/
class HeartModel : public HeartModelInterface {
    std::vector<BeatObserver*> beatObservers;
    std::vector<BPMObserver*> bpmObservers;
    int time{1000};
    std::random_device rd;
    std::mt19937 gen;
    std::unique_ptr<std::thread> thread;
    bool running{true};

public:
    HeartModel() : gen(rd()) {
        thread = std::make_unique<std::thread>([this] { run(); });
    }

    ~HeartModel() {
        running = false;
        if (thread && thread->joinable()) thread->join();
    }

    void run() {
        int lastrate = -1;
        std::uniform_int_distribution<> dis(0, 9);
        std::uniform_int_distribution<> coin(0, 1);

        while (running) {
            int change = dis(gen);
            if (coin(gen) == 0) change = -change;

            int rate = 60000/(time + change);
            if (rate < 120 && rate > 50) {
                time += change;
                notifyBeatObservers();
                if (rate != lastrate) {
                    lastrate = rate;
                    notifyBPMObservers();
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(time));
        }
    }

    int getHeartRate() override { return 60000/time; }

    void registerObserver(BeatObserver* o) override { 
        if (o) beatObservers.push_back(o); 
    }

    void removeObserver(BeatObserver* o) override {
        if (o) beatObservers.erase(
            std::remove(beatObservers.begin(), beatObservers.end(), o),
            beatObservers.end());
    }

    void registerObserver(BPMObserver* o) override { 
        if (o) bpmObservers.push_back(o); 
    }

    void removeObserver(BPMObserver* o) override {
        if (o) bpmObservers.erase(
            std::remove(bpmObservers.begin(), bpmObservers.end(), o),
            bpmObservers.end());
    }

protected:
    void notifyBeatObservers() {
        for (auto observer : beatObservers)
            if (observer) observer->updateBeat();
    }

    void notifyBPMObservers() {
        for (auto observer : bpmObservers)
            if (observer) observer->updateBPM();
    }
};
#pragma endregion //Now let's have a look at the concrete BeatModel class