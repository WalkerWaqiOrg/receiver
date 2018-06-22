#ifndef UTILITY_H
#define UTILITY_H
#include <QSysInfo>
#include <QString>

bool IsWindowsXp()
{
#ifdef Q_OS_WIN
	QSysInfo::WinVersion wv = QSysInfo::windowsVersion();
	if (QSysInfo::WV_5_1 == wv || QSysInfo::WV_5_2 == wv)
		return true;
#endif
	return false;
}

QString include_path_backslash(const QString& path)
{
#ifdef WIN32
	const char backslash_str[] = "\\";
#else
	const char backslash_str[] = "/";
#endif
	QString r = path;
	uint32_t len = (uint32_t)r.length();
	if (len < 0 || (!r.endsWith('/')&& !r.endsWith('\\'))) {
		r += backslash_str;
	}
	return r;
}

#endif //UTILITY_H
