#pragma once
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_GIF_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Shared_Image.H>
#include <thread>
#include <mutex>
#include <memory>
#include <string>
#include "Icon.h"

class ImageProxy : public Icon {
private:
    std::unique_ptr<Fl_Image> imageIcon;
    std::string imageURL;
    std::thread retrievalThread;
    bool retrieving;
    std::mutex imageMutex;

    void loadImage() {
        try {
            // Download image to a temporary file
            std::string tempFile = std::tmpnam(nullptr);
            std::string cmd = "curl -s -o " + tempFile + " " + imageURL;
            system(cmd.c_str());

            // Load the image based on file extension
            if (imageURL.find(".jpg") != std::string::npos || 
                imageURL.find(".jpeg") != std::string::npos) {
                imageIcon.reset(new Fl_JPEG_Image(tempFile.c_str()));
            }
            else if (imageURL.find(".gif") != std::string::npos) {
                imageIcon.reset(new Fl_GIF_Image(tempFile.c_str()));
            }
            else if (imageURL.find(".png") != std::string::npos) {
                imageIcon.reset(new Fl_PNG_Image(tempFile.c_str()));
            }

            // Clean up temporary file
            remove(tempFile.c_str());
        }
        catch (const std::exception& e) {
            fl_alert("Error loading image: %s", e.what());
        }
    }

public:
    ImageProxy(const std::string& url) 
        : imageURL(url), retrieving(false) {}

    ~ImageProxy() {
        if (retrievalThread.joinable()) {
            retrievalThread.join();
        }
    }

    int getIconWidth() const override {
        std::lock_guard<std::mutex> lock(imageMutex);
        return imageIcon ? imageIcon->w() : 800;
    }

    int getIconHeight() const override {
        std::lock_guard<std::mutex> lock(imageMutex);
        return imageIcon ? imageIcon->h() : 600;
    }

    void paintIcon(Fl_Widget* c, int x, int y) override {
        std::lock_guard<std::mutex> lock(imageMutex);
        if (imageIcon) {
            imageIcon->draw(x, y);
        }
        else {
            fl_font(FL_HELVETICA, 16);
            fl_draw("Loading album cover, please wait...", x + 300, y + 190);
            
            if (!retrieving) {
                retrieving = true;
                retrievalThread = std::thread([this, c]() {
                    loadImage();
                    c->redraw();
                });
                retrievalThread.detach();
            }
        }
    }
};