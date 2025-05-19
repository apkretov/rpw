#include "widget.h"

#include <QApplication>
#include "BeatModel.h"
#include "ControllerBeat.h"

/* Java
public class DJTestDrive {
    public static void main (String[] args) {
        BeatModelInterface model = new BeatModel();
        ControllerInterface controller = new BeatController(model);
    }
}
*/
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Widget w;
    w.show();

    BeatModel beatModel;
    BeatController beatController{beatModel};

    return a.exec();
}
