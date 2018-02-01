#include "VoroDrone.h"
#include <QtWidgets/QApplication>
#include <QtPlugin>
#include <string>

using namespace std;

Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin);

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	VoroDrone w;
	w.show();
	return a.exec();
}
