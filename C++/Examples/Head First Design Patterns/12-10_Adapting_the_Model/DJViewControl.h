#pragma once

#include <QMainWindow>
#include "./ui_djviewcontrol.h"
#include "ControllerInterface.h"
#include <QApplication>

#pragma region Implementing the View
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/combined/djview
public class DJView implements ActionListener,  BeatObserver, BPMObserver {
	BeatModelInterface model;
	ControllerInterface controller;
	JFrame viewFrame;
	JPanel viewPanel;
	BeatBar beatBar;
	JLabel bpmOutputLabel;
	JFrame controlFrame;
	JPanel controlPanel;
	JLabel bpmLabel;
	JTextField bpmTextField;
	JButton setBPMButton;
	JButton increaseBPMButton;
	JButton decreaseBPMButton;
	JMenuBar menuBar;
	JMenu menu;
	JMenuItem startMenuItem;
	JMenuItem stopMenuItem;

	public DJView(ControllerInterface controller, BeatModelInterface model) {
		this.controller = controller;
		this.model = model;
		model.registerObserver((BeatObserver)this);
		model.registerObserver((BPMObserver)this);
	}

	public void createView() {
		// Create all Swing components here
	}

	public void createControls() {
		// Create all Swing components here
	}

	public void enableStopMenuItem() {
		stopMenuItem.setEnabled(true);
	}

	public void disableStopMenuItem() {
		stopMenuItem.setEnabled(false);
	}

	public void enableStartMenuItem() {
		startMenuItem.setEnabled(true);
	}

	public void disableStartMenuItem() {
		startMenuItem.setEnabled(false);
	}

	public void actionPerformed(ActionEvent event) {
		if (event.getSource() == setBPMButton) {
			int bpm = Integer.parseInt(bpmTextField.getText());
			controller.setBPM(bpm);
		} else if (event.getSource() == increaseBPMButton) {
			controller.increaseBPM();
		} else if (event.getSource() == decreaseBPMButton) {
			controller.decreaseBPM();
		}
	}

	public void updateBPM() {
		if (model != null) {
			int bpm = model.getBPM();
			if (bpm == 0) {
				bpmOutputLabel.setText("offline");
			} else {
				bpmOutputLabel.setText("Current BPM: " + model.getBPM());
			}
		}
	}

	public void updateBeat() {
		beatBar.setValue(100);
	}
}
*/

QT_BEGIN_NAMESPACE
namespace Ui {
    class DJView;
}
QT_END_NAMESPACE

class DJViewControl : public QMainWindow {
    Q_OBJECT
    Ui::DJView *ui;
    ControllerInterface& controller;
public:
    DJViewControl(ControllerInterface& controller, QWidget *parent = nullptr) :
        QMainWindow(parent),
        ui(new Ui::DJView),
        controller(controller)
    {
        ui->setupUi(this);
        connect(ui->setBPMButton, &QPushButton::clicked, this, &DJViewControl::setBPM);
        connect(ui->increaseBPMButton, &QPushButton::clicked, this, &DJViewControl::increaseBPM);
        connect(ui->decreaseBPMButton, &QPushButton::clicked, this, &DJViewControl::decreaseBPM);
        connect(ui->actionStart, &QAction::triggered, this, &DJViewControl::start);
        connect(ui->actionStop, &QAction::triggered, this, &DJViewControl::stop);
        connect(ui->actionQuit, &QAction::triggered, this, &DJViewControl::quit);
        ui->actionStop->setEnabled(false);
    }

    ~DJViewControl() { delete ui; }
private slots:
    void setBPM() { controller.setBPM(ui->bpmTextField->text().toInt()); }
    void increaseBPM() { controller.increaseBPM(); }
    void decreaseBPM() { controller.decreaseBPM(); }

    void start() {
        controller.start();
        ui->actionStart->setEnabled(false);
        ui->actionStop->setEnabled(true);
    }

    void stop() {
        controller.stop();
        ui->actionStart->setEnabled(true);
        ui->actionStop->setEnabled(false);
    }

    void quit() { qApp->quit(); }
};
#pragma endregion //Implementing the View