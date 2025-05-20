#ifndef MYCLASS_H
#define MYCLASS_H

#include <string>

class MyClass {
using string = std::string;
public:
    MyClass(const string& text);
    const string& text() const;
    void setText( const string& text );
    int getLengthOfText() const;
private:
    string m_text;
};

MyClass::MyClass(const string& text) : m_text(text) {}
const MyClass::string& MyClass::text() const { return m_text; }
void MyClass::setText(const string& text) { m_text = text; }
int MyClass::getLengthOfText() const { return m_text.length(); }
#endif // MYCLASS_H
