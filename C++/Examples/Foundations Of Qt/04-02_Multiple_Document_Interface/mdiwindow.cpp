#include "mdiwindow.h"
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QSignalMapper>
#include <QStatusBar>

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
