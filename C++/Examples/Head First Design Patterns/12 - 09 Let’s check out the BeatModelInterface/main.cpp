#pragma once

#include <memory>
#include "../../stdafx.h"
#include "vld.h"
#include "BeatModel.h"
#include "ControllerBeat.h"

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
	print_file_line(); //MINE

	BeatModel beatModel;
	BeatController beatController{beatModel};

	std::cout << '\n'; //MINE
    return 0;
}
#pragma endregion //Putting it all together...