#include <windows.h>
#include "resource.h"
#define IDC_MAIN_EDIT	101

const char g_szClassName[] = "myWindowClass";

BOOL LoadTextFileToEdit(HWND hEdit, LPCTSTR pszFileName) {
	HANDLE hFile;
	BOOL bSuccess = FALSE;
	hFile = CreateFile(pszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL); /*GENERIC_READ: we only want read access.*/ /*FILE_SHARE_READ: it's okay if other programs open the file at the same time we do, but ONLY if they want to read as well, we don't want them writing to the file while we are reading it.*/ /*OPEN_EXISTING: only open the file if it already exists, don't create it, and don't overwrite it.*/ //@ http://winprog.org/tutorial/app_two.html
	if (hFile != INVALID_HANDLE_VALUE) {
		DWORD dwFileSize;
		dwFileSize = GetFileSize(hFile, NULL);
		if (dwFileSize != 0xFFFFFFFF) {
			LPSTR pszFileText;
			pszFileText = (LPSTR)GlobalAlloc(GPTR, dwFileSize + 1); //The API file functions have no concept of Text Files so they won't do things like read a single line of text, or add NULL terminators to the end of our strings. This is why we've allocated an extra byte and after we read in the file we add the NULL ourselves so that we can then pass the memory buffer as a string to SetWindowText(). @ http://winprog.org/tutorial/app_two.html
			if (pszFileText != NULL) {
				DWORD dwRead;
				if ( ReadFile(hFile, pszFileText, dwFileSize, &dwRead, NULL) ) { //&dwRead: We don't use it except as a paramter in ReadFile(). This parameter MUST be provided, the call will fail without it. //Once we've opened the file and checked to see that CreateFile() succeeded, we check the size of the file so we'll know how much memory we need to allocate in order to read the entire thing. We then allocate the memory, check to make sure the allocation succeeded, and then call ReadFile() to load the contents from disk into our memory buffer. @ http://winprog.org/tutorial/app_two.html
					pszFileText[dwFileSize] = 0; // Add null terminator
					if (SetWindowText(hEdit, pszFileText)) bSuccess = TRUE; // It worked!
				}
				GlobalFree(pszFileText); //Clean up as we reach the end of the function, freeing the memory buffer and closing the file handle before finally returning to the caller. @ http://winprog.org/tutorial/app_two.html
		}	}
		CloseHandle(hFile);
	}
	return bSuccess;
}

BOOL SaveTextFileFromEdit(HWND hEdit, LPCTSTR pszFileName) {
	HANDLE hFile;
	BOOL bSuccess = FALSE;
	hFile = CreateFile(pszFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE) {
		DWORD dwTextLength;
		dwTextLength = GetWindowTextLength(hEdit);
		if (dwTextLength > 0) { // No need to bother if there's no text.
			LPSTR pszText;
			DWORD dwBufferSize = dwTextLength + 1;
			pszText = (LPSTR)GlobalAlloc(GPTR, dwBufferSize);
			if (pszText != NULL) {
				if (GetWindowText(hEdit, pszText, dwBufferSize)) { //Request the string from the edit control. @ http://winprog.org/tutorial/app_two.html
					DWORD dwWritten;
					if (WriteFile(hFile, pszText, dwTextLength, &dwWritten, NULL)) bSuccess = TRUE; //&dwWritten: Again, like with ReadFile() the parameter that returns how much was actually written is required, even though we don't use it. @ http://winprog.org/tutorial/app_two.html
				}
				GlobalFree(pszText);
		}	}
		CloseHandle(hFile);
	}
	return bSuccess;
}

