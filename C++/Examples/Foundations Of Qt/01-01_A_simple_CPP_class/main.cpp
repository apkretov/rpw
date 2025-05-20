#include "../stdafx.h"
#include "MyClass.h"

int main() {
    print_file_line();

    MyClass myClass("test");
    std::cout << "Text: " << myClass.text() << '\n';
    std::cout << "Length of text: " << myClass.getLengthOfText() << '\n';

    myClass.setText("new text");
    std::cout << "Updated text: " << myClass.text() << '\n';

    return 0;
}
