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

    BeatModel beatModel;
    BeatController beatController{beatModel};

    Widget w;
    w.show();
    return a.exec();
}
