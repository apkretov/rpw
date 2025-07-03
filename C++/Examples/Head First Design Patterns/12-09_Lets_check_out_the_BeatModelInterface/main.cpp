#include <QApplication>
#include "BeatModel.h"
#include "ControllerBeat.h"
#include "DJViewControl.h"
#include "DJViewView.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    BeatModel beatModel;
    ControllerBeat controller(beatModel);

    DJViewControl control(controller);
    control.show();

    DJViewView view(beatModel);
    view.show();

    return a.exec();
}
