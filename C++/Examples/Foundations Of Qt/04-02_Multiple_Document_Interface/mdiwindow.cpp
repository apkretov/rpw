#include "mdiwindow.h"
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QSignalMapper>
#include <QStatusBar>
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QCloseEvent>
#include "documentwindow.h"

#pragma region Listing 4-8. Constructor of the main window with differences between MDI and SDI highlighted
MdiWindow::MdiWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle(tr("MDI"));

    workspace = new QMdiArea; //ORIG workspace = new QWorkspace;
    setCentralWidget(workspace);

    connect(workspace, &QMdiArea::subWindowActivated, this, &MdiWindow::enableActions); //ORIG connect(workspace, SIGNAL(windowActivated(QWidget *)), this, SLOT(enableActions()));
    mapper = new QSignalMapper(this);
    connect(mapper, &QSignalMapper::mappedObject, this, [this](QObject *obj) {
        if (QWidget *widget = qobject_cast<QWidget*>(obj))
            if (QMdiSubWindow *window = qobject_cast<QMdiSubWindow*>(widget))
                workspace->setActiveSubWindow(window);
    }); //ORIG connect(mapper, SIGNAL(mapped(QWidget *)), workspace, SLOT(setActiveWindow(QWidget *)));

    createActions();
    createMenus();
    createToolbars();
    statusBar()->showMessage( tr("Done") );

    enableActions();
}
#pragma endregion //Listing 4-8. Constructor of the main window with differences between MDI and SDI highlighted

#pragma region Listing 4-9. Creating actions for the MDI application
void MdiWindow::createActions() {
    newAction = new QAction(tr("&New"), this);
    newAction->setShortcut(tr("Ctrl+N"));
    newAction->setStatusTip(tr("Create a new document"));
    connect(newAction, &QAction::triggered, this, &MdiWindow::fileNew);
    
    closeAction = new QAction(tr("&Close"), this);
    closeAction->setShortcut(tr("Ctrl+W"));
    closeAction->setStatusTip(tr("Close this document"));
    connect(closeAction, &QAction::triggered, workspace, &QMdiArea::closeActiveSubWindow); //ORIG connect(closeAction, SIGNAL(triggered()), workspace, SLOT(closeActiveWindow()));
    
    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    
    cutAction = new QAction(tr("Cu&t"), this);
    cutAction->setShortcut(tr("Ctrl+X"));
    cutAction->setStatusTip(tr("Cut the selection to the clipboard"));
    connect(cutAction, &QAction::triggered, this, &MdiWindow::editCut);
    
    copyAction = new QAction(tr("&Copy"), this);
    copyAction->setShortcut(tr("Ctrl+C"));
    copyAction->setStatusTip(tr("Copy the selection to the clipboard"));
    connect(copyAction, &QAction::triggered, this, &MdiWindow::editCopy);
    
    pasteAction = new QAction(tr("&Paste"), this);
    pasteAction->setShortcut(tr("Ctrl+V"));
    pasteAction->setStatusTip(tr("Paste from the clipboard"));
    connect(pasteAction, &QAction::triggered, this, &MdiWindow::editPaste);
    
    tileAction = new QAction(tr("&Tile"), this);
    tileAction->setStatusTip(tr("Tile windows"));
    connect(tileAction, &QAction::triggered, workspace, &QMdiArea::tileSubWindows); //ORIG connect(tileAction, SIGNAL(triggered()), workspace, SLOT(tile()));
    
    cascadeAction = new QAction(tr("&Cascade"), this);
    cascadeAction->setStatusTip(tr("Cascade windows"));
    connect(cascadeAction, &QAction::triggered, workspace, &QMdiArea::cascadeSubWindows);
    
    nextAction = new QAction(tr("Ne&xt"), this);
    nextAction->setShortcut(tr("Ctrl+Tab"));
    nextAction->setStatusTip(tr("Move to the next window"));
    connect(nextAction, &QAction::triggered, workspace, &QMdiArea::activateNextSubWindow);
    
    previousAction = new QAction(tr("Pre&vious"), this);
    previousAction->setShortcut(tr("Ctrl+Shift+Tab"));
    previousAction->setStatusTip(tr("Move to the previous window"));
    connect(previousAction, &QAction::triggered, workspace, &QMdiArea::activatePreviousSubWindow);
    
    separatorAction = new QAction(this);
    separatorAction->setSeparator(true);
}
#pragma endregion // Listing 4-9. Creating actions for the MDI application

