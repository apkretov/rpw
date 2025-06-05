#include "qregexpvalidator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QRegExpValidator w;
    w.show();
    return a.exec();
}
