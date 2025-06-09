#pragma once

#include <QTextEdit>

class QCloseEvent;

#pragma region Listing 4-6. Document widget class for the MDI application
class DocumentWindow : public QTextEdit {
    Q_OBJECT
public:
    DocumentWindow(QWidget *parent = 0);
protected:
    void closeEvent(QCloseEvent *event);
    bool isSafeToClose();
};
#pragma endregion //Listing 4-6. Document widget class for the MDI application
