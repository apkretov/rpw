#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "DJView.h"
#include "BeatModelInterface.h"
#include "ControllerInterface.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget, public DJView
{
    Q_OBJECT

public:
    Widget(ControllerInterface& controller, BeatModelInterface& model, QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
