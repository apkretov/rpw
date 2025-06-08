#include "sdiwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    SdiWindow w;
    w.show();
    return a.exec();
}
