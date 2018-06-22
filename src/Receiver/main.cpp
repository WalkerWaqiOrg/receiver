#include "Receiver.h"
#include <QtWidgets/QApplication>
#include "qtsingleapplication/QtSingleApplication"
#include <QTextCodec>
#include <QFile>
#include <QDir>
#include "Log4Qt/LogManager"
#include "Log4Qt/propertyconfigurator.h"
#include "Log4Qt/helpers/properties.h"
#include "AppSetting/CAppSetting.h"

int main(int argc, char *argv[])
{
	int returnVal = -1;
	try {
		const QString APP_ID = "ANTIY_EMERGENCY_TOOLBOX_MUTEX";
		QtSingleApplication a(APP_ID, argc, argv);
		if (a.isRunning()) {
			a.sendMessage("Wake up!");
			return 0;
		}

		//产品UI日志
		Log4Qt::Properties qtlogProper;
		qtlogProper.setProperty("log4j.rootLogger", "DEBUG, A1");
		qtlogProper.setProperty("log4j.appender.A1", "org.apache.log4j.FileAppender");
		qtlogProper.setProperty("log4j.appender.A1.file", CAppSetting::instance().GetUILogPath());
		qtlogProper.setProperty("log4j.appender.A1.layout", "org.apache.log4j.TTCCLayout");
		qtlogProper.setProperty("log4j.appender.A1.layout.DateFormat", "{yyyy-MM-dd HH:mm:ss}");
		Log4Qt::PropertyConfigurator::configure(qtlogProper);
		Log4Qt::LogManager::setHandleQtMessages(true);

		//加载样式表
		QString skinPath = CAppSetting::instance().GetSkinPath();
		QString skinCssPath = skinPath + "skin.css";
		QFile file(skinCssPath);
		if (!file.open(QIODevice::ReadOnly)) {
			//Q_ASSERT(false);
		}
		QString styleSheet = file.readAll();
		QString absolutePath = QDir(skinPath).absolutePath();
		styleSheet.replace("%skinpath%", absolutePath, Qt::CaseInsensitive);
		a.setStyleSheet(styleSheet);
		file.close();

		Receiver w;
		a.setActivationWindow(&w);
		w.show();
		returnVal = a.exec();
	}catch (int e) {
		returnVal = e;
	}catch (...) {
	}
	return returnVal;
}
