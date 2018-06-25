#include "AppSetting/CAppSetting.h"
#include <QProcessEnvironment>
#include <QStandardPaths>
#include "AppSetting/utility.h"
#include <QDir>

CAppSetting& CAppSetting::instance()
{
	static CAppSetting setting;
	return setting;
}

CAppSetting::~CAppSetting(void)
{
}

const QString& CAppSetting::GetCertCodePath()
{
	if (m_certCodePath.isEmpty()) {
		m_certCodePath = ":/Receiver/api.myrtb.net.crt";
	}
	return m_certCodePath;
}

const QString& CAppSetting::GetRequestUrl()
{
	if (m_requestUrl.isEmpty()){
		m_requestUrl = "https://api2.myrtb.net/client/bind/wallet";
	}
	return m_requestUrl;
}

const QString& CAppSetting::GetConfirmUrl()
{
	if (m_confirmUrl.isEmpty()) {
		m_confirmUrl = "https://api2.myrtb.net/client/bind/confirm";
	}
	return m_confirmUrl;
}

const QString& CAppSetting::GetUILogPath()
{
	//Fix Mac下不能再程序目录创建日志文件
	if (m_logPath.isEmpty()){
		m_logPath = m_appdataPath + "log.log";
	}
	return m_logPath;
}

const QString& CAppSetting::GetSkinPath()
{
	if (m_skinPath.isEmpty()){
		m_skinPath = m_homePath + "skin/";
	}
	return m_skinPath;
}

CAppSetting::CAppSetting(void):
	m_certCodePath(""), m_confirmUrl("")
{
	m_homePath = qApp->applicationDirPath()+ "/";
	DetectAppDataPath();
}

void CAppSetting::DetectAppDataPath()
{
#ifdef Q_OS_MAC
	m_appdataPath = QProcessEnvironment::systemEnvironment().value("HOME");
	m_appdataPath = include_path_backslash(m_appdataPath) + "Library/Application Support/";
#else
	m_appdataPath = QProcessEnvironment::systemEnvironment().value("APPDATA");
	m_appdataPath = include_path_backslash(m_appdataPath);
	if (m_appdataPath.isEmpty() || m_appdataPath == "/") {
		QStringList strList = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
		if (strList.size() > 0){
			m_appdataPath = strList[0];
			m_appdataPath += IsWindowsXp() ? "/Application Data/" : "/AppData/Roaming/";
		}
	}
#endif
	m_appdataPath += "RRCMoneyShield/";
	QDir dir(m_appdataPath);
	if (!dir.exists()) {
		dir.mkpath(m_appdataPath);
	}
}

