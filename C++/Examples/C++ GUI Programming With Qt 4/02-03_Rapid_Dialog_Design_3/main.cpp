#pragma region To make the dialog use a QDialogButtonBox

#include <QApplication>
#include "gotocelldialog.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    GoToCellDialog dialog;
    dialog.show();
    return app.exec();
}
#pragma endregion //To make the dialog use a QDialogButtonBox
