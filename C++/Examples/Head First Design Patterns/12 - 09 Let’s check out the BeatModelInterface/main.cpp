#pragma once

#include <memory>
#include "BeatModel.h"
#include "HeartModel.h"
#include "BeatController.h"
#include "HeartController.h"

#pragma region Putting it all together
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
	// Test the Beat Model
	auto beatModel = std::make_shared<BeatModel>();
	auto beatController = std::make_unique<BeatController>(beatModel);

	// Test the Heart Model
	auto heartModel = std::make_shared<HeartModel>();
	auto heartController = std::make_unique<HeartController>(heartModel);

	return 0;
}
#pragma endregion //Putting it all together