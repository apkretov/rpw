#include <QApplication>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include "MyClass.h"

#pragma region Listing 1-10. Creating an application, widgets, layout, and a MyClass object
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget widget;
    QLineEdit *lineEdit = new QLineEdit;
    QLabel *label = new QLabel;

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(lineEdit);
    layout->addWidget(label);
    widget.setLayout(layout);

    MyClass *bridge = new MyClass("", &app);

#pragma region Listing 1-11. Setting up the connections
    QObject::connect(lineEdit, SIGNAL(textChanged(const QString&)), bridge, SLOT(setText(const QString&)));
    QObject::connect(bridge, SIGNAL(textChanged(const QString&)), label, SLOT(setText(const QString&)));
#pragma endregion //Listing 1-11. Setting up the connections

    return app.exec(); //QT
}
#pragma endregion //Listing 1-10. Creating an application, widgets, layout, and a MyClass object
