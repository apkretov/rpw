#pragma once

#pragma region Customizing Qt Widgets

#include <QSpinBox>

class QRegExpValidator;

class HexSpinBox : public QSpinBox {
    Q_OBJECT
public:
    HexSpinBox(QWidget *parent = 0);
protected:
    QValidator::State validate(QString &text, int &pos) const;
    int valueFromText(const QString &text) const;
    QString textFromValue(int value) const;
private:
    QRegExpValidator *validator;
};
#pragma endregion //Customizing Qt Widgets
