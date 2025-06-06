#include <QApplication>
#include "listdialog.h"

#pragma region Listing 2-10. Editing an item of the list
int main(int argc, char **argv) {
    QApplication app(argc, argv);
    ListDialog dlg;
    dlg.show();
    return app.exec();
}
#pragma endregion // Listing 2-10. Editing an item of the list
