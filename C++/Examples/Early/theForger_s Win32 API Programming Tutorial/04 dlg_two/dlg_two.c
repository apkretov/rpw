#include <windows.h>
#include "resource.h" 

const char g_szClassName[] = "myWindowClass";
HWND g_hToolbar = NULL;

BOOL CALLBACK ToolDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
		case WM_COMMAND:
			switch (LOWORD(wParam)) {
				case IDC_PRESS: MessageBox(hwnd, "Hi!", "This is a message", MB_OK | MB_ICONEXCLAMATION); break;
				case IDC_OTHER: MessageBox(hwnd, "Bye!", "This is also a message", MB_OK | MB_ICONEXCLAMATION); break;
			}
			break;
		default: return FALSE;
	}
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
		case WM_CREATE:
			g_hToolbar = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_TOOLBAR), hwnd, ToolDlgProc); /*CreateDialog(), DialogBox()'s sister function. The difference is that while DialogBox() implements it's own message loop and does not return untill the dialog is closed, CreateDialog() acts more like a window created with CreateWindowEx() in that it returns immediately and depends on your message loop to pump the messages as it does for your main window. @ http://winprog.org/tutorial/modeless_dialogs.html */
			if (g_hToolbar != NULL) ShowWindow(g_hToolbar, SW_SHOW);
			else MessageBox(hwnd, "CreateDialog returned NULL", "Warning!", MB_OK | MB_ICONINFORMATION);
			break;
		case WM_COMMAND:
			switch (LOWORD(wParam)) {
				case ID_FILE_EXIT: PostMessage(hwnd, WM_CLOSE, 0, 0); break;
				case ID_DIALOG_SHOW: ShowWindow(g_hToolbar, SW_SHOW); break; //Display and hide our toolbar whenever we choose so. @ http://winprog.org/tutorial/modeless_dialogs.html
				case ID_DIALOG_HIDE:ShowWindow(g_hToolbar, SW_HIDE); break;
			}
			break;
		case WM_CLOSE: DestroyWindow(hwnd); break;
		case WM_DESTROY:
			DestroyWindow(g_hToolbar); //We don't call EndDialog() for modeless dialogs, we can use DestroyWindow() just like for regular windows. @ http://winprog.org/tutorial/modeless_dialogs.html
			PostQuitMessage(0);
			break;
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
	//ORIG hwnd = CreateWindowEx( WS_EX_CLIENTEDGE, g_szClassName, "The title of my window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 600, 300, NULL, NULL, hInstance, NULL);
	hwnd = CreateWindowEx( WS_EX_CLIENTEDGE, g_szClassName, "04 dlg_two.exe - The title of my window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 600, 300, NULL, NULL, hInstance, NULL);
	if (hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&Msg, NULL, 0, 0) > 0) {
		if (!IsDialogMessage(g_hToolbar, &Msg)) { //Whereas DialogBox() implements it's own message loop and handles these events by default, CreateDialog() does not. We can do it ourselves though, by calling IsDialogMessage() in our message loop which will do the default processing for us. @ http://winprog.org/tutorial/modeless_dialogs.html
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}	
	}
	return Msg.wParam;
}
