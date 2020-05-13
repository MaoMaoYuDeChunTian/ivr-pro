#include "IVRTestPlugin/IVRTestPlugin.h"
#include <QDockWidget>
#include <QObject>
#include "IVRFramework/eService.h"
#include "IVRFramework/base_widget/eMainWindow.h"

#include "testCommand.h"

using namespace IVRFramework;
using namespace IVRTest;

eIPlugin* CreatePluginInstance()
{
	return new IVRTestPlugin();
}

IVRTestPlugin::IVRTestPlugin()
{
}

IVRTest::IVRTestPlugin::~IVRTestPlugin()
{

}

bool IVRTest::IVRTestPlugin::Load()
{
	QDockWidget* pLayerDock = new QDockWidget();
	pLayerDock->setWindowTitle(QObject::tr("test dock"));
	eService::GetInstance()->m_pMainWindow->addDockWidget(Qt::RightDockWidgetArea, pLayerDock);

	return true;
}

void IVRTest::IVRTestPlugin::RegisterCommands()
{
	AddCommand(new TestCommand());
}

eIFrameExtension* IVRTest::IVRTestPlugin::LoadFrameExtemsion()
{
	return nullptr;
}

void IVRTest::IVRTestPlugin::HandleEvent(int nEventType, void* pEventData)
{

}

