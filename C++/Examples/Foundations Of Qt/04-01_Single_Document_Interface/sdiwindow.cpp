#include "sdiwindow.h"
#include <QTextEdit>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QApplication>
#include <QCloseEvent>
#include <QMessageBox>

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
    connect(newAction, &QAction::triggered, this, &SdiWindow::fileNew); //ORIG connect(newAction, SIGNAL(triggered()), this, SLOT(fileNew()));
    
    closeAction = new QAction(tr("&Close"), this);
    closeAction->setShortcut(tr("Ctrl+W"));
    closeAction->setStatusTip(tr("Close this document"));
    connect(closeAction, &QAction::triggered, this, &QWidget::close);
    
    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, &QAction::triggered, qApp, &QApplication::closeAllWindows);
    
    cutAction = new QAction(tr("Cu&t"), this); //ORIG cutAction = new QAction(QIcon(":/images/cut.png"), tr("Cu&t"), this);
    cutAction->setShortcut(tr("Ctrl+X"));
    cutAction->setStatusTip(tr("Cut"));
    cutAction->setEnabled(false);
    connect(docWidget, &QTextEdit::copyAvailable, cutAction, &QAction::setEnabled); //ORIG connect(docWidget, SIGNAL(copyAvailable(bool)), cutAction, SLOT(setEnabled(bool)));
    connect(cutAction, &QAction::triggered, docWidget, &QTextEdit::cut); //ORIG connect(cutAction, SIGNAL(triggered()), docWidget, SLOT(cut()));
    
    copyAction = new QAction(tr("&Copy"), this);
    copyAction->setShortcut(tr("Ctrl+C"));
    copyAction->setStatusTip(tr("Copy"));
    copyAction->setEnabled(false);
    connect(docWidget, &QTextEdit::copyAvailable, copyAction, &QAction::setEnabled);
    connect(copyAction, &QAction::triggered, docWidget, &QTextEdit::copy);
    
    pasteAction = new QAction(tr("&Paste"), this);
    pasteAction->setShortcut(tr("Ctrl+V"));
    pasteAction->setStatusTip(tr("Paste"));
    connect(pasteAction, &QAction::triggered, docWidget, &QTextEdit::paste);
    
    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("About this application"));
    connect(aboutAction, &QAction::triggered, this, &SdiWindow::about);
    
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
    
    menu = menuBar()->addMenu(tr("&Edit"));
    menu->addAction(cutAction);
    menu->addAction(copyAction);
    menu->addAction(pasteAction);
    
    menu = menuBar()->addMenu(tr("&Help"));
    menu->addAction(aboutAction);
    menu->addAction(aboutQtAction);
}

void SdiWindow::createToolbars() {
    QToolBar *toolbar;
    toolbar = addToolBar(tr("File"));
    toolbar->addAction(newAction);
    toolbar->addAction(closeAction);
    
    toolbar = addToolBar(tr("Edit"));
    toolbar->addAction(cutAction);
    toolbar->addAction(copyAction);
    toolbar->addAction(pasteAction);
}
#pragma endregion // Listing 4-3. The menus and toolbars are populated.

#pragma Listing 4-4. Creating a new document
void SdiWindow::fileNew() { (new SdiWindow())->show(); }
#pragma endregion // Listing 4-4. Creating a new document

#pragma region Listing 4-5. Closing a document
void SdiWindow::closeEvent(QCloseEvent *event) {
    if (isSafeToClose())
        event->accept();
    else
        event->ignore();
}

bool SdiWindow::isSafeToClose() {
    if (isWindowModified()) {
        switch (QMessageBox::warning(this, tr("SDI"), tr("The document has unsaved changes.\n" "Do you want to save it before it is closed?"), QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel)) {
        case QMessageBox::Save:
            // In a real application, we would save the document here
            return true;
        case QMessageBox::Cancel:
            return false;
        default:
            return true;
        }
    }
    return true;
}
#pragma endregion // Listing 4-5. Closing a document

#pragma region Additional functionality
void SdiWindow::about() {
    QMessageBox::about(this, tr("About SDI Application"),
                       tr("This is a simple SDI application example from "
                          "the Foundations of Qt book."));
}
#pragma endregion // Additional functionality
