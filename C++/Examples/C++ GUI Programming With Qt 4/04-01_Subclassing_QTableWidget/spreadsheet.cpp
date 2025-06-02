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

void Spreadsheet::clear() {
    setRowCount(0);
    setColumnCount(0);
    setRowCount(RowCount);
    setColumnCount(ColumnCount);

    for (int i = 0; i < ColumnCount; ++i) {
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(QString(QChar('A' + i)));
        setHorizontalHeaderItem(i, item);
    }

    setCurrentCell(0, 0);
}

Cell *Spreadsheet::cell(int row, int column) const { return static_cast<Cell *>(item(row, column)); }

QString Spreadsheet::text(int row, int column) const {
    Cell *c = cell(row, column);
    if (c)
        return c->text();
    else
        return "";
}

QString Spreadsheet::formula(int row, int column) const {
    Cell *c = cell(row, column);
    if (c)
        return c->formula();
    else
        return "";
}
#pragma endregion //Subclassing QTableWidget
