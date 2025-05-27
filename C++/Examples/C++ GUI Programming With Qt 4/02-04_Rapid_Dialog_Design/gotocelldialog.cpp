#ifdef QT

#include "gotocelldialog.h"
#include "./ui_gotocelldialog.h"

GoToCellDialog::GoToCellDialog(QWidget *parent) : QWidget(parent), ui(new Ui::GoToCellDialog) { ui->setupUi(this); }
GoToCellDialog::~GoToCellDialog() { delete ui; }

#else //ORIG //We can make the dialog function properly by writing some code.

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
#endif //ORIG //We can make the dialog function properly by writing some code.
