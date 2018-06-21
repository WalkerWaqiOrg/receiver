#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Receiver.h"

class Receiver : public QMainWindow
{
	Q_OBJECT

public:
	Receiver(QWidget *parent = Q_NULLPTR);

private:
	Ui::ReceiverClass ui;
};
