#include "widget.h" // Qt C++ Crash Course | Beginner to Advanced (GUI Development & Applications) - YouTube @ https://youtu.be/nyS7X9vsNHs?si=EiGJpO0FklA2NTSz
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
