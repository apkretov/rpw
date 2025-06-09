#include "sdiwindow.h"
#include <QTextEdit>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QApplication>

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

#pragma region Listing 4-2. Creating actions for the SDI application
void SdiWindow::createActions() {
    newAction = new QAction(tr("&New"), this); //ORIG newAction = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
    newAction->setShortcut(tr("Ctrl+N"));
    newAction->setStatusTip(tr("Create a new document"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(fileNew())); //MINE connect(newAction, &QAction::triggered, this, &SdiWindow::fileNew);
    // ...
    cutAction = new QAction(tr("Cu&t"), this); //ORIG cutAction = new QAction(QIcon(":/images/cut.png"), tr("Cu&t"), this);
    cutAction->setShortcut(tr("Ctrl+X"));
    cutAction->setStatusTip(tr("Cut"));
    cutAction->setEnabled(false);
    connect(docWidget, &QTextEdit::copyAvailable, cutAction, &QAction::setEnabled); //ORIG connect(docWidget, SIGNAL(copyAvailable(bool)), cutAction, SLOT(setEnabled(bool)));
    connect(cutAction, &QAction::triggered, docWidget, &QTextEdit::cut); //ORIG connect(cutAction, SIGNAL(triggered()), docWidget, SLOT(cut()));
    // ...
    aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setStatusTip(tr("About the Qt toolkit"));
    connect(aboutQtAction, &QAction::triggered, qApp, &QApplication::aboutQt); //ORIG connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}
#pragma endregion //Listing 4-2. Creating actions for the SDI application

#pragma region Listing 4-3. The menus and toolbars are populated.
void SdiWindow::createMenus() {
    QMenu *menu;
    menu = menuBar()->addMenu(tr("&File"));
    menu->addAction(newAction);
    menu->addAction(closeAction);
    menu->addSeparator();
    menu->addAction(exitAction);
    // ...
}

void SdiWindow::createToolbars() {
    QToolBar *toolbar;
    toolbar = addToolBar(tr("File"));
    toolbar->addAction(newAction);
    // ...
}
#pragma endregion // Listing 4-3. The menus and toolbars are populated.
