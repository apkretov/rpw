#ifndef DJVIEW_H
#define DJVIEW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class DJView;
}
QT_END_NAMESPACE

class DJView : public QMainWindow
{
    Q_OBJECT

public:
    DJView(QWidget *parent = nullptr);
    ~DJView();

private:
    Ui::DJView *ui;
};
#endif // DJVIEW_H
