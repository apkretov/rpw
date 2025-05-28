#include "sortdialog.h"
#include "./ui_sortdialog.h"

SortDialog::SortDialog(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SortDialog)
{
    ui->setupUi(this);
}

SortDialog::~SortDialog()
{
    delete ui;
}
