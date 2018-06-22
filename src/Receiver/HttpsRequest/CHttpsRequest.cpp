#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkRequest>
#include "CHttpsRequest.h"
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

void CHttpsRequest::SendHttpsRequest(const QString& url, const QString& deviceID, const QString receiveUrl)
{
	const static QString defaultText = "uuid=%1&wallet_addr=%2";

	QString strText = defaultText.arg(deviceID, receiveUrl);
	QByteArray dataArray = strText.toUtf8();

	QNetworkRequest request;
	//Fix 设置证书目前设置证书不能访问
	//QSslConfiguration config = request.sslConfiguration();
	//QList<QSslCertificate> certs = QSslCertificate::fromPath(CAppSetting::instance().GetCertCodePath());
	//config.setCaCertificates(certs);
	//request.setSslConfiguration(config);

	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
	request.setHeader(QNetworkRequest::ContentLengthHeader, dataArray.length());

	request.setUrl(QUrl(url)); //发送的服务器IP地址

	QNetworkReply* pReply = m_pManager->post(request, dataArray);

	connect(pReply, SIGNAL(finished()), this, SLOT(SlotFinished()));
	connect(pReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(SlotError(QNetworkReply::NetworkError)));

}

void CHttpsRequest::SlotFinished()
{
	QNetworkReply *pReplay = qobject_cast<QNetworkReply*>(sender());
	// 保存接受的数据;
	QByteArray replyContent = pReplay->readAll();
	QString sss = replyContent;
	AnalyzeJson(QString::fromUtf8(replyContent));
	emit SignalRequestFinished();
}

void CHttpsRequest::SlotError(QNetworkReply::NetworkError error)
{
	QNetworkReply *pReplay = qobject_cast<QNetworkReply*>(sender());
	qDebug() << pReplay->errorString();
}

void CHttpsRequest::AnalyzeJson(const QString& text)
{
	QJsonParseError jsonError;
	QJsonDocument json = QJsonDocument::fromJson(text.toUtf8().data(), &jsonError);
	if (jsonError.error == QJsonParseError::NoError){
		if (json.isObject()){
			QJsonObject rootObj = json.object();

			QString code;
			int codeNum;
			if (rootObj.contains("code")){
				QJsonValue value = rootObj.value("code");
				codeNum = value.toInt();
			}

			QString msg;
			QString msgText;
			if (rootObj.contains("msg")){
				QJsonValue value = rootObj.value("msg");
				if (value.isString()){
					msgText = value.toString();
				}
			}

			if (rootObj.contains("data")){
				QJsonValue valueArray = rootObj.value("data");
				if (valueArray.isObject()){
					//Fix 解析data段数据
					int i = 0;
				}
			}
		}
	}
}
