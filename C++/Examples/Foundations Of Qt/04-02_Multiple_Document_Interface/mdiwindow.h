#ifndef MDIWINDOW_H
#define MDIWINDOW_H

#include <QMainWindow>

class MdiWindow : public QMainWindow
{
    Q_OBJECT

public:
    MdiWindow(QWidget *parent = nullptr);
    ~MdiWindow();
};
#endif // MDIWINDOW_H
