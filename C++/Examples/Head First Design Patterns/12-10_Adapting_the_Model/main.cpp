#include <QApplication>
#include "HeartModel.h"
#include "HeartController.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    HeartModel heartModel;
    ControllerInterface* model = new HeartController(heartModel);

    return a.exec();
}
