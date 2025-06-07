#include "MyDialog.h"

// Constructor for the MyDialog class
MyDialog::MyDialog(QWidget *parent) : QDialog(parent) {
    // 1. Create the widgets (as shown in Listing 3-1 [1])
    groupBox = new QGroupBox(tr("Groupbox"),
                             this); // 'this' sets MyDialog as parent [21]
    label = new QLabel(tr("Supercalifragilisticexpialidocious"), this);
    lineEdit = new QLineEdit(this);
    buttons =
        new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                                   this); // OK and Cancel buttons [22]

    // 2. Set up layouts (building upon Listing 3-2 [2])
    // Horizontal layout for label and lineEdit inside the group box
    QHBoxLayout *hLayout =
        new QHBoxLayout(groupBox); // 'groupBox' is parent for hLayout [2]
    hLayout->addWidget(label);
    hLayout->addWidget(lineEdit);

    // Vertical layout for the main dialog
    QVBoxLayout *vLayout =
        new QVBoxLayout(this); // 'this' sets MyDialog as parent for vLayout [2]
    vLayout->addWidget(groupBox);
    vLayout->addStretch(); // Adds a stretchable space [2]
    vLayout->addWidget(buttons);

    // Connect QDialogButtonBox signals to QDialog's standard slots,
    // which handle closing the dialog with accepted/rejected results [23, 24].
    connect(buttons, &QDialogButtonBox::accepted, this,
            &MyDialog::handleAccepted);
    connect(buttons, &QDialogButtonBox::rejected, this,
            &MyDialog::handleRejected);

    // Set the main layout for the dialog [2]
    setLayout(vLayout);

    // Set a title for the dialog window
    setWindowTitle(tr("Qt Dialog Example"));
}

void MyDialog::handleAccepted() {
    // This slot is called when the OK button is clicked or accept() is implicitly
    // called.
    qDebug() << "OK button clicked!";
    QMessageBox::information(this, tr("Dialog Status"), tr("You clicked OK!"));
    accept(); // Closes the dialog with accepted status [23]
}

void MyDialog::handleRejected() {
    // This slot is called when the Cancel button is clicked or reject() is
    // implicitly called.
    qDebug() << "Cancel button clicked!";
    QMessageBox::warning(this, tr("Dialog Status"), tr("You clicked Cancel!"));
    reject(); // Closes the dialog with rejected status [23]
}
