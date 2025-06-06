#pragma once

#pragma region Listing 2-2. The header file for the ListDialog class
#include <QDialog>
#include "ui_listdialog.h"

class ListDialog : public QDialog {
    Q_OBJECT
    Ui::ListDialog ui;
public:
    ListDialog();
private slots:
    void addItem();
    void editItem();
    void deleteItem();
};
#pragma endregion //Listing 2-2. The header file for the ListDialog class
