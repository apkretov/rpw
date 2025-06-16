#include <QApplication>
#include "DJViewControl.h"
#include "DJViewView.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    DJViewControl control;
    control.show();

    DJViewView view;
    view.show();

    return a.exec();
}
