#include <QCoreApplication>
#include "../stdafx.h"
#include "MyClass.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    print_file_line(); //MINE

    MyClass myClass("test");
    std::cout << "Text: " << myClass.text() << '\n';
    std::cout << "Length of text: " << myClass.getLengthOfText() << '\n';

    myClass.setText("new text");
    std::cout << "Updated text: " << myClass.text() << '\n';

    return a.exec();
}
