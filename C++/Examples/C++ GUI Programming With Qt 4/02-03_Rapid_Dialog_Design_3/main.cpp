#pragma region We can make the dialog function properly by writing some code.

#include <QApplication>
#include "gotocelldialog.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    GoToCellDialog dialog;
    dialog.show();
    return app.exec();
}
#pragma endregion //We can make the dialog function properly by writing some code.
