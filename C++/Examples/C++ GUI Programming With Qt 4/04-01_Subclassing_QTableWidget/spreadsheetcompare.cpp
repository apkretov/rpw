#pragma region Implementing the Other Menus

#include "spreadsheetcompare.h"
#include <QStringList>

bool SpreadsheetCompare::operator()(const QStringList &row1, const QStringList &row2) const {
    for (int i = 0; i < KeyCount; ++i) {
        int column = keys[i];
        if (column != -1)
            if (row1[column] != row2[column])
                if (ascending[i])
                    return row1[column] < row2[column];
                else
                    return row1[column] > row2[column];
    }
    return false;
}
#pragma endregion //Implementing the Other Menus
