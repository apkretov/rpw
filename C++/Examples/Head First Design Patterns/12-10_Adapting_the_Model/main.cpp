#include <QApplication>
#include <QScreen>
#include "HeartModel.h"
#include "HeartController.h"
#include "HeartAdapter.h"
#include "DJViewView.h"
#include "DJViewControl.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    HeartModel heartModel;
    HeartController heartController(heartModel);
    HeartAdapter heartAdapter(heartModel);

    DJViewView view(heartAdapter);
    view.show();

    DJViewControl control(heartController);
    control.show();

    // Place the windows in the middle of the screen
    const QRect availableGeometry = view.screen()->availableGeometry();
    int x = (availableGeometry.width() - view.width() - control.width()) / 2;
    int y = (availableGeometry.height() - view.height()) / 2;
    view.move(x, y);
    control.move(x + view.width() + 20, y);

    return a.exec();
}
