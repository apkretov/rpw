#pragma once

#pragma region Subclassing QTableWidget
class SpreadsheetCompare {
public:
    bool operator()(const QStringList &row1, const QStringList &row2) const;
    enum { KeyCount = 3 };
    int keys[KeyCount];
    bool ascending[KeyCount];
};
#pragma endregion //Subclassing QTableWidget
