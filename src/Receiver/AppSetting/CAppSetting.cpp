#include "AppSetting/CAppSetting.h"

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
		m_certCodePath = m_homePath + "api.myrtb.net.crt";
	}
	return m_certCodePath;
}

CAppSetting::CAppSetting(void):
	m_certCodePath("")
{
	m_homePath = qApp->applicationDirPath()+ "/";
}

