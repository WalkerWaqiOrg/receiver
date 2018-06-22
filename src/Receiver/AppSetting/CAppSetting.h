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
	const QString& GetUILogPath();
	const QString& GetSkinPath();
private:
	CAppSetting(void);
	void DetectAppDataPath();
private:
	QString m_homePath;
	QString m_certCodePath;
	QString m_requestUrl;
	QString m_confirmUrl;
	QString m_logPath;
	QString m_skinPath;
	QString m_appdataPath;
};
