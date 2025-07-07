#include <QApplication>
#include <QScreen>
#include "BeatModel.h"
#include "ControllerBeat.h"
#include "DJViewControl.h"
#include "DJViewView.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    BeatModel beatModel;
    beatModel.initialize(); //TO DO: Create a BeatModel constructor and call initialize() there.
    BeatController beatController(beatModel);

    DJViewView view(beatModel);
    view.show();

    DJViewControl control(beatController);
    control.show();

    const QRect availableGeometry = view.screen()->availableGeometry(); // Place the windows in the middle of the screen
    int x = (availableGeometry.width() - view.width() - control.width()) / 2;
    int y = (availableGeometry.height() - view.height()) / 2;
    view.move(x, y);
    control.move(x + view.width() + 20, y);

    return a.exec();
}
