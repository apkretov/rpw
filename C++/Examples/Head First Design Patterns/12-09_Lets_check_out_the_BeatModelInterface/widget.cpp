#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(ControllerInterface& controller, BeatModelInterface& model, QWidget *parent)
    : QWidget(parent)
    , DJView(controller, model)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    createView();
    createControls();
}

Widget::~Widget()
{
    delete ui;
}
