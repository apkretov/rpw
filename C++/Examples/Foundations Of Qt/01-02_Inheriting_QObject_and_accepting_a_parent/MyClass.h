#pragma once

#include <QObject>
#include <string>

class MyClass {
using string = std::string;
    string m_text;
public:
    MyClass(const string& text, QObject *parent = 0) : m_text(text) {}
    const string& text() const { return m_text; }
    void setText(const string& text) { m_text = text; }
    int getLengthOfText() const { return m_text.length(); }
};

