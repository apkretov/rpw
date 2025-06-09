#include "mdiwindow.h"
#include <QWorkspace>

#pragma region Listing 4-8. Constructor of the main window with differences between MDI and SDI highlighted
MdiWindow::MdiWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle(tr("MDI"));
    workspace = new QWorkspace;
    setCentralWidget(workspace);
    connect(workspace, SIGNAL(windowActivated(QWidget *)), this, SLOT(enableActions()));
    mapper = new QSignalMapper(this);
    connect(mapper, SIGNAL(mapped(QWidget *)), workspace, SLOT(setActiveWindow(QWidget *)));
    createActions();
    createMenus();
    createToolbars();
    statusBar()->showMessage( tr("Done") );
    enableActions();
}
#pragma endregion //Listing 4-8. Constructor of the main window with differences between MDI and SDI highlighted
