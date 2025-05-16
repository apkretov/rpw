#include <QDebug>
#include "./ui_widget.h"
#include "stdafx.h"
#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);

    Rnd rnd(1, 10); // Generate (1-10).
    secret_number = rnd();

    ui->startOverButton->setDisabled(true); // Disable the Start Over button.
    ui->messageLable->setText("");
}

Widget::~Widget() { delete ui; }

void Widget::on_guessButton_clicked() {
    guess_number = ui->numberSpinbox->value();

    if (guess_number == secret_number) { // Check if the guessed right.
        ui->messageLable->setText("Congratulations, the number is " + QString::number(guess_number) + "!");
        ui->guessButton->setDisabled(true); // Button housekeeping.
        ui->startOverButton->setDisabled(false);
    } else {
        if (secret_number < guess_number)
            ui->messageLable->setText("Number is lower than that");
        else if (secret_number > guess_number)
            ui->messageLable->setText("Number is higher than that");
    }
}

void Widget::on_startOverButton_clicked() { 
	ui->guessButton->setDisabled(false); // Enable the Guess button.
	ui->startOverButton->setDisabled(true); // Disable the Start Over button.
	ui->numberSpinbox->setValue(1); // Reset the spinbox to 1.

	Rnd rnd(1, 10); // Regenerate the random number.
	secret_number = rnd();

    ui->messageLable->setText(""); // Clear the message label.
}

