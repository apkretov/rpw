#ifndef QREGEXPVALIDATOR_H
#define QREGEXPVALIDATOR_H

#include <QWidget>

class QRegExpValidator : public QWidget
{
    Q_OBJECT

public:
    QRegExpValidator(QWidget *parent = nullptr);
    ~QRegExpValidator();
};
#endif // QREGEXPVALIDATOR_H
