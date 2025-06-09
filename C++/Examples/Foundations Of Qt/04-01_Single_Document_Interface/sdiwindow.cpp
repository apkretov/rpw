#include "sdiwindow.h"
#include <QTextEdit>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>

#pragma region Listing 4-1. Constructor of the SDI main window
SdiWindow::SdiWindow(QWidget *parent) : QMainWindow(parent) {
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle(QString("%1[*] - %2").arg("unnamed").arg("SDI"));
    docWidget = new QTextEdit(this);
    setCentralWidget(docWidget);
    connect(docWidget->document(), &QTextDocument::modificationChanged, this, &QMainWindow::setWindowModified); //ORIG connect(docWidget->document(), SIGNAL(modificationChanged(bool)), this, SLOT(setWindowModified(bool)));
    createActions();
    createMenus();
    createToolbars();
    statusBar()->showMessage("Done");
}
#pragma endregion //Listing 4-1. Constructor of the SDI main window

#pragma region MINE
void SdiWindow::createActions() {}

void SdiWindow::createMenus() {}

void SdiWindow::createToolbars() {}
#pragma endregion //MINE
