#ifdef QT
#include "gotocelldialog.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    GoToCellDialog w;
    w.show();
    return a.exec();
}
#else //ORIG

#include <QApplication>
#include "gotocelldialog.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    GoToCellDialog dialog;
    dialog.show();
    return app.exec();
}
#endif //ORIG
