#include <FL/Fl.H>
#include <FL/Fl_Shared_Image.H>
#include "AlbumCoverViewer.h"

int main(int argc, char *argv[]) {
    fl_register_images();              // Initialize image handlers
    Fl::scheme("gtk+");                // Set modern look and feel
    Fl::visual(FL_DOUBLE|FL_INDEX);    // Enable double buffering

    AlbumCoverViewer *viewer = new AlbumCoverViewer();
    viewer->show();

    return Fl::run();
}