#pragma once

#include <QMainWindow>
#include "./ui_djviewcontrol.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class DJView;
}
QT_END_NAMESPACE

class DJView : public QMainWindow {
    Q_OBJECT
public:
    DJView(QWidget *parent = nullptr) : QMainWindow(parent), ui(new Ui::DJView) { ui->setupUi(this); }
    ~DJView() { delete ui; }
private:
    Ui::DJView *ui;
};
