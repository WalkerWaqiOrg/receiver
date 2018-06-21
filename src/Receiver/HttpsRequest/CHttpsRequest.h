#pragma once

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class CHttpsRequest :public QObject
{
	Q_OBJECT
public:
	CHttpsRequest(QObject* parent = NULL);
	~CHttpsRequest();
public:
	void SendHttpsRequest(const QString& deviceID, const QString receiveUrl);
private slots:
	void SlotFinished();
	void SlotError(QNetworkReply::NetworkError error);
private:
	void AnalyzeJson(const QString& text);
private:
	QNetworkAccessManager* m_pManager;
};
