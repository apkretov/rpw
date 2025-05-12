#pragma once

#include <memory>
#include <string>
#include <windows.h>
#include "BeatObserver.h"
#include "BPMObserver.h"
#include "BeatModelInterface.h"
#include "ControllerInterface.h"

class DJView : public BeatObserver, public BPMObserver {
	BeatModelInterface *model;
	ControllerInterface *controller;

	// Win32 window handles
	HWND hwndMain;
	HWND hwndBeatBar;
	HWND hwndBPMOutput;
	HWND hwndBPMInput;
	HWND hwndSetBPM;
	HWND hwndIncreaseBPM;
	HWND hwndDecreaseBPM;
	HMENU hMenu;

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	DJView(ControllerInterface *controller, BeatModelInterface *model)
		: controller(controller), model(model) {
		model->registerObserver(static_cast<BeatObserver &>(*this));
		model->registerObserver(static_cast<BPMObserver &>(*this));
	}

	~DJView() {
		if (model) {
			model->removeObserver(static_cast<BeatObserver &>(*this));
			model->removeObserver(static_cast<BPMObserver &>(*this));
		}
		DestroyWindow(hwndMain);
	}

	void createView() {
		WNDCLASSEX wc = {0};
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.lpfnWndProc = WindowProc;
		wc.hInstance = GetModuleHandle(NULL);
		wc.lpszClassName = L"DJViewClass";
		RegisterClassEx(&wc);

		hwndMain = CreateWindowEx(
			0, L"DJViewClass", L"DJ View",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
			NULL, NULL, GetModuleHandle(NULL), NULL
		);

		hwndBeatBar = CreateWindow(
			L"PROGRESS", NULL,
			WS_CHILD | WS_VISIBLE,
			10, 10, 380, 30,
			hwndMain, NULL, GetModuleHandle(NULL), NULL
		);

		hwndBPMOutput = CreateWindow(
			L"STATIC", L"Current BPM: 90",
			WS_CHILD | WS_VISIBLE,
			10, 50, 380, 20,
			hwndMain, NULL, GetModuleHandle(NULL), NULL
		);

		ShowWindow(hwndMain, SW_SHOW);
	}

	void createControls() {
		hwndBPMInput = CreateWindow(
			L"EDIT", L"90",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			10, 80, 60, 20,
			hwndMain, NULL, GetModuleHandle(NULL), NULL
		);

		hwndSetBPM = CreateWindow(
			L"BUTTON", L"Set BPM",
			WS_CHILD | WS_VISIBLE,
			80, 80, 80, 20,
			hwndMain, (HMENU)1, GetModuleHandle(NULL), NULL
		);

		hwndIncreaseBPM = CreateWindow(
			L"BUTTON", L"+",
			WS_CHILD | WS_VISIBLE,
			170, 80, 30, 20,
			hwndMain, (HMENU)2, GetModuleHandle(NULL), NULL
		);

		hwndDecreaseBPM = CreateWindow(
			L"BUTTON", L"-",
			WS_CHILD | WS_VISIBLE,
			210, 80, 30, 20,
			hwndMain, (HMENU)3, GetModuleHandle(NULL), NULL
		);

		// Create menu
		hMenu = CreateMenu();
		HMENU hSubMenu = CreatePopupMenu();
		AppendMenu(hSubMenu, MF_STRING, 4, L"Start");
		AppendMenu(hSubMenu, MF_STRING, 5, L"Stop");
		AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hSubMenu, L"Control");
		SetMenu(hwndMain, hMenu);
	}

	void enableStopMenuItem() {
		EnableMenuItem(hMenu, 5, MF_ENABLED);
		DrawMenuBar(hwndMain);
	}

	void disableStopMenuItem() {
		EnableMenuItem(hMenu, 5, MF_GRAYED);
		DrawMenuBar(hwndMain);
	}

	void enableStartMenuItem() {
		EnableMenuItem(hMenu, 4, MF_ENABLED);
		DrawMenuBar(hwndMain);
	}

	void disableStartMenuItem() {
		EnableMenuItem(hMenu, 4, MF_GRAYED);
		DrawMenuBar(hwndMain);
	}

	void updateBPM() override {
		if (model) {
			int bpm = model->getBPM();
			wchar_t text[32];
			swprintf_s(text, L"Current BPM: %d", bpm);
			SetWindowText(hwndBPMOutput, text);
		}
	}

	void updateBeat() override {
		SendMessage(hwndBeatBar, PBM_SETPOS, 100, 0);
		SetTimer(hwndMain, 1, 100, NULL); // Reset progress bar after 100ms
	}
};

LRESULT CALLBACK DJView::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		case WM_COMMAND:
			// Handle button clicks and menu items
			switch (LOWORD(wParam)) {
				case 1: // Set BPM button
					// Handle set BPM
					break;
				case 2: // Increase BPM button
					// Handle increase
					break;
				case 3: // Decrease BPM button
					// Handle decrease
					break;
				case 4: // Start menu item
					// Handle start
					break;
				case 5: // Stop menu item
					// Handle stop
					break;
			}
			break;
		case WM_TIMER:
			if (wParam == 1) {
				SendMessage(hwndBeatBar, PBM_SETPOS, 0, 0);
				KillTimer(hwnd, 1);
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}