#pragma region To add code to the form, we will use the same multiple inheritance approach

#include <QApplication>
#include "sortdialog.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    SortDialog *dialog = new SortDialog;
    dialog->setColumnRange('C', 'F');
    dialog->show();
    return app.exec();
}
#pragma endregion //To add code to the form, we will use the same multiple inheritance approach
