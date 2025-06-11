#include "djview.h"
#include "./ui_djviewcontrol.h"

DJView::DJView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DJView)
{
    ui->setupUi(this);
}

DJView::~DJView()
{
    delete ui;
}
