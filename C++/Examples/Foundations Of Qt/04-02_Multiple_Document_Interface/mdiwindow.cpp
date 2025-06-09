#include "mdiwindow.h"
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QSignalMapper>
#include <QStatusBar>
#include <QAction>

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
