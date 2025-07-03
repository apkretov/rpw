#include <QApplication>
#include "BeatModel.h"
#include "ControllerBeat.h"
#include "DJViewControl.h"
#include "DJViewView.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    BeatModel beatModel;
    BeatController beatController{beatModel};

    DJViewView view{beatModel};
    view.show();

    DJViewControl control{beatController};
    control.show();

    return a.exec();
}
