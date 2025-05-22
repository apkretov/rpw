#include <QCoreApplication>
#include <QList>
#include <QDebug>

void Listing_1_13() { //Listing 1-13. Populating a QList and printing the contents
    QList<QString> list;
    list << "foo" << "bar" << "baz";
    foreach(QString s, list)
        qDebug() << s;
}

void Listing_1_14() { //Listing 1-14. STL-style iterators and Java-style iterators side by side
    QList<int> list;
    list << 23 << 27 << 52 << 52;

    QListIterator<int> javaIter( list ); //Java-style.
    while(javaIter.hasNext())
        qDebug() << javaIter.next();

    QList<int>::const_iterator stlIter; //STL-style.
    for(stlIter = list.begin(); stlIter != list.end(); ++stlIter)
        qDebug() << (*stlIter);
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    
    Listing_1_13();
    Listing_1_14();

    return a.exec();
}

