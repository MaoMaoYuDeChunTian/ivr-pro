#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include "IVRFramework/eStyle.h"
#include "IVRFramework/eService.h"

using namespace IVRFramework;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//style setting
	a.setStyle(new IVRFramework::eStyle);

	MainWindow _w;

	eService::GetInstance()->StartApp();

	_w.show();
	return a.exec();
}
