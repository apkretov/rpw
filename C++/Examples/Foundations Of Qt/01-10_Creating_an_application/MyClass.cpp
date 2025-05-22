#include "MyClass.h"

#pragma region Listing 1-9. Implementing MyClass with signals and slots
void MyClass::setText(const QString &text) {
    if (m_text == text)
        return;
    m_text = text;
    emit textChanged(m_text);
}
#pragma endregion //Listing 1-9. Implementing MyClass with signals and slots
