#include "editdialog.h"

#pragma Listing 2-8. Editing an item of the list
EditDialog::EditDialog(QWidget *parent) : QDialog(parent) { ui.setupUi(this); }
#pragma endregion // Listing 2-8. Editing an item of the list

#pragma region Listing 2-9. Editing an item of the list
const QString EditDialog::name() const { return ui.nameEdit->text().replace("--", "").trimmed(); }
void EditDialog::setName(const QString &name) { ui.nameEdit->setText(name); }
#pragma endregion //Listing 2-9. Editing an item of the list
