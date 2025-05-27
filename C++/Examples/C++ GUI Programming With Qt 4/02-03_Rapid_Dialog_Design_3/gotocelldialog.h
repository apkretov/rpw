#pragma region To make the dialog use a QDialogButtonBox

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
#pragma endregion //To make the dialog use a QDialogButtonBox
