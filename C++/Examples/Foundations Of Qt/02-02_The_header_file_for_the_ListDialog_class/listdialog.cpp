#include "listdialog.h"
#include "ui_listdialog.h"

ListDialog::ListDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ListDialog)
{
    ui->setupUi(this);
}

ListDialog::~ListDialog()
{
    delete ui;
}
