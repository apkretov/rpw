#ifndef DJVIEWVIEW_H
#define DJVIEWVIEW_H

#include <QWidget>
#include "ui_djviewview.h"

namespace Ui {
    class DJViewView;
}

class DJViewView : public QWidget {
    Q_OBJECT
    Ui::DJViewView *ui;
public:
    explicit DJViewView(QWidget *parent = nullptr) : QWidget(parent) , ui(new Ui::DJViewView) { ui->setupUi(this); }
    ~DJViewView() { delete ui; }
};

#endif // DJVIEWVIEW_H
