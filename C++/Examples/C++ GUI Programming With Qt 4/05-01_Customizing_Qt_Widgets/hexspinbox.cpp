#include "hexspinbox.h"

#include <QtGui>
#include "hexspinbox.h"

HexSpinBox::HexSpinBox(QWidget *parent) : QSpinBox(parent) {
    setRange(0, 255);
    validator = new QRegExpValidator(QRegExp("[0-9A-Fa-f]{1,8}"), this);
}
