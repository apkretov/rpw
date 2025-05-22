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

    qDebug("\n");
    QList<int>::const_iterator stlIter; //STL-style.
    for(stlIter = list.begin(); stlIter != list.end(); ++stlIter)
        qDebug() << (*stlIter);
}

void Listing_1_15() { //Listing 1-15. Modifying lists using iterators
    QList<int> list;
    list << 27 << 33 << 61 << 62;

    QMutableListIterator<int> javaIter(list); //Java-style iterator
    while(javaIter.hasNext()) {
        int value = javaIter.next() + 1;
        javaIter.setValue( value );
        qDebug() << value;
    }

    qDebug("\n");
    QList<int>::Iterator stlIter; //STL-style iterator
    for(stlIter = list.begin(); stlIter != list.end(); ++stlIter) {
        (*stlIter) = (*stlIter) * 2;
        qDebug() << (*stlIter);
    }
}

int main(int argc, char *argv[]) {  
    Listing_1_13();
    qDebug("\n");
    Listing_1_14();
    qDebug("\n");
    Listing_1_15();

    return 0;
}

