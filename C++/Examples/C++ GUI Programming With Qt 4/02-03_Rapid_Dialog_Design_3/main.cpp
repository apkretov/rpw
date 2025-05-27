#ifdef QT

#include "gotocelldialog.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    GoToCellDialog w;
    w.show();
    return a.exec();
}

#else //ORIG //We can make the dialog function properly by writing some code.

#include <QApplication>
#include "gotocelldialog.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    GoToCellDialog dialog;
    dialog.show();
    return app.exec();
}
#endif //ORIG //We can make the dialog function properly by writing some code.
