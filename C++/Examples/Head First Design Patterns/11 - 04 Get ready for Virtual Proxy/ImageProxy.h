#pragma once
#include <windows.h>
#include <gdiplus.h>
#include <string>
#include <memory>
#include <thread>
#include <atomic>

class Icon {
public:
    virtual int GetWidth() const = 0;
    virtual int GetHeight() const = 0;
    virtual void Paint(HDC hdc, int x, int y) = 0;
    virtual ~Icon() = default;
};

class ImageProxy : public Icon {
private:
    std::unique_ptr<Gdiplus::Image> imageIcon;
    std::wstring imageURL;
    std::thread retrievalThread;
    std::atomic<bool> retrieving;
    HWND hwnd;

public:
    ImageProxy(const std::wstring& url, HWND window) 
        : imageURL(url), retrieving(false), hwnd(window) {}

    ~ImageProxy() {
        if (retrievalThread.joinable()) {
            retrievalThread.join();
        }
    }

    int GetWidth() const override {
        return imageIcon ? imageIcon->GetWidth() : 800;
    }

    int GetHeight() const override {
        return imageIcon ? imageIcon->GetHeight() : 600;
    }

    void Paint(HDC hdc, int x, int y) override;
};