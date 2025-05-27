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

#else //ORIG //We can make the dialog function properly by writing some code.

#ifndef GOTOCELLDIALOG_H
#define GOTOCELLDIALOG_H

#include <QDialog>
#include "ui_gotocelldialog.h"

class GoToCellDialog : public QDialog, Ui::GoToCellDialog {
    Q_OBJECT
public:
    GoToCellDialog(QWidget *parent = 0);
private slots:
    void on_lineEdit_textChanged();
};
#endif // GOTOCELLDIALOG_H
#endif //ORIG //We can make the dialog function properly by writing some code.
