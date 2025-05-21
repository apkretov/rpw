//OFF #define QT_NO_DEBUG_OUTPUT 1 // Turn off qDebug().

#include <QCoreApplication>
#include <QDebug>
#include "../stdafx.h"
#include "MyClass.h"

#pragma region Listing 1-4. Dynamic memory with Qt
int main(int argc, char *argv[]) {
    print_file_line(); //MINE

    QObject parent;
    MyClass *a, *b, *c;

    a = new MyClass("foo", &parent);
    b = new MyClass("ba-a-ar", &parent);
    c = new MyClass("baz", &parent);

    qDebug() << QString::fromStdString(a->text()) << " (" << a->getLengthOfText() << ")";
    a->setText(b->text());
    qDebug() << QString::fromStdString(a->text()) << " (" << a->getLengthOfText() << ")";

    return a->getLengthOfText() - c->getLengthOfText();
}
#pragma endregion //Listing 1-4. Dynamic memory with Qt
