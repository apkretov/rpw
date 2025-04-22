#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <map>
#include <string>
#include "ImageComponent.h"
#include "ImageProxy.h"

class AlbumCoverViewer : public Fl_Double_Window {
private:
    std::map<std::string, std::string> albums;
    Fl_Menu_Bar* menuBar;
    ImageComponent* imageComponent;

    static void menuCallback(Fl_Widget*, void* v) {
        AlbumCoverViewer* viewer = (AlbumCoverViewer*)v;
        const Fl_Menu_Item* item = viewer->menuBar->mvalue();
        if (item) {
            viewer->loadAlbum(item->label());
        }
    }

    void loadAlbum(const char* name) {
        auto it = albums.find(name);
        if (it != albums.end()) {
            imageComponent->setIcon(new ImageProxy(it->second));
        }
    }

public:
    AlbumCoverViewer()
        : Fl_Double_Window(800, 600, "Album Cover Viewer") {
        
        // Initialize album collection
        albums["Buddha Bar"] = "http://images.amazon.com/images/P/B00009XBYK.01.LZZZZZZZ.jpg";
        albums["Ima"] = "http://images.amazon.com/images/P/B000005IRM.01.LZZZZZZZ.jpg";
        albums["Karma"] = "http://images.amazon.com/images/P/B000005DCB.01.LZZZZZZZ.gif";
        albums["MCMXC a.D."] = "http://images.amazon.com/images/P/B000002URV.01.LZZZZZZZ.jpg";
        albums["Northern Exposure"] = "http://images.amazon.com/images/P/B000003SFN.01.LZZZZZZZ.jpg";
        albums["Selected Ambient Works, Vol. 2"] = "http://images.amazon.com/images/P/B000002MNZ.01.LZZZZZZZ.jpg";

        // Create menu bar
        menuBar = new Fl_Menu_Bar(0, 0, w(), 25);
        menuBar->add("Favorite Albums/Buddha Bar", 0, menuCallback, this);
        menuBar->add("Favorite Albums/Ima", 0, menuCallback, this);
        menuBar->add("Favorite Albums/Karma", 0, menuCallback, this);
        menuBar->add("Favorite Albums/MCMXC a.D.", 0, menuCallback, this);
        menuBar->add("Favorite Albums/Northern Exposure", 0, menuCallback, this);
        menuBar->add("Favorite Albums/Selected Ambient Works, Vol. 2", 0, menuCallback, this);

        // Create image component
        imageComponent = new ImageComponent(0, 25, w(), h()-25,
            new ImageProxy(albums["Selected Ambient Works, Vol. 2"]));

        end();
    }

    ~AlbumCoverViewer() {
        delete menuBar;
        delete imageComponent;
    }
};