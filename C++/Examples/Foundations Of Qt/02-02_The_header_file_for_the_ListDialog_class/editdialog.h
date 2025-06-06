#pragma once

#include <QDialog> //MINE
#include "ui_editdialog.h" //MINE

#pragma region Listing 2-7. Editing dialog class
class EditDialog : public QDialog {
public:
    EditDialog(QWidget *parent = 0);
    const QString name() const;
    void setName(const QString &);
    const QString number() const;
    void setNumber(const QString &);
private:
    Ui::EditDialog ui;
};
#pragma endregion // Listing 2-7. Editing dialog class
