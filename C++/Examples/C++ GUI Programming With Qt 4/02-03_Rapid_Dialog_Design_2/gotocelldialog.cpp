#ifdef QT
#include "gotocelldialog.h"
#include "./ui_gotocelldialog.h"

GoToCellDialog::GoToCellDialog(QWidget *parent) : QWidget(parent), ui(new Ui::GoToCellDialog) { ui->setupUi(this); }
GoToCellDialog::~GoToCellDialog() { delete ui; }
#endif //QT
