#include "spreadsheet.h"

#pragma region Subclassing QTableWidget

#include <QtGui>
#include "cell.h"
#include "spreadsheet.h"

Spreadsheet::Spreadsheet(QWidget *parent) : QTableWidget(parent) {
    autoRecalc = true;

    setItemPrototype(new Cell);
    setSelectionMode(ContiguousSelection);

    connect(this, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(somethingChanged()));

    clear();
}
#pragma endregion //Subclassing QTableWidget
