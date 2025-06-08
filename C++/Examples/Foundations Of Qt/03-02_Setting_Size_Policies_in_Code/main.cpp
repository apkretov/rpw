#include <QApplication>
#include "MyDialog.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MyDialog dialog;
    dialog.exec();
    return 0;
}
