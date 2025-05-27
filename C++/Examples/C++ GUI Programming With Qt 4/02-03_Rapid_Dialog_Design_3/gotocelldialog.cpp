#pragma region To make the dialog use a QDialogButtonBox

#include <QtGui>
#include "gotocelldialog.h"

GoToCellDialog::GoToCellDialog(QWidget *parent) : QDialog(parent) {
    setupUi(this);

    QRegularExpression regExp("[A-Za-z][1-9][0-9]{0,2}");
    lineEdit->setValidator(new QRegularExpressionValidator(regExp, this));

    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

void GoToCellDialog::on_lineEdit_textChanged() { okButton->setEnabled(lineEdit->hasAcceptableInput()); }
#pragma endregion //To make the dialog use a QDialogButtonBox
