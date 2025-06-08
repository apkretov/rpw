#include "mydialog.h"
#include <QGridLayout>
#include <QPushButton>

MyDialog::MyDialog(QWidget *parent) : QDialog(parent) { // Push buttons are by default Fixed in vertical direction. If we wanted to adjust sizing policies, we would use QSizePolicy.
#pragma region Listing 3-4. The grid layout is populated.
#ifdef ORIG
    QGridLayout layout(this); //ORIG QGridLayout layout(&widget);
    layout.addWidget(new QPushButton("foo"), 0, 0, 1, 2);
    layout.addWidget(new QPushButton("bar"), 1, 0);
    layout.addWidget(new QPushButton("baz"), 1, 1);
#else //NOTEBOOKLM
    QGridLayout *gridLayout = new QGridLayout(this); // Create a QGridLayout instance and set it as the top-level layout for the dialog. As per Listing 3-4, the layout is initialized with a parent (here, 'this' QDialog).
    gridLayout->addWidget(new QPushButton("foo"), 0, 0, 1, 2); // Add widgets to the grid layout as specified in Listing 3-4. layout.addWidget( new QPushButton( "foo" ), 0, 0, 1, 2 ); This button is placed at row 0, column 0, and spans 1 row and 2 columns.
    gridLayout->addWidget(new QPushButton("bar"), 1, 0); // layout.addWidget( new QPushButton( "bar" ), 1, 0 ); This button is placed at row 1, column 0.
    gridLayout->addWidget(new QPushButton("baz"), 1, 1); // layout.addWidget( new QPushButton( "baz" ), 1, 1 ); // This button is placed at row 1, column 1.
#endif //NOTEBOOKLM
#pragma endregion //Listing 3-4. The grid layout is populated.

    setWindowTitle("Qt Listing 3-4 Example (CMake)");
}

