#include "../stdafx.h"
#include "MyClass.h"

#pragma region Listing 1-3. Dynamic memory without Qt
int main() {
    print_file_line(); //MINE

    MyClass *a, *b, *c;
    a = new MyClass( "foo" );
    b = new MyClass( "ba-a-ar" );
    c = new MyClass( "baz" );

    std::cout << a->text() << " (" << a->getLengthOfText() << ")" << std::endl;
    a->setText( b->text() );
    std::cout << a->text() << " (" << a->getLengthOfText() << ")" << std::endl;

    int result = a->getLengthOfText() - c->getLengthOfText();

    delete a;
    delete b;
    delete c;

    return result;
}
#pragma endregion //Listing 1-3. Dynamic memory without Qt
