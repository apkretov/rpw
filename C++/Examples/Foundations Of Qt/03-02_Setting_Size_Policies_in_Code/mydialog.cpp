#include "MyDialog.h"

MyDialog::MyDialog(QWidget *parent) : QDialog(parent) {
#pragma region Listing 3-1. The widgets are created.
    groupBox = new QGroupBox(tr("Groupbox"), this);
    label = new QLabel(tr("Supercalifragilisticexpialidocious"), this);
    lineEdit = new QLineEdit(this);
    buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
#pragma endregion //Listing 3-1. The widgets are created.

#pragma region Listing 3-2. The widgets are laid out.
    QHBoxLayout *hLayout = new QHBoxLayout(groupBox); // 2. Set up layouts (building upon Listing 3-2) // Horizontal layout for label and lineEdit inside the group box // 'groupBox' is parent for hLayout
    hLayout->addWidget(label);
    hLayout->addWidget(lineEdit);

    QVBoxLayout *vLayout = new QVBoxLayout(this); // Vertical layout for the main dialog // 'this' sets MyDialog as parent for vLayout
    vLayout->addWidget(groupBox);
    vLayout->addStretch(); // Adds a stretchable space
    vLayout->addWidget(buttons);
#pragma endregion //Listing 3-2. The widgets are laid out.

    connect(buttons, &QDialogButtonBox::accepted, this, &MyDialog::handleAccepted);
    connect(buttons, &QDialogButtonBox::rejected, this, &MyDialog::handleRejected);

    setLayout(vLayout); // Set the main layout for the dialog
    setWindowTitle(tr("Qt Dialog Example")); // Set a title for the dialog window
}

void MyDialog::handleAccepted() { // This slot is called when the OK button is clicked or accept() is implicitly called.
    qDebug() << "OK button clicked!";
    QMessageBox::information(this, tr("Dialog Status"), tr("You clicked OK!"));
    accept(); // Closes the dialog with accepted status
}

void MyDialog::handleRejected() { // This slot is called when the Cancel button is clicked or reject() is implicitly called.
    qDebug() << "Cancel button clicked!";
    QMessageBox::warning(this, tr("Dialog Status"), tr("You clicked Cancel!"));
    reject(); // Closes the dialog with rejected status
}
