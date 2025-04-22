#pragma once
#include <FL/Fl.H>
#include <FL/fl_draw.H>

class Icon {
public:
    virtual ~Icon() = default;
    virtual int getIconWidth() const = 0;
    virtual int getIconHeight() const = 0;
    virtual void paintIcon(Fl_Widget* c, int x, int y) = 0;
};