#ifndef DJVIEWVIEW_H
#define DJVIEWVIEW_H

#include <QWidget>

namespace Ui {
class DJViewView;
}

class DJViewView : public QWidget
{
    Q_OBJECT

public:
    explicit DJViewView(QWidget *parent = nullptr);
    ~DJViewView();

private:
    Ui::DJViewView *ui;
};

#endif // DJVIEWVIEW_H
