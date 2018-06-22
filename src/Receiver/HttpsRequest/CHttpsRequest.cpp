#include "CHttpsRequest.h"
#include <QNetworkRequest>
#include "AppSetting/CAppSetting.h"

CHttpsRequest::CHttpsRequest(QObject* parent /*= NULL*/):
	QObject(parent)
{
	m_pManager = new QNetworkAccessManager(this);
	//m_pRequest = new QNetworkRequest();
}

CHttpsRequest::~CHttpsRequest()
{
}

void CHttpsRequest::SendHttpsRequest(const QString& deviceID, const QString receiveUrl)
{
	const static QString defaultText = "uuid=%1,wallet_addr=%2";

	QString strText = defaultText.arg(deviceID, receiveUrl);
	QByteArray dataArray = strText.toUtf8();

	QNetworkRequest request;
	QSslConfiguration config = request.sslConfiguration();
	QList<QSslCertificate> certs = QSslCertificate::fromPath(CAppSetting::instance().GetCertCodePath());
	config.setCaCertificates(certs);
	request.setSslConfiguration(config);

	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
	request.setHeader(QNetworkRequest::ContentLengthHeader, dataArray.length());

	request.setUrl(QUrl(CAppSetting::instance().GetRequestUrl())); //发送的服务器IP地址

	QNetworkReply* pReply = m_pManager->post(request, dataArray);

	connect(pReply, SIGNAL(finished()), this, SLOT(SlotFinished()));
	connect(pReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(SlotError(QNetworkReply::NetworkError)));

}

void CHttpsRequest::SlotFinished()
{
	QNetworkReply *pReplay = qobject_cast<QNetworkReply*>(sender());
	// 保存接受的数据;
	QByteArray replyContent = pReplay->readAll();
	AnalyzeJson(QString::fromUtf8(replyContent));
}

void CHttpsRequest::SlotError(QNetworkReply::NetworkError error)
{
	QNetworkReply *pReplay = qobject_cast<QNetworkReply*>(sender());
	qDebug() << pReplay->errorString();
}

void CHttpsRequest::AnalyzeJson(const QString& text)
{
	//Fix 解析返回的Json字符串
}
