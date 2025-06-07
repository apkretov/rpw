#include "MyDialog.h"   // Required for your custom dialog class
#include <QApplication> // Required for QApplication [27]

int main(int argc, char *argv[]) {
    // Create a QApplication object. For all graphical Qt applications,
    // there must be one (and only one) application instance [25, 28, 29].
    QApplication app(argc, argv);

    // Create an instance of your custom dialog
    MyDialog dialog;

    // Show the dialog. For modal dialogs, exec() is commonly used,
    // which starts the application's event loop and blocks until the dialog is
    // closed [3, 23].
    dialog.exec();

    // When the dialog is closed, exec() returns, and the application exits [3].
    return 0;
}
