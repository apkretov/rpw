#pragma region We can make the dialog function properly by writing some code.

#ifndef GOTOCELLDIALOG_H
#define GOTOCELLDIALOG_H

#include <QDialog>
#include "ui_gotocelldialog.h"

class GoToCellDialog : public QDialog, Ui::GoToCellDialog {
    Q_OBJECT
public:
    GoToCellDialog(QWidget *parent = 0);
    QString getCellLocation() const; //MINE
private slots:
    void on_lineEdit_textChanged();
};
#endif // GOTOCELLDIALOG_H
#pragma endregion //We can make the dialog function properly by writing some code.
