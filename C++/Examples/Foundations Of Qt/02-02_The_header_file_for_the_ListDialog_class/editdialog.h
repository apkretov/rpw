#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>

namespace Ui {
    class nameEdit;
}

class EditDialog : public QDialog {
    Q_OBJECT
public:
    explicit EditDialog(QWidget *parent = nullptr);
    ~EditDialog();
private:
    Ui::nameEdit *ui;
};
#endif // EDITDIALOG_H
