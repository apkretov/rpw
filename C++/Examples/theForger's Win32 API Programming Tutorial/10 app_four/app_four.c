#include <windows.h>
#include <commctrl.h>
#include "resource.h"
#define IDC_MAIN_MDI	101
#define IDC_MAIN_TOOL	102
#define IDC_MAIN_STATUS	103
#define IDC_CHILD_EDIT	101
#define ID_MDI_FIRSTCHILD 50000

const char g_szClassName[] = "myWindowClass";
const char g_szChildClassName[] = "myMDIChildWindowClass";
HWND g_hMDIClient = NULL;
HWND g_hMainWindow = NULL;

BOOL LoadTextFileToEdit(HWND hEdit, LPCTSTR pszFileName) {
	HANDLE hFile;
	BOOL bSuccess = FALSE;
	hFile = CreateFile(pszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE) {
		DWORD dwFileSize;
		dwFileSize = GetFileSize(hFile, NULL);
		if (dwFileSize != 0xFFFFFFFF)	{
			LPSTR pszFileText;
			pszFileText = (LPSTR)GlobalAlloc(GPTR, dwFileSize + 1);
			if (pszFileText != NULL) {
				DWORD dwRead;
				if (ReadFile(hFile, pszFileText, dwFileSize, &dwRead, NULL)) {
					pszFileText[dwFileSize] = 0; // Add null terminator
					if (SetWindowText(hEdit, pszFileText))
						bSuccess = TRUE; // It worked!
				}
				GlobalFree(pszFileText);
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
			if (pszText != NULL)	{
				if (GetWindowText(hEdit, pszText, dwBufferSize)) {
					DWORD dwWritten;
					if (WriteFile(hFile, pszText, dwTextLength, &dwWritten, NULL)) bSuccess = TRUE;
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
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "txt";
	if (GetOpenFileName(&ofn))	{
		HWND hEdit = GetDlgItem(hwnd, IDC_CHILD_EDIT);
		if (LoadTextFileToEdit(hEdit, szFileName)) {
			SendDlgItemMessage(g_hMainWindow, IDC_MAIN_STATUS, SB_SETTEXT, 0, (LPARAM)"Opened...");
			SendDlgItemMessage(g_hMainWindow, IDC_MAIN_STATUS, SB_SETTEXT, 1, (LPARAM)szFileName);
			SetWindowText(hwnd, szFileName); //Additionally setting the title of the MDI Child to the filename. @ http://winprog.org/tutorial/app_four.html
}	}	}

void DoFileSave(HWND hwnd) {
	OPENFILENAME ofn;
	char szFileName[MAX_PATH] = "";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrDefExt = "txt";
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	if (GetSaveFileName(&ofn))	{
		HWND hEdit = GetDlgItem(hwnd, IDC_CHILD_EDIT);
		if (SaveTextFileFromEdit(hEdit, szFileName)) {
			SendDlgItemMessage(g_hMainWindow, IDC_MAIN_STATUS, SB_SETTEXT, 0, (LPARAM)"Saved...");
			SendDlgItemMessage(g_hMainWindow, IDC_MAIN_STATUS, SB_SETTEXT, 1, (LPARAM)szFileName);
			SetWindowText(hwnd, szFileName); //Additionally setting the title of the MDI Child to the filename. @ http://winprog.org/tutorial/app_four.html
}	}	}

HWND CreateNewMDIChild(HWND hMDIClient) { //MDI Child windows are not created directly, isntead we send a WM_MDICREATE message to the client window telling it what kind of window we want by setting the members of an MDICREATESTRUCT. @ http://winprog.org/tutorial/app_four.html
	MDICREATESTRUCT mcs; //One member of MDICREATESTRUCT that I didn't use that can be quite usefull is the lParam member. This can be used to send any 32bit value (like a pointer) to the child you are creating in order to provide it with any custom information you choose. In the WM_CREATE handler for your child window, the lParam value for the WM_CREATE message will point to a CREATESTRUCT. the lpCreateParams member of that structure will point to the MDICREATESTRUCT you sent along with WM_MDICREATE. So in order to access the lParam value from the Child window you need to do something like this in the child window procedure...
								//case WM_CREATE: {
								//   CREATESTRUCT* pCreateStruct;
								//   MDICREATESTRUCT* pMDICreateStruct;
								//   pCreateStruct = (CREATESTRUCT*)lParam;
								//   pMDICreateStruct = (MDICREATESTRUCT*)pCreateStruct->lpCreateParams; //pMDICreateStruct now points to the same MDICREATESTRUCT that you sent along with the WM_MDICREATE message and you can use it to access the lParam. //If you don't want to bother with those two extra pointers you can access the lParam in one step with ((MDICREATESTRUCT*)((CREATESTRUCT*)lParam)->lpCreateParams)->lParam
								//	}break; @ http://winprog.org/tutorial/app_four.html
	HWND hChild;
	mcs.szTitle = "[Untitled]";
	mcs.szClass = g_szChildClassName;
	mcs.hOwner  = GetModuleHandle(NULL);
	mcs.x = mcs.cx = CW_USEDEFAULT;
	mcs.y = mcs.cy = CW_USEDEFAULT;
	mcs.style = MDIS_ALLCHILDSTYLES;
	hChild = (HWND)SendMessage(hMDIClient, WM_MDICREATE, 0, (LONG)&mcs); //The return value from the WM_MDICREATE message is the handle to the newly created window. @ http://winprog.org/tutorial/app_four.html
	if (!hChild) MessageBox(hMDIClient, "MDI Child creation failed.", "Oh Oh...", MB_ICONEXCLAMATION | MB_OK);
	return hChild;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)	{
		case WM_CREATE: {
			HWND hTool;
			TBBUTTON tbb[3];
			TBADDBITMAP tbab;
			HWND hStatus;
			int statwidths[] = {100, -1};
			CLIENTCREATESTRUCT ccs;
			ccs.hWindowMenu  = GetSubMenu(GetMenu(hwnd), 2); /* Create MDI Client // Find window menu where children will be listed //The menu handle is the handle to the popup menu that the MDI client will add items to representing each window that is created, allowing the user to select the window they want to activate from the menu, we'll add functionality shortly to handle this case. In this example it's the 3rd popup (index 2) since I've added Edit and Window to the menu after File. @ http://winprog.org/tutorial/app_four.html */
			ccs.idFirstChild = ID_MDI_FIRSTCHILD; //A number to use as the first ID for the items the Client adds to the Window menu... you want this to be easily distinguishable from your own menu identifiers so you can handle your menu commands and pass the Window menu commands to DefFrameProc() for processing. In the example I specify an identifier defined as 50000, high enough that I know none of my menu command id's will be above it. @ http://winprog.org/tutorial/app_four.html
			g_hMDIClient = CreateWindowEx(WS_EX_CLIENTEDGE, "mdiclient", NULL, WS_CHILD | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hwnd, (HMENU)IDC_MAIN_MDI, GetModuleHandle(NULL), (LPVOID)&ccs); //
			//TEST g_hMDIClient = CreateWindowEx(WS_EX_CLIENTEDGE, "mdiclient", NULL, WS_CHILD | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL/* | WS_VISIBLE*/, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hwnd, (HMENU)IDC_MAIN_MDI, GetModuleHandle(NULL), (LPVOID)&ccs);
			//TEST g_hMDIClient = CreateWindowEx(WS_EX_CLIENTEDGE, "mdiclient", NULL, WS_CHILD /*| WS_CLIPCHILDREN*/ | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hwnd, (HMENU)IDC_MAIN_MDI, GetModuleHandle(NULL), (LPVOID)&ccs);
			if (g_hMDIClient == NULL) MessageBox(hwnd, "Could not create MDI client.", "Error", MB_OK | MB_ICONERROR);
			
			hTool = CreateWindowEx(0, TOOLBARCLASSNAME, NULL, WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hwnd, (HMENU)IDC_MAIN_TOOL, GetModuleHandle(NULL), NULL); // Create Toolbar
			if (hTool == NULL) MessageBox(hwnd, "Could not create tool bar.", "Error", MB_OK | MB_ICONERROR);
			SendMessage(hTool, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0); // Send the TB_BUTTONSTRUCTSIZE message, which is required for backward compatibility.
			tbab.hInst = HINST_COMMCTRL;
			tbab.nID = IDB_STD_SMALL_COLOR;
			SendMessage(hTool, TB_ADDBITMAP, 0, (LPARAM)&tbab);
			ZeroMemory(tbb, sizeof(tbb));
			tbb[0].iBitmap = STD_FILENEW;
			tbb[0].fsState = TBSTATE_ENABLED;
			tbb[0].fsStyle = TBSTYLE_BUTTON;
			tbb[0].idCommand = ID_FILE_NEW;
			tbb[1].iBitmap = STD_FILEOPEN;
			tbb[1].fsState = TBSTATE_ENABLED;
			tbb[1].fsStyle = TBSTYLE_BUTTON;
			tbb[1].idCommand = ID_FILE_OPEN;
			tbb[2].iBitmap = STD_FILESAVE;
			tbb[2].fsState = TBSTATE_ENABLED;
			tbb[2].fsStyle = TBSTYLE_BUTTON;
			tbb[2].idCommand = ID_FILE_SAVEAS;
			SendMessage(hTool, TB_ADDBUTTONS, sizeof(tbb)/sizeof(TBBUTTON), (LPARAM)&tbb);

			hStatus = CreateWindowEx(0, STATUSCLASSNAME, NULL, WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP, 0, 0, 0, 0, hwnd, (HMENU)IDC_MAIN_STATUS, GetModuleHandle(NULL), NULL); // Create Status bar
			SendMessage(hStatus, SB_SETPARTS, sizeof(statwidths)/sizeof(int), (LPARAM)statwidths);
			SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)"Hi there :)");
			}break;
		case WM_SIZE: {
			HWND hTool;
			RECT rcTool;
			int iToolHeight;
			HWND hStatus;
			RECT rcStatus;
			int iStatusHeight;
			HWND hMDI;
			int iMDIHeight;
			RECT rcClient;
			hTool = GetDlgItem(hwnd, IDC_MAIN_TOOL); // Size toolbar and get height
			SendMessage(hTool, TB_AUTOSIZE, 0, 0);
			GetWindowRect(hTool, &rcTool);
			iToolHeight = rcTool.bottom - rcTool.top;
			hStatus = GetDlgItem(hwnd, IDC_MAIN_STATUS); // Size status bar and get height
			SendMessage(hStatus, WM_SIZE, 0, 0);
			GetWindowRect(hStatus, &rcStatus);
			iStatusHeight = rcStatus.bottom - rcStatus.top;
			GetClientRect(hwnd, &rcClient); // Calculate remaining height and size edit
			iMDIHeight = rcClient.bottom - iToolHeight - iStatusHeight;
			hMDI = GetDlgItem(hwnd, IDC_MAIN_MDI);
			SetWindowPos(hMDI, NULL, 0, iToolHeight, rcClient.right, iMDIHeight, SWP_NOZORDER); //Since we're building on the last example, the code to size the MDI client is the same as the code to resize the edit control in the last example, that takes into account the size and position of the tool and status bars so they don't overlap the MDI client window. @ http://winprog.org/tutorial/app_four.html
			}break;
		case WM_CLOSE: DestroyWindow(hwnd); break;
		case WM_DESTROY: PostQuitMessage(0); break;
		case WM_COMMAND:
			switch (LOWORD(wParam)) {
				case ID_FILE_EXIT: PostMessage(hwnd, WM_CLOSE, 0, 0); break;
				case ID_FILE_NEW: CreateNewMDIChild(g_hMDIClient); break; //Implement the File commands on our menu in our Frame window procedure. @ http://winprog.org/tutorial/app_four.html
				case ID_FILE_OPEN: {
					HWND hChild = CreateNewMDIChild(g_hMDIClient);
					if (hChild) DoFileOpen(hChild);	
					}break;
				case ID_FILE_CLOSE: {
					HWND hChild = (HWND)SendMessage(g_hMDIClient, WM_MDIGETACTIVE,0,0);
					if (hChild) SendMessage(hChild, WM_CLOSE, 0, 0);
					}break;
				case ID_WINDOW_TILE: SendMessage(g_hMDIClient, WM_MDITILE, 0, 0); break; //Provide some default MDI processing of window arrangment for our Window menu, since MDI supports this itself it's not much work. @ http://winprog.org/tutorial/app_four.html
				case ID_WINDOW_CASCADE: SendMessage(g_hMDIClient, WM_MDICASCADE, 0, 0); break;
				default: {
					if (LOWORD(wParam) >= ID_MDI_FIRSTCHILD) DefFrameProc(hwnd, g_hMDIClient, WM_COMMAND, wParam, lParam); /*Check to see if the value is greater than or equal to ID_MDI_FIRSTCHILD. If it is, then the user has clicked on one of the Window menu items and we send the message on to DefFrameProc() for processing. @ http://winprog.org/tutorial/app_four.html */
					else { //If it isn't one of the Window IDs then...
						HWND hChild = (HWND)SendMessage(g_hMDIClient, WM_MDIGETACTIVE,0,0); //... I get the handle to the active child window and...
						if (hChild) SendMessage(hChild, WM_COMMAND, wParam, lParam); //... forward the message to it for processing. @ http://winprog.org/tutorial/app_four.html
			}	}	}
			break;
		default: return DefFrameProc(hwnd, g_hMDIClient, msg, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK MDIChildWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) { //The window procecure for an MDI child is much like any other with a few small exceptions. @ http://winprog.org/tutorial/app_four.html
	switch(msg)	{
		case WM_CREATE: {
			HFONT hfDefault;
			HWND hEdit;
			hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL, 0, 0, 100, 100, hwnd, (HMENU)IDC_CHILD_EDIT, GetModuleHandle(NULL), NULL); // Create Edit Control
			if (hEdit == NULL) MessageBox(hwnd, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
			hfDefault = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
			SendMessage(hEdit, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE, 0));
			}break;
		case WM_MDIACTIVATE: { //We also want to disable the Edit and Window menu's when they aren't needed (just because it's a nice thing to do), so we handle WM_MDIACTIVEATE and enable or disable them depending on if our window is getting activated or not. @ http://winprog.org/tutorial/app_four.html
			HMENU hMenu, hFileMenu;
			UINT EnableFlag;
			hMenu = GetMenu(g_hMainWindow);
			if (hwnd == (HWND)lParam) EnableFlag = MF_ENABLED; //being activated, enable the menus
			else EnableFlag = MF_GRAYED; //being de-activated, gray the menus
			EnableMenuItem(hMenu, 1, MF_BYPOSITION | EnableFlag);
			EnableMenuItem(hMenu, 2, MF_BYPOSITION | EnableFlag);
			hFileMenu = GetSubMenu(hMenu, 0);
			EnableMenuItem(hFileMenu, ID_FILE_SAVEAS, MF_BYCOMMAND | EnableFlag);
			EnableMenuItem(hFileMenu, ID_FILE_CLOSE, MF_BYCOMMAND | EnableFlag);
			EnableMenuItem(hFileMenu, ID_FILE_CLOSEALL, MF_BYCOMMAND | EnableFlag);
			DrawMenuBar(g_hMainWindow);
			}break;
		case WM_COMMAND:
			switch(LOWORD(wParam)) {
				case ID_FILE_OPEN: DoFileOpen(hwnd); break;
				case ID_FILE_SAVEAS: DoFileSave(hwnd); break;
				case ID_EDIT_CUT: SendDlgItemMessage(hwnd, IDC_CHILD_EDIT, WM_CUT, 0, 0); break; //The Edit commands are easy, because the edit control has built in support for them, we just tell it what to do. http://winprog.org/tutorial/app_four.html
				case ID_EDIT_COPY: SendDlgItemMessage(hwnd, IDC_CHILD_EDIT, WM_COPY, 0, 0); break;
				case ID_EDIT_PASTE: SendDlgItemMessage(hwnd, IDC_CHILD_EDIT, WM_PASTE, 0, 0); break;
			}
			break;
		case WM_SIZE: {
			HWND hEdit;
			RECT rcClient;
			GetClientRect(hwnd, &rcClient); // Calculate remaining height and size edit
			hEdit = GetDlgItem(hwnd, IDC_CHILD_EDIT);
			SetWindowPos(hEdit, NULL, 0, 0, rcClient.right, rcClient.bottom, SWP_NOZORDER);
			}
			return DefMDIChildProc(hwnd, msg, wParam, lParam); //Remember I mentioned that there are little things you need to remember or your application will behave strangely? Note that I've called DefMDIChildProc() at the end of WM_SIZE, this is important otherwise the system wont' have a chance to do it's own processing on the message. You can look up DefMDIChildProc() in MSDN for a list of the messages that it processes, and always be sure to pass them to it. @ http://winprog.org/tutorial/app_four.html
		default: return DefMDIChildProc(hwnd, msg, wParam, lParam); //First of all, default messages are passed to DefMDIChildProc() instead of DefWindowProc(). //This is important otherwise the system wont' have a chance to do it's own processing on the message. @ http://winprog.org/tutorial/app_four.html
	}
	return 0;
}

BOOL SetUpMDIChildWindowClass(HINSTANCE hInstance) { //In addition to the main window of the program (the Frame window) we need to create new window classes for each type of child window we want. //This is basically identical to registering our regular frame window, there are no particularly special flags here for use with MDI. We've set the menu as NULL, and the window procedure to point to the child window procedure. @ http://winprog.org/tutorial/app_four.html
	WNDCLASSEX wc;
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.style		 = CS_HREDRAW | CS_VREDRAW; //CS_HREDRAW: Redraws the entire window if a movement or size adjustment changes the width of the client area. CS_VREDRAW: Redraws the entire window if a movement or size adjustment changes the height of the client area. @ https://msdn.microsoft.com/en-us/library/ff729176(v=vs.85).aspx
	//TEST wc.style		 = 0; 
	wc.lpfnWndProc	 = MDIChildWndProc; //We've set the window procedure to point to the child window procedure. @ http://winprog.org/tutorial/app_four.html
	wc.cbClsExtra	 = 0;
	wc.cbWndExtra	 = 0;
	wc.hInstance	 = hInstance;
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_3DFACE+1);
	wc.lpszMenuName  = NULL; //We've set the menu as NULL. @ http://winprog.org/tutorial/app_four.html
	wc.lpszClassName = g_szChildClassName;
	//ORIG wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm		 = LoadIcon(NULL, IDI_QUESTION); //TEST
	if (!RegisterClassEx(&wc))	{
		MessageBox(0, "Could Not Register Child Window", "Oh Oh...", MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}
	else return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;
	InitCommonControls();
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.style		 = 0;
	wc.lpfnWndProc	 = WndProc;
	wc.cbClsExtra	 = 0;
	wc.cbWndExtra	 = 0;
	wc.hInstance	 = hInstance;
	//ORIG wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIcon		 = LoadIcon(NULL, IDI_HAND); //TEST 
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MAINMENU);
	wc.lpszClassName = g_szClassName;
	//ORIG wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm		 = LoadIcon(NULL, IDI_HAND); //TEST
	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	if (!SetUpMDIChildWindowClass(hInstance)) return 0;
	hwnd = CreateWindowEx( 0, g_szClassName, "10 theForger's Tutorial Application", WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, CW_USEDEFAULT, CW_USEDEFAULT, 480, 320, NULL, NULL, hInstance, NULL);
	if (hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	g_hMainWindow = hwnd;
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&Msg, NULL, 0, 0) > 0) {
		if (!TranslateMDISysAccel(g_hMDIClient, &Msg)) { //Check for the pre-defined accelerator keys, Ctrl+F6 which swtiches to the next window, Ctrl+F4 which closes the Child and so on. @ http://winprog.org/tutorial/app_four.html
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
	}	}
	return Msg.wParam;
}
