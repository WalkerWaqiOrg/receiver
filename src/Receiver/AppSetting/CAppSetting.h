#pragma once
#include <QString>
#include <QCoreApplication>

class CAppSetting
{
public:
public:
	static CAppSetting& instance();
	~CAppSetting(void);
public:
	const QString& GetCertCodePath();
	const QString& GetRequestUrl();
	const QString& GetConfirmUrl();
private:
	CAppSetting(void);
private:
	QString m_homePath;
	QString m_certCodePath;
	QString m_requestUrl;
	QString m_confirmUrl;
};
