#pragma region Listing 2-3. Constructor of the ListDialog class

#include "listdialog.h"
#include "editdialog.h" //MINE

ListDialog::ListDialog() : QDialog() {
    ui.setupUi(this);
    connect(ui.addButton, SIGNAL(clicked()), this, SLOT(addItem()));
    connect(ui.editButton, SIGNAL(clicked()), this, SLOT(editItem()));
    connect(ui.deleteButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
}
#pragma end region //Listing 2-3. Constructor of the ListDialog class

#pragma region Listing 2-4. Adding a new item to the list
void ListDialog::addItem() {
    EditDialog dlg(this);
    if (dlg.exec() == Qt::Accepted)
        ui.list->addItem(dlg.name() + " -- " + dlg.number());
}
#pragma end region //Listing 2-4. Adding a new item to the list

#pragma region Listing 2-5. Deleting an item of the list
void ListDialog::deleteItem() { delete ui.list->currentItem(); }
#pragma end region //Listing

#pragma region Listing 2-6. Editing an item of the list
void ListDialog::editItem() {
    if (!ui.list->currentItem())
        return;

    QStringList parts = ui.list->currentItem()->text().split("--");

    EditDialog dlg(this);
    dlg.setName(parts[0].trimmed());
    dlg.setNumber(parts[1].trimmed());

    if (dlg.exec() == Qt::Accepted)
        ui.list->currentItem()->setText(dlg.name() + " -- " + dlg.number());
}
#pragma end region //Listing 2-6. Editing an item of the list
