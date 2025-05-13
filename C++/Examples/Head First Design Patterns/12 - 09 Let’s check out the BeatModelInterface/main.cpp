#pragma once

#include <memory>
#include "BeatModel.h"
#include "HeartModel.h"
#include "BeatController.h"
#include "HeartController.h"

#pragma region Now lets have a look at the concrete BeatModel class //Now let's have a look at the concrete BeatModel class
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/combined/djview
public class DJTestDrive {
    public static void main (String[] args) {
        BeatModelInterface model = new BeatModel();
        ControllerInterface controller = new BeatController(model);
    }
}

public class HeartTestDrive {
    public static void main (String[] args) {
        HeartModel heartModel = new HeartModel();
        ControllerInterface model = new HeartController(heartModel);
    }
}
*/

int main() {
    auto beatModel = std::make_shared<BeatModel>(); // Test the Beat Model
    auto beatController = std::make_unique<BeatController>(beatModel);

    auto heartModel = std::make_shared<HeartModel>(); // Test the Heart Model
    auto heartController = std::make_unique<HeartController>(heartModel);

    return 0;
}
#pragma endregion //Now lets have a look at the concrete BeatModel class