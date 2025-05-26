#ifdef QT
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
    Ui::GoToCellDialog *ui;
public:
    GoToCellDialog(QWidget *parent = nullptr);
    ~GoToCellDialog();
};
#endif // GOTOCELLDIALOG_H
#endif //QT
