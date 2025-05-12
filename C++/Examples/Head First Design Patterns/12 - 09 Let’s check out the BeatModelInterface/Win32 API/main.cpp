#pragma once

#include <memory>
#include <windows.h>
#include "BeatModel.h"
#include "HeartModel.h"
#include "BeatController.h"
#include "HeartController.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	// Test the Beat Model
	auto beatModel = std::make_shared<BeatModel>();
	auto beatController = std::make_unique<BeatController>(beatModel);

	// Test the Heart Model
	auto heartModel = std::make_shared<HeartModel>();
	auto heartController = std::make_unique<HeartController>(heartModel);

	// Windows message loop
	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}