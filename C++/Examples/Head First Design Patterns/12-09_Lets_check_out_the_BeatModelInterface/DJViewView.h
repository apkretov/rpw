#pragma once

#include <QWidget>
#include "ui_djviewview.h"
#include "ObserverBPM.h"
#include "ObserverBeat.h"
#include "BeatModelInterface.h"

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

namespace Ui {
    class DJViewView;
}

class DJViewView : public QWidget, public BeatObserver, public BPMObserver {
    Q_OBJECT
    Ui::DJViewView *ui;
    BeatModelInterface& model;
public:
    explicit DJViewView(BeatModelInterface& model, QWidget *parent = nullptr) : QWidget(parent), ui(new Ui::DJViewView), model(model) {
        ui->setupUi(this);
        model.registerObserver(static_cast<BPMObserver*>(this));
        model.registerObserver(static_cast<BeatObserver*>(this));
    }

    ~DJViewView() {
        model.removeObserver(static_cast<BeatObserver *>(this));
        model.removeObserver(static_cast<BPMObserver *>(this));
        delete ui;
    }
public slots:
    void updateBPM() override { 
        if (model.getBPM() == 0)
            ui->bpmOutputLabel->setText("offline");
        else
            ui->bpmOutputLabel->setText(QString::number(model.getBPM())); 
    }

    void updateBeat() override { ui->beatBar->setValue(100); }
};
#pragma endregion //Implementing the View
