#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Receiver.h"
#include <QTimer>
#include "CHttpsRequest.h"

class Receiver : public QMainWindow
{
	Q_OBJECT

public:
	Receiver(QWidget *parent = Q_NULLPTR);
	~Receiver();
private:
	void CheckDeviceConnect();
private slots:
	void SlotCheckTimeout();
	void on_btnBind_clicked();
	void on_btnOk_clicked();
	void on_btnCancel_clicked();
private:
	Ui::ReceiverClass ui;
	QTimer* m_pTimer;
	QString m_deviceID;
	CHttpsRequest* m_pHttpsRequest;
};
