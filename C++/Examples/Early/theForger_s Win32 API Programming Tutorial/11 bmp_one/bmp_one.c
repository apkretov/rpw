#include <windows.h>
#include "resource.h"

const char g_szClassName[] = "myWindowClass";
HBITMAP g_hbmBall = NULL;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch(msg)	{
		case WM_CREATE:
			g_hbmBall = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BALL)); //The first step is of course loading the bitmap, this is quite simple with a bitmap resource, there are no significant differences from loading other resource types. @ http://winprog.org/tutorial/bitmaps.html
			if (g_hbmBall == NULL) MessageBox(hwnd, "Could not load IDB_BALL!", "Error", MB_OK | MB_ICONEXCLAMATION);
			break;
		case WM_CLOSE: DestroyWindow(hwnd); break;
		case WM_PAINT: { //Just a note, never use a MessageBox from inside WM_PAINT. The box will cause more WM_PAINT messages and you'll probably end up stuck in a loop.
			BITMAP bm; //Holds information about an HBITMAP which is the actual GDI object. @ http://winprog.org/tutorial/bitmaps.html
			PAINTSTRUCT ps; //Contains information about the window being painted and the paint message. @ http://winprog.org/tutorial/bitmaps.html
			HDC hdc = BeginPaint(hwnd, &ps); //Returns an HDC that represents the HWND that we pass to it. @ http://winprog.org/tutorial/bitmaps.html 
			HDC hdcMem = CreateCompatibleDC(hdc); //In order to draw, we need to create a DC in memory. @ http://winprog.org/tutorial/bitmaps.html
			HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, g_hbmBall); //Select the bitmap into the DC and store the default bitmap to replace it later on. @ http://winprog.org/tutorial/bitmaps.html 
			GetObject(g_hbmBall, sizeof(bm), &bm); //Get the height and width of the HBITMAP. @ http://winprog.org/tutorial/bitmaps.html
			BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY); //Copy the image from our Memory DC to the Window DC, thus displaying on the screen. @ http://winprog.org/tutorial/bitmaps.html
			//TEST BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, DSTINVERT); //Myself: similar: BLACKNESS, PATINVERT.
			//TEST BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, MERGEPAINT); //Myself: similar: PATCOPY, PATPAINT, SRCERASE, SRCPAINT, WHITENESS.
			//TEST BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, NOTSRCCOPY);
			SelectObject(hdcMem, hbmOld); //Restore the Memory DC to the state it was when we got it. @ http://winprog.org/tutorial/bitmaps.html
			DeleteDC(hdcMem); //Delete the Memory DC. @ http://winprog.org/tutorial/bitmaps.html
			EndPaint(hwnd, &ps); //Release the Window DC. // Destroying an HDC is a little confusing sometimes because there are at least 3 ways to do it depending on how you got it in the first place. Here's a list of the common methods of gaining an HDC, and how to release it when you're done. GetDC() - ReleaseDC(), BeginPaint() - EndPaint(), CreateCompatibleDC() - DeleteDC(). @ http://winprog.org/tutorial/bitmaps.html
			}break;
		case WM_DESTROY:
			DeleteObject(g_hbmBall); //Free any resources that we allocated. @ http://winprog.org/tutorial/bitmaps.html
			PostQuitMessage(0);
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
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, g_szClassName, "11 A Bitmap Program", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 240, 120, NULL, NULL, hInstance, NULL);
	if (hwnd == NULL)	{
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
