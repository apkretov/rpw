#pragma once

#include <QMainWindow>
#include "./ui_djviewcontrol.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class DJView;
}
QT_END_NAMESPACE

class DJViewControl : public QMainWindow {
    Q_OBJECT
public:
    DJViewControl(QWidget *parent = nullptr) : QMainWindow(parent), ui(new Ui::DJView) { ui->setupUi(this); }
    ~DJViewControl() { delete ui; }
private:
    Ui::DJView *ui;
};
