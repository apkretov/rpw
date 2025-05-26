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
#include <QDialog>
#include "ui_GoToCellDialog.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Ui::GoToCellDialog ui;
    QDialog *dialog = new QDialog;
    ui.setupUi(dialog);
    dialog->show();
    return app.exec();
}
#endif //ORIG
