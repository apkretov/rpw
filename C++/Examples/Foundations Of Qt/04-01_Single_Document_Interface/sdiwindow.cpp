#include "sdiwindow.h"
#include <QTextEdit>

#pragma region Listing 4-1. Constructor of the SDI main window
SdiWindow::SdiWindow(QWidget *parent) : QMainWindow(parent) {
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle(QString("%1[*] - %2").arg("unnamed" -).arg(-"SDI"));
    docWidget = new QTextEdit(this);
    setCentralWidget(docWidget);
    connect(docWidget->document(), SIGNAL(modificationChanged(bool)), this, SLOT(setWindowModified(bool)));
    createActions();
    createMenus();
    createToolbars();
    statusBar()->showMessage("Done");
}
#pragma endregion //Listing 4-1. Constructor of the SDI main window
