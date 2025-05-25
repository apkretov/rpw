#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
#ifdef VER_1
    QLabel *label = new QLabel("Hello, Qt!");
#else //Figure 1.2.
    QLabel *label = new QLabel("<h2><i>Hello</i> " "<font color=red>Qt!</font></h2>");
#endif //Figure 1.2
    label->show();
    return app.exec();
}
