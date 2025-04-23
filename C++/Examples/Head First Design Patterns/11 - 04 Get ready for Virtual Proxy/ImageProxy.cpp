#include "ImageProxy.h"
#include <wininet.h>
#include <vector>
#include <Shlwapi.h>

#pragma comment(lib, "Shlwapi.lib")

#pragma region Trae
void ImageProxy::Paint(HDC hdc, int x, int y) { // This method is called when it's time to paint the icon on the screen.
    if (imageIcon) {
        Gdiplus::Graphics graphics(hdc);
        graphics.DrawImage(imageIcon.get(), x, y); // If we've got an icon already, we go ahead and tell it to paint itself.
    } else {
        SetTextAlign(hdc, TA_CENTER);
        TextOut(hdc, x + 400, y + 300, L"Loading album cover, please wait...", 35); // Otherwise we display the “loading” message.

		// Here's where things get interesting. This code paints the icon on the screen (by delegating to the imageIcon). However, if we don't have a fully created ImageIcon, then we create one.
		// Here's where we load the REAL icon image. Note that the image loading with IconImage is synchronous: the ImageIcon constructor doesn't return until the image is loaded. That doesn't give us much of a chance to do screen updates and have our message displayed, so we're going to do this asynchronously
        if (!retrieving) { // If we aren't already trying to retrieve the image...
            retrieving = true; // ...then it's time to start retrieving it (in case you were wondering, only one thread calls paint, so we should be okay here in terms of thread safety).

			retrievalThread = std::thread([this]() { // We don't want to hang up the entire user interface, so we're going to use another thread to retrieve the image.
                HINTERNET hInternet = InternetOpen(L"ImageProxy", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
                if (hInternet) {
                    HINTERNET hFile = InternetOpenUrl(hInternet, imageURL.c_str(), NULL, 0, INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE, 0);
                    if (hFile) {
                        std::vector<BYTE> buffer;
                        DWORD bytesRead;
                        char temp[4096];
                        
                        while (InternetReadFile(hFile, temp, sizeof(temp), &bytesRead) && bytesRead > 0)
                            buffer.insert(buffer.end(), temp, temp + bytesRead);

                        IStream* stream = SHCreateMemStream(buffer.data(), buffer.size());
                        if (stream) {
                            imageIcon = std::make_unique<Gdiplus::Image>(stream);
                            stream->Release();
                            InvalidateRect(hwnd, NULL, TRUE);
                        }

                        InternetCloseHandle(hFile);
                    }
                    InternetCloseHandle(hInternet);
                }
            });
            retrievalThread.detach();
        }
    }
}
#pragma endregion //Trae