#include "djviewview.h"
#include "ui_djviewview.h"

DJViewView::DJViewView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DJViewView)
{
    ui->setupUi(this);
}

DJViewView::~DJViewView()
{
    delete ui;
}
