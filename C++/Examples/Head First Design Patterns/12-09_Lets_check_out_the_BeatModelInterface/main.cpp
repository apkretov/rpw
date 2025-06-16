#include "DJViewControl.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    DJViewControl w;
    w.show();


    return a.exec();
}
