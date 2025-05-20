#include "../stdafx.h"
#include "MyClass.h"

int main() {
    print_file_line();

    MyClass myClass("test");
    std::cout << "Text: " << myClass.text() << '\n';
    std::cout << "Length of text: " << myClass.getLengthOfText() << '\n';

    return 0;
}
