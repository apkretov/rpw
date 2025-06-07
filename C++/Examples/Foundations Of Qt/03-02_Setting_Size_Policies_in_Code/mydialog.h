#pragma once

#include <QDialog>            
#include <QGroupBox>         
#include <QLabel>            
#include <QLineEdit>         
#include <QDialogButtonBox>      
#include <QHBoxLayout>       
#include <QVBoxLayout>       
#include <QMessageBox>          
#include <QtDebug>          

class MyDialog : public QDialog {
    Q_OBJECT
public:
    explicit MyDialog(QWidget *parent = nullptr);
private slots:
    void handleAccepted();
    void handleRejected();
private:
    QGroupBox *groupBox;
    QLabel *label;
    QLineEdit *lineEdit;
    QDialogButtonBox *buttons;
};