#pragma region Listing 4-10. Enabling and disabling actions
DocumentWindow *MdiWindow::activeDocument() {
    if (QMdiSubWindow *activeSubWindow = workspace->activeSubWindow()) //ORIG return qobject_cast<DocumentWindow *>(workspace->activeWindow());
        return qobject_cast<DocumentWindow *>(activeSubWindow->widget());
    return nullptr;
}

void MdiWindow::enableActions() {
    bool hasDocuments = (activeDocument() != 0);

    closeAction->setEnabled(hasDocuments);
    pasteAction->setEnabled(hasDocuments);
    tileAction->setEnabled(hasDocuments);
    cascadeAction->setEnabled(hasDocuments);
    nextAction->setEnabled(hasDocuments);
    previousAction->setEnabled(hasDocuments);
    separatorAction->setVisible(hasDocuments);

    bool hasSelection = hasDocuments && activeDocument()->textCursor().hasSelection();

    cutAction->setEnabled(hasSelection);
    copyAction->setEnabled(hasSelection);
}
#pragma endregion // Listing 4-10. Enabling and disabling actions

#pragma region Listing 4-11. Passing signals from the main window to the document widget
void MdiWindow::editCut() { activeDocument()->cut(); }

void MdiWindow::editCopy() { activeDocument()->copy(); }

void MdiWindow::editPaste() { activeDocument()->paste(); }
#pragma endregion //Listing 4-11. Passing signals from the main window to the document widget

#pragma region Listing 4-12. Creating the Window menu
void MdiWindow::createMenus() {
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
    
    windowMenu = menuBar()->addMenu(tr("&Window"));
    connect(windowMenu, &QMenu::aboutToShow, this, &MdiWindow::updateWindowList); //ORIG connect(windowMenu, SIGNAL(aboutToShow()), this, SLOT(updateWindowList()));
}
#pragma endregion //Listing 4-12. Creating the Window menu

#pragma region Listing 4-13. Updating the Window menu
void MdiWindow::updateWindowList() {
    windowMenu->clear();

    windowMenu->addAction(tileAction);
    windowMenu->addAction(cascadeAction);
    windowMenu->addSeparator();
    windowMenu->addAction(nextAction);
    windowMenu->addAction(previousAction);
    windowMenu->addAction(separatorAction);

    int i = 1;
    foreach (QMdiSubWindow *w, workspace->subWindowList()) { //ORIG foreach (QWidget *w, workspace->windowList()) {
        QString text;
        if (i < 10)
            text = QString("&%1 %2").arg(i++).arg(w->windowTitle());
        else
            text = w->windowTitle();

        QAction *action = windowMenu->addAction(text);
        action->setCheckable(true);
        action->setChecked(w->widget() == activeDocument()); //ORIG action->setChecked(w == activeDocument());
        connect(action, &QAction::triggered, this, [this, action, w]() {
            workspace->setActiveSubWindow(w);
        }); //ORIG connect(action, SIGNAL(triggered()), mapper, SLOT(map()));
        mapper->setMapping(action, w);
    }
}
#pragma endregion //Listing 4-13. Updating the Window menu

#pragma region Listing 4-14. Creating a new document
void MdiWindow::fileNew() {
    DocumentWindow *document = new DocumentWindow;
    workspace->addSubWindow(document); //ORIG workspace->addWindow(document);
    connect(document, &QTextEdit::copyAvailable, cutAction, &QAction::setEnabled);
    connect(document, &QTextEdit::copyAvailable, copyAction, &QAction::setEnabled);
    document->show();
}
#pragma endregion // Listing 4-14. Creating a new document

#pragma region Listing 4-15. Closing all documents and the main window
void MdiWindow::closeEvent(QCloseEvent *event) {
    workspace->closeAllSubWindows(); //ORIG workspace->closeAllWindows();
    if (activeDocument())
        event->ignore();
}
#pragma endregion //Listing 4-15. Closing all documents and the main window

void MdiWindow::createToolbars() {
    QToolBar *fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newAction);
    
    QToolBar *editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);
}
