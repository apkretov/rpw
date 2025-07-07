#include <QApplication>
#include "BeatModel.h"
#include "ControllerBeat.h"
#include "DJViewControl.h"
#include "DJViewView.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    BeatModel beatModel;
    beatModel.initialize(); //TO DO: Create a BeatModel constructor and call initialize() there.
    ControllerBeat beatController{beatModel};

    DJViewView view{beatModel};
    view.show();

    DJViewControl control(beatController);
    control.show();

    view.move(0, 0);
    control.move(view.width(), 0);

    return a.exec();
}
