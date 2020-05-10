#include "IVRFramework/eService.h"
#include <QSplashScreen>
#include <QPixmap>
#include "IVRFramework/eAppInfo.h"
#include "IVRFramework/frame_extension/eFrameExtensionManager.h"

using namespace IVRFramework;

eService* IVRFramework::eService::GetInstance()
{
	static eService globalService;
	return &globalService;
}

IVRFramework::eService::eService(void)
	:m_pMainWindow(nullptr)
	,m_pSplashScreen(nullptr)
	,m_pContentManager(nullptr)
{

}

IVRFramework::eService::~eService()
{

}

void IVRFramework::eService::StartApp()
{
	//创建启动界面
	QPixmap pixmap(eAppInfo::GetInstance()->GetWorkPath() + "Config/splash.png");
	m_pSplashScreen = new QSplashScreen(pixmap);
	m_pSplashScreen->show();
	
 	//优先加载主菜单
	eFrameExtensionManager::GetInstance()->LoadUIConfigs(eAppInfo::GetInstance()->GetWorkPath() + "Config/UIConfig");

//	//加载右键菜单配置
//	eRightMenuManager::GetInstance()->LoadXmlFile(eAppInfo::GetInstance()->GetWorkPath() + "Config/RightMenuConfig.xml");
//
//	//加载插件配置文件中的插件
//#ifdef NDEBUG
//	QString pluginConfigFile(eAppInfo::GetInstance()->GetWorkPath() + "Config/Plugin.xml");
//#else
//	QString pluginConfigFile(eAppInfo::GetInstance()->GetWorkPath() + "Config/Plugind.xml");
//#endif
//	ePluginManager::GetInstance()->LoadPlugins(eAppInfo::GetInstance()->GetWorkPath(), pluginConfigFile);
//
//	//初始化日志机制
//	eLog::GetInstance()->Init(eAppInfo::GetInstance()->GetAppPath());
}

void IVRFramework::eService::EndApp()
{
	//释放资源
	delete eService::GetInstance()->m_pMainWindow;
	eService::GetInstance()->m_pMainWindow = NULL;
}
