#include "GoToCellDialog.h"
#include "./ui_GoToCellDialog.h"

GoToCellDialog::GoToCellDialog(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

GoToCellDialog::~GoToCellDialog()
{
    delete ui;
}
