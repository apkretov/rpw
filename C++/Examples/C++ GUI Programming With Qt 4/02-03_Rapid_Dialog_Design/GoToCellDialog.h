#ifndef GOTOCELLDIALOG_H
#define GOTOCELLDIALOG_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class GoToCellDialog;
}
QT_END_NAMESPACE

class GoToCellDialog : public QWidget {
    Q_OBJECT

public:
    GoToCellDialog(QWidget *parent = nullptr);
    ~GoToCellDialog();

private:
    Ui::GoToCellDialog *ui;
};
#endif // GOTOCELLDIALOG_H
