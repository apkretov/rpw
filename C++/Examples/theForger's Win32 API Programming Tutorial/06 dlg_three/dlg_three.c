#include <windows.h>
#include "resource.h" 

HBRUSH g_hbrBackground = NULL;

BOOL CALLBACK DlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message)	{
		case WM_INITDIALOG:
			g_hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
			//ORIG SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION)));
			//ORIG SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION)));
			SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(NULL, MAKEINTRESOURCE(IDI_ASTERISK))); //TEST //GetIconInfo function @ https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k(WINUSER%2FIDI_APPLICATION);k(IDI_APPLICATION);k(DevLang-C%2B%2B);k(TargetOS-Windows)&rd=true
			SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)LoadIcon(NULL, MAKEINTRESOURCE(IDI_ASTERISK))); //TEST
			//TEST SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(NULL, MAKEINTRESOURCE(IDI_WINLOGO)));
			//TEST SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)LoadIcon(NULL, MAKEINTRESOURCE(IDI_WINLOGO)));
			//TEST SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(NULL, MAKEINTRESOURCE(IDI_QUESTION)));
			//TEST SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)LoadIcon(NULL, MAKEINTRESOURCE(IDI_QUESTION)));
			//TEST SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(NULL, MAKEINTRESOURCE(IDI_HAND)));
			//TEST SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)LoadIcon(NULL, MAKEINTRESOURCE(IDI_HAND)));
			break;
		case WM_CLOSE: EndDialog(hwnd, 0); break;
		case WM_CTLCOLORDLG: 
			return (LONG)g_hbrBackground;
			//TEST return GetSysColorBrush(COLOR_BTNFACE);
		case WM_CTLCOLORSTATIC: {
			HDC hdcStatic = (HDC)wParam;
			SetTextColor(hdcStatic, RGB(255, 255, 255));
			//ORIG SetBkMode(hdcStatic, TRANSPARENT); //If you leave this line off the background will be filled in with the brush you specify, but when the control draws the text it will get written over with the default background color! Setting the text drawing mode to transparent fixes this problem. @ http://winprog.org/tutorial/dlgfaq.html
			//TEST SetBkMode(hdcStatic, OPAQUE);
			//TEST SetBkMode(hdcStatic, BKMODE_LAST);
			SetBkColor(hdcStatic, RGB(0, 0, 0)); //The other option would be to SetBkColor() to the same color as our background brush.  @ http://winprog.org/tutorial/dlgfaq.html
			return (LONG)g_hbrBackground;
			//TEST return GetSysColorBrush(COLOR_BTNFACE);
			} break;
		case WM_COMMAND:
			switch (LOWORD(wParam)) {
				case IDOK: EndDialog(hwnd, 0); break;
			} 
			break;
		case WM_DESTROY: DeleteObject(g_hbrBackground); break;
		default: return FALSE;
	}
	return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) { return DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, DlgProc); }
