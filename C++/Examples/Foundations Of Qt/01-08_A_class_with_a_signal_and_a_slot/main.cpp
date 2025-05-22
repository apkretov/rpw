#include <QDebug>
#include "../stdafx.h"
#include "MyClass.h"

#pragma region Making the Connection
int main(int argc, char *argv[]) {
    print_file_line(); //MINE

    QObject parent;
    MyClass *a = new MyClass("AAA", &parent);
    MyClass *b = new MyClass("BBB", &parent);
    MyClass *c = new MyClass("CCC", &parent);

    qDebug() << "a->text():" << a->text(); //MINE
    qDebug() << "b->text():" << b->text();
    qDebug() << "c->text():" << c->text();

    QObject::connect(a, SIGNAL(textChanged(const QString&)), b, SLOT(setText(const QString&)));
    QObject::connect(b, SIGNAL(textChanged(const QString&)), c, SLOT(setText(const QString&)));
    QObject::connect(c, SIGNAL(textChanged(const QString&)), b, SLOT(setText(const QString&)));

    a->setText("Hello Qt!"); // Test the connections

    qDebug() << "a->text():" << a->text(); //MINE
    qDebug() << "b->text():" << b->text();
    qDebug() << "c->text():" << c->text();

    b->setText("My change to b."); //MINE
    qDebug() << "a->text():" << a->text();
    qDebug() << "b->text():" << b->text();
    qDebug() << "c->text():" << c->text();

    return 0;
}
#pragma endregion //Making the Connection
