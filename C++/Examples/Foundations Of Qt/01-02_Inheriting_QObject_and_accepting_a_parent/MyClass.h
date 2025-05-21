#pragma once

#include <QObject>
#include <string>

#pragma region Listing 1-2. Inheriting QObject and accepting a parent
class MyClass {
using string = std::string;
    string m_text;
public:
    MyClass(const string& text, QObject *parent = 0) : m_text(text) {}
    const string& text() const { return m_text; }
    void setText(const string& text) { m_text = text; }
    int getLengthOfText() const { return m_text.length(); }
};
#pragma endregion //Listing 1-2. Inheriting QObject and accepting a parent
