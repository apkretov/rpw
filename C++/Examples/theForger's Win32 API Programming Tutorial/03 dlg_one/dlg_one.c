#include <windows.h>
#include "resource.h" 

const char g_szClassName[] = "myWindowClass";

BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) { //There are a few important differences between a dialog procedure and window procedure. One is that you DO NOT call DefWindowProc() for message you don't handle. With dialogs this is done automatically for you (and will really screw things up if you do it). Secondly, in general you return FALSE for messages you don't process, and TRUE for messages you do process, UNLESS the message specifies you return something else. Note that this is what we do above, the default is to do nothing and return FALSE, while messages we do handle break the switch () and return TRUE. Thirdy, You do not call DestroyWindow() to close a dialog, you call EndDialog(). The second paramter is the value that is returned to whatever code called DialogBox(). Finally, instead of handling WM_CREATE, you handle WM_INITDIALOG to do any processing that needs to be done before the dialog appears, and then return TRUE to have the keyboard focus set to the default control. (You can actually handle WM_CREATE as well, but it is sent BEFORE any of the controls have been created, so you can't access them. In WM_INITDIALOG the controls have already been created). @ http://winprog.org/tutorial/dialogs.html
	switch (Message) {
		case WM_INITDIALOG: //Instead of handling WM_CREATE, you handle WM_INITDIALOG to do any processing that needs to be done before the dialog appears, and then return TRUE to have the keyboard focus set to the default control. (You can actually handle WM_CREATE as well, but it is sent BEFORE any of the controls have been created, so you can't access them. In WM_INITDIALOG the controls have already been created). @ http://winprog.org/tutorial/dialogs.html
			return TRUE; //Return FALSE for messages you don't process, and TRUE for messages you do process, UNLESS the message specifies you return something else. @ http://winprog.org/tutorial/dialogs.html
		case WM_COMMAND:
			switch (LOWORD(wParam)) {
				case IDOK: EndDialog(hwnd, IDOK); break; //You do not call DestroyWindow() to close a dialog, you call EndDialog(). The second paramter is the value that is returned to whatever code called DialogBox(). @ http://winprog.org/tutorial/dialogs.html
				case IDCANCEL: 
					EndDialog(hwnd, IDCANCEL); //You do not call DestroyWindow() to close a dialog, you call EndDialog(). The second paramter is the value that is returned to whatever code called DialogBox(). @ http://winprog.org/tutorial/dialogs.html
					//TEST MessageBox(hwnd, "Dialog exited with IDCANCEL.", "My test", MB_OK | MB_ICONINFORMATION);
					break;
			}
		break;
		default: return FALSE; //Return FALSE for messages you don't process, and TRUE for messages you do process, UNLESS the message specifies you return something else. @ http://winprog.org/tutorial/dialogs.html
	}
	return TRUE; //Return FALSE for messages you don't process, and TRUE for messages you do process, UNLESS the message specifies you return something else. @ http://winprog.org/tutorial/dialogs.html
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
		case WM_COMMAND:
			switch (LOWORD(wParam)) {
				case ID_FILE_EXIT: PostMessage(hwnd, WM_CLOSE, 0, 0); break;
				case ID_HELP_ABOUT: {
					int ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ABOUT), hwnd, AboutDlgProc); //You do not call DestroyWindow() to close a dialog, you call EndDialog(). The second paramter is the value that is returned to whatever code called DialogBox(). @ http://winprog.org/tutorial/dialogs.html
					if (ret == IDOK) MessageBox(hwnd, "Dialog exited with IDOK.", "Notice", MB_OK | MB_ICONINFORMATION);
					else if (ret == IDCANCEL) MessageBox(hwnd, "Dialog exited with IDCANCEL.", "Notice", MB_OK | MB_ICONINFORMATION);
					//TEST if (ret == IDCANCEL) PostQuitMessage(0);
					else if (ret == -1) MessageBox(hwnd, "Dialog failed!", "Error", MB_OK | MB_ICONINFORMATION);
				}
				break;
			}
			break;
		case WM_CLOSE: DestroyWindow(hwnd); break;
		case WM_DESTROY: PostQuitMessage(0); break;
		default: return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.style		 = 0;
	wc.lpfnWndProc	 = WndProc;
	wc.cbClsExtra	 = 0;
	wc.cbWndExtra	 = 0;
	wc.hInstance	 = hInstance;
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MYMENU);
	wc.lpszClassName = g_szClassName;
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	//ORIG hwnd = CreateWindowEx( WS_EX_CLIENTEDGE, g_szClassName, "The title of my window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 600, 300, NULL, NULL, hInstance, NULL );
	hwnd = CreateWindowEx( WS_EX_CLIENTEDGE, g_szClassName, "03 dlg_one.exe - The title of my window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 600, 300, NULL, NULL, hInstance, NULL );
	if (hwnd == NULL) { 
		MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	PostMessage(hwnd, WM_COMMAND, ID_HELP_ABOUT, 0); //My test.
	while(GetMessage(&Msg, NULL, 0, 0) > 0) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}
