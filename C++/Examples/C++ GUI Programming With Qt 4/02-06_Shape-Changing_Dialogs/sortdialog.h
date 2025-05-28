#ifndef SORTDIALOG_H //To add code to the form, we will use the same multiple inheritance approach
#define SORTDIALOG_H

#include <QDialog>
#include "ui_sortdialog.h"

class SortDialog : public QDialog, public Ui::SortDialog {
    Q_OBJECT
public:
    SortDialog(QWidget *parent = 0);
    void setColumnRange(QChar first, QChar last);
};
#endif //To add code to the form, we will use the same multiple inheritance approach
