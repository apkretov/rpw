#include <QDebug>
#include "../stdafx.h"
#include "MyClass.h"

#pragma region Making the Connection
int main(int argc, char *argv[]) {
    print_file_line(); //MINE

    QObject parent;
    MyClass *a, *b, *c;

    a = new MyClass( "foo", &parent );
    b = new MyClass( "bar", &parent );
    c = new MyClass( "baz", &parent );

    qDebug() << "a->text():" << a->text(); //MINE
    qDebug() << "b->text():" << b->text();
    qDebug() << "c->text():" << c->text();

    QObject::connect(a, SIGNAL(textChanged(const QString&)), b, SLOT(setText(const QString&)));
    QObject::connect(b, SIGNAL(textChanged(const QString&)), c, SLOT(setText(const QString&)));
    QObject::connect(c, SIGNAL(textChanged(const QString&)), b, SLOT(setText(const QString&)));

    b->setText("test");

    qDebug() << "\na->text():" << a->text(); //MINE
    qDebug() << "b->text():" << b->text();
    qDebug() << "c->text():" << c->text();

    a->setText("Qt");

    qDebug() << "\na->text():" << a->text(); //MINE
    qDebug() << "b->text():" << b->text();
    qDebug() << "c->text():" << c->text();

    return 0;
}
#pragma endregion //Making the Connection
