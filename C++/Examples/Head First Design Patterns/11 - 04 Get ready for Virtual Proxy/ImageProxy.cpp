#include "ImageProxy.h"
#include <wininet.h>
#include <vector>
#include <Shlwapi.h>

#pragma comment(lib, "Shlwapi.lib")

void ImageProxy::Paint(HDC hdc, int x, int y) {
    if (imageIcon) {
        Gdiplus::Graphics graphics(hdc);
        graphics.DrawImage(imageIcon.get(), x, y);
    } else {
        SetTextAlign(hdc, TA_CENTER);
        TextOut(hdc, x + 400, y + 300, L"Loading album cover, please wait...", 31);

        if (!retrieving) {
            retrieving = true;
            retrievalThread = std::thread([this]() {
                HINTERNET hInternet = InternetOpen(L"ImageProxy", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
                if (hInternet) {
                    HINTERNET hFile = InternetOpenUrl(hInternet, imageURL.c_str(), NULL, 0, 
                        INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE, 0);
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