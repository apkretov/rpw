#pragma once

#include <memory>
#include "../../stdafx.h"
#include "vld.h"
#include "BeatModel.h"
#include "BeatController.h"

#pragma region Putting it all together...
/* Java
public class DJTestDrive {
    public static void main (String[] args) {
        BeatModelInterface model = new BeatModel();
        ControllerInterface controller = new BeatController(model);
    }
}
*/

int main() {
	print_file_line();

	auto beatModel = std::make_shared<BeatModel>(); // Test the Beat Model
	auto beatController = std::make_unique<BeatController>(beatModel);

    return 0;
}
#pragma endregion //Putting it all together...