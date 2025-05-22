#pragma once

#include <QObject>
#include <QString>

#pragma region Listing 1-8. A class with a signal and a slot
class MyClass : public QObject {
    Q_OBJECT
    QString m_text;
public:
    MyClass(const QString& text, QObject *parent = 0) : m_text(text), QObject(parent) {}
    const QString& text() const { return m_text; }
public slots:
    void setText(const QString& text);
signals:
    void textChanged(const QString &);
};
#pragma endregion //Listing 1-8. A class with a signal and a slot
