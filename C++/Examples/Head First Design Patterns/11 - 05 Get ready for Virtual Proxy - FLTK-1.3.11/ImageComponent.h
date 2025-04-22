#pragma once
#include <FL/Fl_Widget.H>
#include "Icon.h"

class ImageComponent : public Fl_Widget {
private:
    Icon* icon;

public:
    ImageComponent(int x, int y, int w, int h, Icon* ic)
        : Fl_Widget(x, y, w, h), icon(ic) {}

    void setIcon(Icon* ic) {
        icon = ic;
        redraw();
    }

    void draw() override {
        if (icon) {
            int w = icon->getIconWidth();
            int h = icon->getIconHeight();
            int x = (this->w() - w) / 2;
            int y = (this->h() - h) / 2;
            icon->paintIcon(this, x + this->x(), y + this->y());
        }
    }
};