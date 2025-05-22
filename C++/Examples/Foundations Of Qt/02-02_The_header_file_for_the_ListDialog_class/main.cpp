#include "listdialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ListDialog w;
    w.show();
    return a.exec();
}
