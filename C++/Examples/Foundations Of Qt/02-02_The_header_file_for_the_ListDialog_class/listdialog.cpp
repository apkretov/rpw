// #include "listdialog.h"
// #include "ui_listdialog.h"

// ListDialog::ListDialog(QWidget *parent) : QDialog(parent), ui(new Ui::ListDialog) { ui->setupUi(this); }
// ListDialog::~ListDialog() { delete ui; }
// void ListDialog::on_addButton_clicked() {}


#pragma region Listing 2-3. Constructor of the ListDialog class

#include "listdialog.h"

ListDialog::ListDialog() : QDialog() {
    ui.setupUi(this);
    connect(ui.addButton, SIGNAL(clicked()), this, SLOT(addItem()));
    connect(ui.editButton, SIGNAL(clicked()), this, SLOT(editItem()));
    connect(ui.deleteButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
}
#pragma end region //Listing 2-3. Constructor of the ListDialog class
