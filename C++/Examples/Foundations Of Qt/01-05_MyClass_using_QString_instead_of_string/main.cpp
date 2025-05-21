#include <QDebug>
#include "../stdafx.h"
#include "MyClass.h"

#pragma region Listing 1-6. A trivial example
int main( ) {
    print_file_line(); //MINE
    qDebug() << "Hello Qt World!";
    return 0;
}
#pragma endregion //Listing 1-6. A trivial example
