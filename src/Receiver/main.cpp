#include "Receiver.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Receiver w;
	w.show();
	return a.exec();
}
