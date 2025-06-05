// #ifndef LISTDIALOG_H
// #define LISTDIALOG_H

// #include <QDialog>

// namespace Ui {
//     class ListDialog;
// }

// class ListDialog : public QDialog {
//     Q_OBJECT
// public:
//     explicit ListDialog(QWidget *parent = nullptr);
//     ~ListDialog();
// private slots:
//     void on_addButton_clicked();
// private:
//     Ui::ListDialog *ui;
// };
// #endif // LISTDIALOG_H

#pragma region Listing 2-2. The header file for the ListDialog class

#include <QDialog>
#include "ui_listdialog.h"
class ListDialog : public QDialog {
    Q_OBJECT
public:
    ListDialog();
private slots:
    void addItem();
    void editItem();
    void deleteItem();
private:
    Ui::ListDialog ui;
};
#pragma endregion //Listing 2-2. The header file for the ListDialog class
