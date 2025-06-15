#ifdef OFF
#include "DJViewControl.h"
#endif //OFF

#include <QApplication>
#include <iostream>

void Example_Observer_Pattern_Less_Coupled_Extended_Demo();

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

#ifdef OFF
    DJView w;
    w.show();
    return a.exec();
#endif //OFF
    
    Example_Observer_Pattern_Less_Coupled_Extended_Demo();
    return 0;
}

#include "Example_Observer_Pattern_Less_Coupled.h"
void Example_Observer_Pattern_Less_Coupled_Extended_Demo() {
    Demo();
}
