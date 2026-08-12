#include "ImageProxy.h"
#include <wininet.h>
#include <vector>
#include <Shlwapi.h>
#include <urlmon.h>

#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "urlmon.lib")

#pragma region Trae
void ImageProxy::Paint(HDC hdc, int x, int y) { // This method is called when it's time to paint the icon on the screen.
	std::unique_lock<std::mutex> lock(imageMutex);
	if (imageIcon) {
		Gdiplus::Graphics graphics(hdc);
		graphics.DrawImage(imageIcon.get(), x, y); // If we've got an icon already, we go ahead and tell it to paint itself.
		return;
	}
	lock.unlock();

	{
        SetTextAlign(hdc, TA_CENTER);
        TextOut(hdc, x + 400, y + 300, L"Loading album cover, please wait...", 35); // Otherwise we display the “loading” message.

		// Here's where things get interesting. This code paints the icon on the screen (by delegating to the imageIcon). However, if we don't have a fully created ImageIcon, then we create one.
		// Here's where we load the REAL icon image. Note that the image loading with IconImage is synchronous: the ImageIcon constructor doesn't return until the image is loaded. That doesn't give us much of a chance to do screen updates and have our message displayed, so we're going to do this asynchronously
        if (!retrieving) { // If we aren't already trying to retrieve the image...
            retrieving = true; // ...then it's time to start retrieving it (in case you were wondering, only one thread calls paint, so we should be okay here in terms of thread safety).

			retrievalThread = std::thread([this]() { // We don't want to hang up the entire user interface, so we're going to use another thread to retrieve the image.
				WCHAR cacheFile[MAX_PATH] = {};
				if (SUCCEEDED(URLDownloadToCacheFileW(nullptr, imageURL.c_str(), cacheFile, MAX_PATH, 0, nullptr))) {
					auto loadedImage = std::make_unique<Gdiplus::Image>(cacheFile);
					if (loadedImage && loadedImage->GetLastStatus() == Gdiplus::Ok) {
						std::lock_guard<std::mutex> guard(imageMutex);
						imageIcon = std::move(loadedImage);
						InvalidateRect(hwnd, NULL, TRUE);
					}
				}
            });
        }
	}
}
#pragma endregion //Trae