#include <windows.h>
#include <string>
using std::string;
using std::to_string;
#include "resource.h"

#define displayNumber(varNum) string(#varNum " = " + to_string(varNum)) 

const char g_szClassName[] = "myWindowClass";

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) { // Step 4: the Window Procedure
	switch (msg) {
		case WM_CREATE: /*MessageBox(hwnd, "Initialize the window.", "WM_CREATE", MB_ICONINFORMATION);*/ break; // Initialize the window. @ https://msdn.microsoft.com/en-us/library/ms633570(v=vs.85).aspx#designing_proc
		//ERROR case WM_PAINT:	return 0; // Paint the window's client area. @ https://msdn.microsoft.com/en-us/library/ms633570(v=vs.85).aspx#designing_proc
		case WM_SIZE: /*MessageBox(hwnd, "Set the size and position of the window.", "WM_SIZE", MB_ICONINFORMATION);*/ return 0; // Set the size and position of the window. @ https://msdn.microsoft.com/en-us/library/ms633570(v=vs.85).aspx#designing_proc
		//ORIG case WM_LBUTTONDOWN: {
		case WM_LBUTTONUP: { //TEST
			char szFileName[MAX_PATH];
			HINSTANCE hInstance = GetModuleHandle(NULL); //The handle to the current instance (which we are given in WinMain() and can also be retreived by using GetModuleHandle(). @ http://winprog.org/tutorial/resources.html
			GetModuleFileName(hInstance, szFileName, MAX_PATH);
			//ORIG MessageBox(hwnd, szFileName, "This program is:", MB_ICONINFORMATION);
			OutputDebugString(("WM_LBUTTONUP: This program is: " + string(szFileName) + "\n").c_str());
			string strMesage = ("Notification message (high bytes (High Word) of a 32 bit value (0xFFFF0000)):\n" + displayNumber(HIWORD(wParam)) + "\n\nControl or menu id that sent the message (low word (0x0000FFFF)):\n" + displayNumber(LOWORD(wParam)) + "\n\nHWND (window handle) to the control which sent the message or NULL if the messages isn't from a control:\n" + displayNumber(lParam));
			//OFF TO ENABLE WM_LBUTTONDBLCLK MessageBox(hwnd, strMesage.c_str(), "WM_LBUTTONUP", MB_ICONINFORMATION);
			OutputDebugString(strMesage.c_str());
			break;
		}
		case WM_LBUTTONDBLCLK: MessageBox(hwnd, "WM_LBUTTONDBLCLK", "WM_LBUTTONDBLCLK", MB_ICONINFORMATION); break; //I don't always receive WM_LBUTTONDBLCLK @ http://stackoverflow.com/questions/3289870/i-dont-always-receive-wm-lbuttondblclk
		case WM_RBUTTONUP: //TEST
			MessageBox(hwnd, "To send a message you can use PostMessage() or SendMessage(). PostMessage() puts the message into the Message Queue and returns immediatly. That means once the call to PostMessage() is done the message may or may not have been processed yet.", "WM_RBUTTONUP", MB_ICONEXCLAMATION);
			PostMessage(hwnd, WM_CLOSE, 0, 0);
			break;
		case WM_MBUTTONUP: //TEST
			MessageBox(hwnd, "SendMessage() sends the message directly to the window and does not return untill the window has finished processing it.", "WM_MBUTTONUP", MB_ICONEXCLAMATION);
			SendMessage(hwnd, WM_CLOSE, 0, 0);
			break;
		case WM_COMMAND:
			MessageBox(hwnd, ( "Notification message: " + displayNumber(HIWORD(wParam)) +	"\n\nControl or menu id that sent the message: " + displayNumber(LOWORD(wParam)) +	"\n\nHWND (window handle) to the control which sent the message or NULL if the messages isn't from a control: " + displayNumber(lParam) ).c_str(), "WM_COMMAND", MB_ICONINFORMATION); //TEST
			switch (LOWORD(wParam)) {
				case ID_FILE_EXIT: PostMessage(hwnd, WM_CLOSE, 0, 0); break;
				case ID_STUFF_GO: MessageBox(hwnd, "You clicked Go!", "Woo!", MB_OK); break;
			}
			break; 
		case WM_CLOSE: 
			//TEST MessageBox(hwnd, "Before DestroyWindow", "My test", MB_ICONINFORMATION);
			DestroyWindow(hwnd);	
			break;
		case WM_DESTROY: 
			//TEST MessageBox(hwnd, "Before PostQuitMessage", "My test", MB_ICONINFORMATION);
			PostQuitMessage(0); 
			break;
		default:	return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;
	wc.cbSize = sizeof(WNDCLASSEX); //Step 1: Registering the Window Class
	//ORIG wc.style = 0;
	wc.style = CS_DBLCLKS; //I don't always receive WM_LBUTTONDBLCLK @ http://stackoverflow.com/questions/3289870/i-dont-always-receive-wm-lbuttondblclk
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	//ORIG wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON)); //@ http://winprog.org/tutorial/menus.html
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	//ORIG wc.lpszMenuName = NULL;
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MYMENU);
	wc.lpszClassName = g_szClassName;
	//ORIG wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON), IMAGE_ICON, 16, 16, 0);
	if (!RegisterClassEx(&wc))	{
		MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION);
		return 0;
	}
	//ORIG hwnd = CreateWindowEx( WS_EX_CLIENTEDGE, g_szClassName, "The title of my window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 600, 300,	NULL, NULL, hInstance, NULL); /* Step 2: Creating the Window //The first parameter (WS_EX_CLIENTEDGE) is the extended windows style, in this case I have set it to give it a sunken inner border around the window. @ http://winprog.org/tutorial/simple_window.html */
	hwnd = CreateWindowEx( WS_EX_CLIENTEDGE, g_szClassName, "01 menu_one.exe - The title of my window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 600, 300,	NULL, NULL, hInstance, NULL); // Step 2: Creating the Window //The first parameter (WS_EX_CLIENTEDGE) is the extended windows style, in this case I have set it to give it a sunken inner border around the window. @ http://winprog.org/tutorial/simple_window.html
	//dwExStyle's:
	//hwnd = CreateWindowEx( 0, g_szClassName, "The title of my window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 600, 300, NULL, NULL, hInstance, NULL); //Set it to 0 if you'd like to see the difference. @ http://winprog.org/tutorial/simple_window.html
	//hwnd = CreateWindowEx(WS_EX_LAYOUTRTL, g_szClassName, "The title of my window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 600, 300, NULL, NULL, hInstance, NULL); //If the shell language is Hebrew, Arabic, or another language that supports reading order alignment, the horizontal origin of the window is on the right edge. Increasing horizontal values advance to the left. @ https://msdn.microsoft.com/en-us/library/ff700543(v=vs.85).aspx
	//hwnd = CreateWindowEx(WS_EX_RIGHT, g_szClassName, "The title of my window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 600, 300, NULL, NULL, hInstance, NULL); //The window has generic "right-aligned" properties.This depends on the window class.This style has an effect only if the shell language is Hebrew, Arabic, or another language that supports reading - order alignment; otherwise, the style is ignored. Using the WS_EX_RIGHT style for static or edit controls has the same effect as using the SS_RIGHT or ES_RIGHT style, respectively.Using this style with button controls has the same effect as using BS_RIGHT and BS_RIGHTBUTTON styles. @ https://msdn.microsoft.com/en-us/library/ff700543(v=vs.85).aspx
	//hwnd = CreateWindowEx(WS_EX_NOACTIVATE, g_szClassName, "The title of my window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 600, 300, NULL, NULL, hInstance, NULL); // A top-level window created with this style does not become the foreground window when the user clicks it. The system does not bring this window to the foreground when the user minimizes or closes the foreground window. To activate the window, use the SetActiveWindow or SetForegroundWindow function. The window does not appear on the taskbar by default.To force the window to appear on the taskbar, use the WS_EX_APPWINDOW style. @ https://msdn.microsoft.com/en-us/library/ff700543(v=vs.85).aspx
	//hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, g_szClassName, "The title of my window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 600, 300, NULL, NULL, hInstance, NULL); //The window is an overlapped window. @ https://msdn.microsoft.com/en-us/library/ff700543(v=vs.85).aspx
	//hwnd = CreateWindowEx(WS_EX_PALETTEWINDOW, g_szClassName, "The title of my window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 600, 300, NULL, NULL, hInstance, NULL); //The window is palette window, which is a modeless dialog box that presents an array of commands. @ https://msdn.microsoft.com/en-us/library/ff700543(v=vs.85).aspx
	//hwnd = CreateWindowEx(WS_EX_TOOLWINDOW, g_szClassName, "The title of my window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 600, 300, NULL, NULL, hInstance, NULL); //The window is intended to be used as a floating toolbar. A tool window has a title bar that is shorter than a normal title bar, and the window title is drawn using a smaller font. A tool window does not appear in the taskbar or in the dialog that appears when the user presses ALT+TAB. If a tool window has a system menu, its icon is not displayed on the title bar. However, you can display the system menu by right-clicking or by typing ALT+SPACE. @ https://msdn.microsoft.com/en-us/library/ff700543(v=vs.85).aspx
	//hwnd = CreateWindowEx(WS_EX_TOPMOST, g_szClassName, "The title of my window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 600, 300, NULL, NULL, hInstance, NULL); //The window should be placed above all non-topmost windows and should stay above them, even when the window is deactivated. To add or remove this style, use the SetWindowPos function. @ https://msdn.microsoft.com/en-us/library/ff700543(v=vs.85).aspx
	//hwnd = CreateWindowEx(WS_EX_TRANSPARENT, g_szClassName, "The title of my window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 600, 300, NULL, NULL, hInstance, NULL); //The window should not be painted until siblings beneath the window(that were created by the same thread) have been painted.The window appears transparent because the bits of underlying sibling windows have already been painted.	To achieve transparency without these restrictions, use the SetWindowRgn function. @ https://msdn.microsoft.com/en-us/library/ff700543(v=vs.85).aspx
	//dwStyle's:
	//hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, g_szClassName, "The title of my window", WS_BORDER, CW_USEDEFAULT, CW_USEDEFAULT, 600, 300, NULL, NULL, hInstance, NULL); //The window has a thin-line border. @ https://msdn.microsoft.com/en-us/library/ms632600(v=vs.85).aspx
	//hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, g_szClassName, "The title of my window", WS_DISABLED, CW_USEDEFAULT, CW_USEDEFAULT, 600, 300, NULL, NULL, hInstance, NULL); //The window is initially disabled. A disabled window cannot receive input from the user. To change this after a window has been created, use the EnableWindow function. @ https://msdn.microsoft.com/en-us/library/ms632600(v=vs.85).aspx
	//hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, g_szClassName, "The title of my window", WS_POPUP, CW_USEDEFAULT, CW_USEDEFAULT, 600, 300, NULL, NULL, hInstance, NULL); //The windows is a pop-up window. This style cannot be used with the WS_CHILD style. @ https://msdn.microsoft.com/en-us/library/ms632600(v=vs.85).aspx
	//hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, g_szClassName, "The title of my window", WS_POPUPWINDOW /*TEST | WS_CAPTION*/, CW_USEDEFAULT, CW_USEDEFAULT, 600, 300, NULL, NULL, hInstance, NULL); //The window is a pop-up window. The WS_CAPTION and WS_POPUPWINDOW styles must be combined to make the window menu visible. @ https://msdn.microsoft.com/en-us/library/ms632600(v=vs.85).aspx
	//hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, g_szClassName, "The title of my window", WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 600, 300, NULL, NULL, hInstance, NULL); //The window has a window menu on its title bar. The WS_CAPTION style must also be specified. @ https://msdn.microsoft.com/en-us/library/ms632600(v=vs.85).aspx	
	//hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, g_szClassName, "The title of my window", WS_VSCROLL, CW_USEDEFAULT, CW_USEDEFAULT, 600, 300, NULL, NULL, hInstance, NULL); //The window has a vertical scroll bar. @ https://msdn.microsoft.com/en-us/library/ms632600(v=vs.85).aspx
	if (hwnd == NULL)	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",	MB_ICONEXCLAMATION);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow); //
	//ShowWindow(hwnd, SW_FORCEMINIMIZE); //Minimizes a window, even if the thread that owns the window is not responding. This flag should only be used when minimizing windows from a different thread. @ https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k(WINUSER%2FShowWindow);k(ShowWindow);k(DevLang-C%2B%2B);k(TargetOS-Windows)&rd=true
	//ShowWindow(hwnd, SW_HIDE); //Hides the window and activates another window. @ https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k(WINUSER%2FShowWindow);k(ShowWindow);k(DevLang-C%2B%2B);k(TargetOS-Windows)&rd=true
	//ShowWindow(hwnd, SW_MAXIMIZE); //Maximizes the specified window. @ https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k(WINUSER%2FShowWindow);k(ShowWindow);k(DevLang-C%2B%2B);k(TargetOS-Windows)&rd=true
	//ShowWindow(hwnd, SW_MINIMIZE); //Minimizes the specified window and activates the next top-level window in the Z order. @ https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k(WINUSER%2FShowWindow);k(ShowWindow);k(DevLang-C%2B%2B);k(TargetOS-Windows)&rd=true
	//ShowWindow(hwnd, SW_SHOWMAXIMIZED); //Activates the window and displays it as a maximized window. @ https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k(WINUSER%2FShowWindow);k(ShowWindow);k(DevLang-C%2B%2B);k(TargetOS-Windows)&rd=true
	//ShowWindow(hwnd, SW_SHOWMINIMIZED); //Activates the window and displays it as a minimized window. @ https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k(WINUSER%2FShowWindow);k(ShowWindow);k(DevLang-C%2B%2B);k(TargetOS-Windows)&rd=true
	//ShowWindow(hwnd, SW_SHOWMINNOACTIVE); //Displays the window as a minimized window. This value is similar to SW_SHOWMINIMIZED, except the window is not activated. @ https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k(WINUSER%2FShowWindow);k(ShowWindow);k(DevLang-C%2B%2B);k(TargetOS-Windows)&rd=true
	//ShowWindow(hwnd, SW_SHOWNA); //Displays the window in its current size and position. This value is similar to SW_SHOW, except that the window is not activated. @ https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k(WINUSER%2FShowWindow);k(ShowWindow);k(DevLang-C%2B%2B);k(TargetOS-Windows)&rd=true
	//ShowWindow(hwnd, SW_SHOWNOACTIVATE); //Displays a window in its most recent size and position. This value is similar to SW_SHOWNORMAL, except that the window is not activated. @ https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k(WINUSER%2FShowWindow);k(ShowWindow);k(DevLang-C%2B%2B);k(TargetOS-Windows)&rd=true
	//ShowWindow(hwnd, SW_SHOWNORMAL); //Activates and displays a window. If the window is minimized or maximized, the system restores it to its original size and position. An application should specify this flag when displaying the window for the first time. @ https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k(WINUSER%2FShowWindow);k(ShowWindow);k(DevLang-C%2B%2B);k(TargetOS-Windows)&rd=true
	UpdateWindow(hwnd);
	//ORIG MessageBox(hwnd, "The window created!", "My test", MB_ICONINFORMATION); 
	/*MessageBox(NULL, "This message box dosn't have an owner (NULL owner window)!\nSo, it isn't modal.", "My test", MB_ICONINFORMATION);*/ //TEST
	while (GetMessage(&Msg, NULL, 0, 0) > 0) { /* Step 3: The Message Loop //1. The message loop calls GetMessage(), which looks in your message queue. If the message queue is empty your program basically stops and waits for one (it Blocks). 2. When an event occures causing a message to be added to the queue (for example the system registers a mouse click) GetMessages() returns a positive value indicating there is a message to be processed, and that it has filled in the members of the MSG structure we passed it. It returns 0 if it hits WM_QUIT, and a negative value if an error occured. @ http://winprog.org/tutorial/message_loop.html */
		TranslateMessage(&Msg); /*3. We take the message (in the Msg variable) and pass it to TranslateMessage(), this does a bit of additional processing, translating virtual key messages into character messages. This step is actually optional, but certain things won't work if it's not there. @ http://winprog.org/tutorial/message_loop.html */
		DispatchMessage(&Msg); //4. Once that's done we pass the message to DispatchMessage(). What DispatchMessage() does is take the message, checks which window it is for and then looks up the Window Procedure for the window. It then calls that procedure, sending as parameters the handle of the window, the message, and wParam and lParam. 6. Once you have finished processing the message, your windows procedure returns, DispatchMessage() returns, and we go back to the beginning of the loop. This is a very important concept for windows programs. Your window procedure is not magically called by the system, in effect you call it yourself indirectly by calling DispatchMessage(). @ http://winprog.org/tutorial/message_loop.html
		//FAILED WNDPROC fWndProc = (WNDPROC)GetWindowLong(Msg.hwnd, GWL_WNDPROC); //You could use GetWindowLong() on the window handle that the message is destined for to look up the window's procedure and call it directly! @ http://winprog.org/tutorial/message_loop.html
		//fWndProc(Msg.hwnd, Msg.message, Msg.wParam, Msg.lParam);
	}
	return Msg.wParam;
}