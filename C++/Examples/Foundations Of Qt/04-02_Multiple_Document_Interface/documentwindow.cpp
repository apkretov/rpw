#include "documentwindow.h"
#include <QCloseEvent>
#include <QMessageBox>

#pragma region Listing 4-7. Constructor of the document widget class
DocumentWindow::DocumentWindow(QWidget *parent) : QTextEdit(parent) {
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle(QString("%1[*]").arg("unnamed"));
    connect(document(), &QTextDocument::modificationChanged, this, &DocumentWindow::setWindowModified); //ORIG connect(document(), SIGNAL(modificationChanged(bool)), this, SLOT(setWindowModified(bool)));
}
#pragma endregion // Listing 4-7. Constructor of the document widget class

void DocumentWindow::closeEvent(QCloseEvent *event) {
    if (isSafeToClose())
        event->accept();
    else
        event->ignore();
}

bool DocumentWindow::isSafeToClose() {
    if (isWindowModified()) {
        switch (QMessageBox::warning(this, tr("SDI"), tr("The document has unsaved changes.\n" "Do you want to save it before it is closed?"), QMessageBox::Discard | QMessageBox::Cancel)) {
        case QMessageBox::Cancel:
            return false;
        default:
            return true;
        }
    }
    return true;
}
