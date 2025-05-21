#pragma once

#include <QObject>
#include <QString>

#pragma region Listing 1-5. MyClass using QString instead of string
class MyClass : public QObject {
    QString m_text;
public:
    MyClass(const QString& text, QObject *parent = 0) : m_text(text), QObject(parent) {}
    const QString& text() const { return m_text; }
    void setText(const QString& text) { m_text = text; }
    int getLengthOfText() const { return m_text.length(); }
};
#pragma endregion //Listing 1-5. MyClass using QString instead of string
