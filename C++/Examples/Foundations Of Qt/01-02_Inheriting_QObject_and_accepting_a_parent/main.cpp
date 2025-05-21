#include <QCoreApplication>
#include <QDebug>
#include "../stdafx.h"
#include "MyClass.h"

#pragma region Listing 1-4. Dynamic memory with Qt
int main(int argc, char *argv[]) {
    // QCoreApplication a(argc, argv);

    print_file_line(); //MINE

    // MyClass myClass("test");
    // std::cout << "Text: " << myClass.text() << '\n';
    // std::cout << "Length of text: " << myClass.getLengthOfText() << '\n';

    // myClass.setText("new text");
    // std::cout << "Updated text: " << myClass.text() << '\n';

    // return a.exec();

    QObject parent;
    MyClass *a, *b, *c;

    a = new MyClass( "foo", &parent );
    b = new MyClass( "ba-a-ar", &parent );
    c = new MyClass( "baz", &parent );

    qDebug() << QString::fromStdString(a->text()) << " (" << a->getLengthOfText() << ")";
    a->setText( b->text() );
    qDebug() << QString::fromStdString(a->text()) << " (" << a->getLengthOfText() << ")";

    return a->getLengthOfText() - c->getLengthOfText();
}
#pragma endregion //Listing 1-4. Dynamic memory with Qt
