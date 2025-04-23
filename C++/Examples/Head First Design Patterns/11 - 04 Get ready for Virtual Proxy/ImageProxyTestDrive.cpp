#include <windows.h>
#include <gdiplus.h>
#include <map>
#include <string>
#include "ImageProxy.h"

#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "gdiplus.lib")

#pragma region Trae
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/proxy/virtualproxy
package headfirst.designpatterns.proxy.virtualproxy;

import java.net.*;
import javax.swing.*;
import java.util.*;

public class ImageProxyTestDrive {
	ImageComponent imageComponent;
	JFrame frame = new JFrame("Album Cover Viewer");
	JMenuBar menuBar;
	JMenu menu;
	Hashtable<String, String> albums = new Hashtable<String, String>();

	public static void main (String[] args) throws Exception {
		ImageProxyTestDrive testDrive = new ImageProxyTestDrive();
	}

	public ImageProxyTestDrive() throws Exception {
		albums.put("Buddha Bar","http://images.amazon.com/images/P/B00009XBYK.01.LZZZZZZZ.jpg");
		albums.put("Ima","http://images.amazon.com/images/P/B000005IRM.01.LZZZZZZZ.jpg");
		albums.put("Karma","http://images.amazon.com/images/P/B000005DCB.01.LZZZZZZZ.gif");
		albums.put("MCMXC a.D.","http://images.amazon.com/images/P/B000002URV.01.LZZZZZZZ.jpg");
		albums.put("Northern Exposure","http://images.amazon.com/images/P/B000003SFN.01.LZZZZZZZ.jpg");
		albums.put("Selected Ambient Works, Vol. 2","http://images.amazon.com/images/P/B000002MNZ.01.LZZZZZZZ.jpg");

		URL initialURL = new URL((String)albums.get("Selected Ambient Works, Vol. 2"));
		menuBar = new JMenuBar();
		menu = new JMenu("Favorite Albums");
		menuBar.add(menu);
		frame.setJMenuBar(menuBar);

		for (Enumeration<String> e = albums.keys(); e.hasMoreElements();) {
			String name = (String)e.nextElement();
			JMenuItem menuItem = new JMenuItem(name);
			menu.add(menuItem);
			menuItem.addActionListener(event -> {
				imageComponent.setIcon(new ImageProxy(getAlbumUrl(event.getActionCommand())));
				frame.repaint();
			});
		}

		// set up frame and menus

		Icon icon = new ImageProxy(initialURL); // Here we create an image proxy and set it to an initial URL. Whenever you choose a selection from the CD menu, you'll get a new image proxy.
		imageComponent = new ImageComponent(icon); // Next we wrap our proxy in a component so it can be added to the frame. The component will take care of the proxy's width, height and similar details.
		frame.getContentPane().add(imageComponent); // Finally we add the proxy to the frame so it can be displayed.
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(800,600);
		frame.setVisible(true);

	}

	URL getAlbumUrl(String name) {
		try {
			return new URL((String)albums.get(name));
		} catch (MalformedURLException e) {
			e.printStackTrace();
			return null;
		}
	}
}
*/

class ImageProxyTestDrive {
	static constexpr int WINDOW_WIDTH = 800;
	static constexpr int WINDOW_HEIGHT = 600;

	HWND hwnd;
	std::map<std::wstring, std::wstring> albums;
	std::unique_ptr<Icon> currentIcon;
	ULONG_PTR gdiplusToken;

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	ImageProxyTestDrive(HINSTANCE hInstance);
	~ImageProxyTestDrive();
	void Initialize();
	void Paint(HDC hdc);
	void HandleMenuSelection(const std::wstring &albumName);
};

ImageProxyTestDrive::ImageProxyTestDrive(HINSTANCE hInstance) {
	Gdiplus::GdiplusStartupInput gdiplusStartupInput; // Initialize GDI+
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	WNDCLASS wc = {}; // Register window class
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = L"ImageProxyTestDrive";
	RegisterClass(&wc);

	hwnd = CreateWindowEx( // Create window
		0, L"ImageProxyTestDrive", L"Album Cover Viewer",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT,
		NULL, NULL, hInstance, this
	);

	SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
}

ImageProxyTestDrive::~ImageProxyTestDrive() {
	currentIcon.reset();
	Gdiplus::GdiplusShutdown(gdiplusToken);
}

void ImageProxyTestDrive::Initialize() {
	albums[L"Buddha Bar"] = L"http://images.amazon.com/images/P/B00009XBYK.01.LZZZZZZZ.jpg"; // Initialize albums
	albums[L"Ima"] = L"http://images.amazon.com/images/P/B000005IRM.01.LZZZZZZZ.jpg";
	albums[L"Karma"] = L"http://images.amazon.com/images/P/B000005DCB.01.LZZZZZZZ.gif";
	albums[L"MCMXC a.D."] = L"http://images.amazon.com/images/P/B000002URV.01.LZZZZZZZ.jpg";
	albums[L"Northern Exposure"] = L"http://images.amazon.com/images/P/B000003SFN.01.LZZZZZZZ.jpg";
	albums[L"Selected Ambient Works, Vol. 2"] = L"http://images.amazon.com/images/P/B000002MNZ.01.LZZZZZZZ.jpg";

	HMENU hMenu = CreateMenu(); // Create menu
	HMENU hSubMenu = CreatePopupMenu();

	int id = 1;
	for (const auto &album : albums)
		AppendMenu(hSubMenu, MF_STRING, id++, album.first.c_str());

	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hSubMenu, L"Favorite Albums");
	SetMenu(hwnd, hMenu);
	currentIcon = std::make_unique<ImageProxy>(albums[L"Selected Ambient Works, Vol. 2"], hwnd); // Set initial image
	ShowWindow(hwnd, SW_SHOW);
}

void ImageProxyTestDrive::Paint(HDC hdc) {
	if (currentIcon) {
		int x = (WINDOW_WIDTH - currentIcon->GetWidth()) / 2;
		int y = (WINDOW_HEIGHT - currentIcon->GetHeight()) / 2;
		currentIcon->Paint(hdc, x, y);
	}
}

void ImageProxyTestDrive::HandleMenuSelection(const std::wstring &albumName) {
	auto it = albums.find(albumName);
	if (it != albums.end()) {
		currentIcon = std::make_unique<ImageProxy>(it->second, hwnd);
		InvalidateRect(hwnd, NULL, TRUE);
	}
}

LRESULT CALLBACK ImageProxyTestDrive::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	ImageProxyTestDrive *app = reinterpret_cast<ImageProxyTestDrive *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

	switch (uMsg) {
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hwnd, &ps);
				if (app) 
					app->Paint(hdc);
				EndPaint(hwnd, &ps);
				return 0;
			}
		case WM_COMMAND:
			{
				if (HIWORD(wParam) == 0) { // Menu selection
					WCHAR menuText[256];
					MENUITEMINFO mii = {sizeof(MENUITEMINFO)};
					mii.fMask = MIIM_STRING;
					mii.dwTypeData = menuText;
					mii.cch = sizeof(menuText);
					GetMenuItemInfo(GetMenu(hwnd), LOWORD(wParam), FALSE, &mii);
					if (app) 
						app->HandleMenuSelection(menuText);
				}
				return 0;
			}
		case WM_DESTROY:
			{
				PostQuitMessage(0);
				return 0;
			}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {
	ImageProxyTestDrive app(hInstance);
	app.Initialize();

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
#pragma endregion //Trae