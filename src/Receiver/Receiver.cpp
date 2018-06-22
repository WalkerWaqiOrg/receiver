#include "Receiver.h"
#include "bdapi.h"
#include "AppSetting/CAppSetting.h"

Receiver::Receiver(QWidget *parent)
	: QMainWindow(parent),m_pTimer(NULL), 
	m_pHttpsRequest(NULL)
{
	ui.setupUi(this);
	CheckDeviceConnect();
}

Receiver::~Receiver()
{
	if (m_pTimer != NULL && m_pTimer->isActive()) {
		m_pTimer->stop();
	}
}

void Receiver::CheckDeviceConnect()
{
	if (NULL == m_pTimer){
		m_pTimer = new QTimer(this);
		connect(m_pTimer, SIGNAL(timeout()), this, SLOT(SlotCheckTimeout()));
	}
	m_pTimer->start(100);
}

void Receiver::SlotCheckTimeout()
{
	if (bd_find_device() <= 0){
		return;
	}
	m_pTimer->stop();

	BDDEV pBapi = NULL;
	for (int i = 0; i < bd_find_device(); i++){
		pBapi = bd_connect(i);
		if (NULL != pBapi){
			break;
		}
	}
	if (NULL == pBapi){
		m_pTimer->start(100);
		return;
	}
	BYTE sn[16];
	bd_get_sn(pBapi, sn);
	m_deviceID = QString::fromLatin1((const char*)sn);
	bd_close(&pBapi);
	ui.stackedWidget->setCurrentWidget(ui.page_2);
	ui.label_3->setText(m_deviceID);
}

void Receiver::on_btnBind_clicked()
{
	if (NULL == m_pHttpsRequest){
		m_pHttpsRequest = new CHttpsRequest(this);
	}
	m_deviceID = "111";
	m_pHttpsRequest->SendHttpsRequest(CAppSetting::instance().GetRequestUrl(), m_deviceID, ui.lineEdit->text());
	ui.stackedWidget->setCurrentWidget(ui.page_2);
}

void Receiver::on_btnOk_clicked()
{
	if (NULL == m_pHttpsRequest) {
		m_pHttpsRequest = new CHttpsRequest(this);
	}
	m_deviceID = "111";
	m_pHttpsRequest->SendHttpsRequest(CAppSetting::instance().GetConfirmUrl(), m_deviceID, ui.lineEdit->text());
}

void Receiver::on_btnCancel_clicked()
{
	//返回到上一个界面 重新输入
}