void DoFileOpen(HWND hwnd) {
	OPENFILENAME ofn;
	char szFileName[MAX_PATH] = "";
	ZeroMemory(&ofn, sizeof(ofn)); //Call ZeroMemory() on the struct in order to initialise it to 0. This is generally a wise practice, as some APIs are very picky about members that you don't use being set to NULL. This way you don't need to explicitely set each member that you don't use. @ http://winprog.org/tutorial/app_two.html
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0"; //The NULLs in this string break it up into filters, each one is two parts. The first filter has the description "Text Files (*.txt)", the wildcard isn't required here I just put it in because I felt like it. The next part is the actual wildcard for the first filter, "*.txt". We do the same thing with the second filter except that this is a generic filter for all files. @ http://winprog.org/tutorial/app_two.html
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY; //OFN_HIDEREADONLY Hides the Read Only check box. - I didn't notice its effect. @ https://msdn.microsoft.com/en-us/library/ms646839(v=vs.85).aspx
	//TEST ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST /*| OFN_HIDEREADONLY*/;
	ofn.lpstrDefExt = "txt"; //A default extention, so if the user types in "foo" and the file is not found, it will try to open "foo.txt" before finally giving up. @ http://winprog.org/tutorial/app_two.html
	if (GetOpenFileName(&ofn)) {
		HWND hEdit = GetDlgItem(hwnd, IDC_MAIN_EDIT);
		LoadTextFileToEdit(hEdit, szFileName);
	}
}

void DoFileSave(HWND hwnd) { //To select a file for saving instead of opening, the code is nearly the same, except for calling GetSaveFileName() we need only change the flags member to options more suitable for saving. @ http://winprog.org/tutorial/app_two.html
	OPENFILENAME ofn;
	char szFileName[MAX_PATH] = "";
	ZeroMemory(&ofn, sizeof(ofn)); //Call ZeroMemory() on the struct in order to initialise it to 0. This is generally a wise practice, as some APIs are very picky about members that you don't use being set to NULL. This way you don't need to explicitely set each member that you don't use. @ http://winprog.org/tutorial/app_two.html
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrDefExt = "txt";
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT; //In this case we no longer want to require the file exist, but we do want the directory to exist since we aren't going to try and create it first. We'll also prompt the user if they select an existing file to make sure they want to overwrite it. @ http://winprog.org/tutorial/app_two.html
	if (GetSaveFileName(&ofn)) { //To select a file for saving instead of opening, the code is nearly the same, except for calling GetSaveFileName(). @ http://winprog.org/tutorial/app_two.html
		HWND hEdit = GetDlgItem(hwnd, IDC_MAIN_EDIT);
		SaveTextFileFromEdit(hEdit, szFileName);
}	}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch(msg) {
		case WM_CREATE: {
			HFONT hfDefault;
			HWND hEdit;
			hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL, 0, 0, 100, 100, hwnd, (HMENU)IDC_MAIN_EDIT, GetModuleHandle(NULL), NULL);
			if (hEdit == NULL) MessageBox(hwnd, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
			hfDefault = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
			SendMessage(hEdit, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE, 0));
			} break;
		case WM_SIZE: {
			HWND hEdit;
			RECT rcClient;
			GetClientRect(hwnd, &rcClient);
			hEdit = GetDlgItem(hwnd, IDC_MAIN_EDIT);
			SetWindowPos(hEdit, NULL, 0, 0, rcClient.right, rcClient.bottom, SWP_NOZORDER);
			} break;
		case WM_CLOSE: DestroyWindow(hwnd); break;
		case WM_DESTROY: PostQuitMessage(0); break;
		case WM_COMMAND:
			switch(LOWORD(wParam)) {
				case ID_FILE_EXIT: PostMessage(hwnd, WM_CLOSE, 0, 0); break;
				case ID_FILE_NEW: SetDlgItemText(hwnd, IDC_MAIN_EDIT, ""); break;
				case ID_FILE_OPEN: DoFileOpen(hwnd); break;
				case ID_FILE_SAVEAS: DoFileSave(hwnd); break;
			}
			break;
		default: return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,	LPSTR lpCmdLine, int nCmdShow) {
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
	wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MAINMENU);
	wc.lpszClassName = g_szClassName;
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	//ORIG hwnd = CreateWindowEx(0, g_szClassName, "theForger's Tutorial Application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 480, 320, NULL, NULL, hInstance, NULL);
	hwnd = CreateWindowEx(0, g_szClassName, "08 app_two.exe - theForger's Tutorial Application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 480, 320, NULL, NULL, hInstance, NULL);
	if (hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while(GetMessage(&Msg, NULL, 0, 0) > 0) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}
