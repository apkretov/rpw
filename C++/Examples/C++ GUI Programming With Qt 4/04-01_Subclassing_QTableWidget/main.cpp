#pragma region Splash Screens

#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

#ifdef OFF
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/images/splash.png"));
    splash->show();

    Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
    splash->showMessage(QObject::tr("Setting up the main window..."), topRight, Qt::white);
#endif //OFF

    MainWindow mainWin;

#ifdef OFF
    splash->showMessage(QObject::tr("Loading modules..."), topRight, Qt::white);
    loadModules();

    splash->showMessage(QObject::tr("Establishing connections..."), topRight, Qt::white);

    establishConnections();
#endif //OFF

    mainWin.show();
#ifdef OFF
    splash->finish(&mainWin);
    delete splash;
#endif //OFF

    return app.exec();
}
#pragma endregion //Splash Screens
