#include "mdiwindow.h"
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QSignalMapper>
#include <QStatusBar>
#include <QAction>
#include <QMenuBar>
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
    // ...
    closeAction = new QAction(tr("&Close"), this);
    closeAction->setShortcut(tr("Ctrl+W"));
    closeAction->setStatusTip(tr("Close this document"));
    connect(closeAction, &QAction::triggered, workspace, &QMdiArea::closeActiveSubWindow); //ORIG connect(closeAction, SIGNAL(triggered()), workspace, SLOT(closeActiveWindow()));
    // ...
    tileAction = new QAction(tr("&Tile"), this);
    tileAction->setStatusTip(tr("Tile windows"));
    connect(tileAction, &QAction::triggered, workspace, &QMdiArea::tileSubWindows); //ORIG connect(tileAction, SIGNAL(triggered()), workspace, SLOT(tile()));
    // ...
    separatorAction = new QAction(this);
    separatorAction->setSeparator(true);
    // ...
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
#ifdef OFF
    pasteAction->setEnabled(hasDocuments);
#endif //OFF
    tileAction->setEnabled(hasDocuments);
#ifdef OFF
    cascadeAction->setEnabled(hasDocuments);
    nextAction->setEnabled(hasDocuments);
    previousAction->setEnabled(hasDocuments);
#endif //OFF
    separatorAction->setVisible(hasDocuments);

    bool hasSelection = hasDocuments && activeDocument()->textCursor().hasSelection();

#ifdef OFF
    cutAction->setEnabled(hasSelection);
    copyAction->setEnabled(hasSelection);
#endif //OFF
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
#ifdef OFF
    menu->addAction(newAction);
#endif //OFF
    menu->addAction(closeAction);
    menu->addSeparator();
#ifdef OFF
    menu->addAction(exitAction);
#endif //OFF
    // ...
    windowMenu = menuBar()->addMenu(tr("&Window"));
    connect(windowMenu, &QMenu::aboutToShow, this, &MdiWindow::updateWindowList); //ORIG connect(windowMenu, SIGNAL(aboutToShow()), this, SLOT(updateWindowList()));
}
#pragma endregion //Listing 4-12. Creating the Window menu

#pragma region Listing 4-13. Updating the Window menu
void MdiWindow::updateWindowList() {
    windowMenu->clear();

    windowMenu->addAction(tileAction);
#ifdef OFF
    windowMenu->addAction(cascadeAction);
#endif //OFF
    windowMenu->addSeparator();
#ifdef OFF
    windowMenu->addAction(nextAction);
    windowMenu->addAction(previousAction);
#endif //OFF
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
