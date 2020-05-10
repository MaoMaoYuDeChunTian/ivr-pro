#include "IVRFramework/command/ePluginManager.h"
#include "IVRFramework/command/eIPlugin.h"
#include "IVRFramework/command/eCommandManager.h"
#include "IVRFramework/frame_extension/eFrameExtensionManager.h"
#include "IVRUtility/eCommonUtil.h"
#include <QLibrary>
#include <QFile>
#include <QFileInfo>
#include <QDomComment>
#include <QMessageBox>

using namespace IVRUtility;
using namespace IVRFramework;

ePluginManager* ePluginManager::GetInstance()
{
	static ePluginManager s_PluginManager;
	return &s_PluginManager;
}

ePluginManager::ePluginManager(void)
{
	m_pCallbackLoadPlugin = NULL;
}

ePluginManager::~ePluginManager(void)
{
	QMap<QString, eIPlugin*>::iterator itr = m_listPlugins.begin();
	while (itr != m_listPlugins.end())
	{
		if (itr.value() != NULL)
		{
			delete itr.value();
			itr.value() = NULL;
		}
		itr++;
	}
	m_listPlugins.clear();

	QList<QLibrary *> lstLibs;
	lstLibs.swap(m_lstLibs);
	for (int i = lstLibs.size() - 1; i >= 0; --i)
	{
		QLibrary *pLib = lstLibs.at(i);
		//pLib->unload();
		delete pLib;
	}
}

bool ePluginManager::LoadPlugins(QString workPath, QString pluginConfigFile)
{
	if (pluginConfigFile.isEmpty())
	{
		return false;
	}

	QDomDocument document;
	QDomElement dRoot;
	QFile* pFile = eCommonUtil::OpenXml(pluginConfigFile, document, dRoot);
	if (pFile == NULL)
	{
		return false;
	}
	QString messgeInfo;
	int nFailCount = 0;
	QDomElement commonPluginsNode = dRoot.firstChildElement("CommonPlugins");
	QDomNodeList pluginElements = commonPluginsNode.elementsByTagName("Plugin");
	for (int i = 0; i < pluginElements.count(); i++)
	{
		QDomElement pluginEle = pluginElements.at(i).toElement();

		QString strIsActive = pluginEle.attribute("IsActive");
		if (strIsActive.toLower() == "false" || strIsActive == "0")
		{
			continue;
		}
		QString dllFileName = pluginEle.attribute("Path");
		QString dllFilePath = workPath + dllFileName;

		//QString uiConfigFileName = pluginEle.attribute("UIConfig");
		//QString uiConfigFilePath = workPath + "Config/UIConfig/" + uiConfigFileName;

		int nReturnCode = LoadPlugin(dllFilePath);
		if (nReturnCode != 0)
		{
			QFile pFile(dllFilePath);
			//messgeInfo += pFile.fileName() + eStringUtil::CStr2QStr("锟斤拷锟斤拷锟斤拷锟轿?") + QString::number(nReturnCode) + "\n";
			++nFailCount;
		}
	}
	if (nFailCount > 0)
	{
		QMessageBox msgBox;
		//msgBox.setWindowTitle(eStringUtil::CStr2QStr("锟斤拷锟斤拷"));
		//msgBox.setText(messgeInfo + eStringUtil::CStr2QStr("锟斤拷锟斤拷失锟斤拷"));
		msgBox.exec();
	}

	if (pFile)
	{
		pFile->close();
		delete pFile;
	}

	LoadFrameExtensions();

	QMap<QString, eIPlugin*>::iterator itr = m_listPlugins.begin();
	while (itr != m_listPlugins.end())
	{
		if (itr.value() != NULL)
		{
			itr.value()->AfterLoad();
		}
		itr++;
	}
	return true;
}

int ePluginManager::LoadPlugin(const QString & dllFilePath)
{
	QFileInfo fileInfo(dllFilePath);
	QString absoluteFilePath = fileInfo.absoluteFilePath();

	int nErrorCode = -1;
	do
	{
		if (!FileExist(absoluteFilePath))
		{
			nErrorCode = 1;
			break;
		}
		if (IsLoaded(absoluteFilePath))
		{
			nErrorCode = 0;
			break;
		}

		QLibrary *pLib = new QLibrary(absoluteFilePath);
		if (!pLib->load())
		{
			nErrorCode = 2;
			delete pLib;
			break;
		}

		bool bHasPlugin = LoadPlugin(pLib);
		if (bHasPlugin)
		{
			nErrorCode = 0;
		}
		else
		{
			nErrorCode = 3;
		}
		m_lstLibs.append(pLib);
	} while (false);
	return nErrorCode;
}

bool ePluginManager::LoadFrameExtensions()
{
	QMap<QString, eIPlugin*>::iterator itr = m_listPlugins.begin();
	while (itr != m_listPlugins.end())
	{
		if (itr.value() != NULL)
		{
			eIPlugin* pPlugin = itr.value();
			eIFrameExtension* pFrameExtension = pPlugin->LoadFrameExtension();
			if (pFrameExtension != NULL)
			{
				bool bSuccess = eFrameExtensionManager::GetInstance()->AddFrameExtension(pFrameExtension);
				if (bSuccess)
				{
					pFrameExtension->CreateFrame();
				}
				else
				{
					delete pFrameExtension;
					pFrameExtension = NULL;
				}
			}
		}
		itr++;
	}
	return true;
}

bool ePluginManager::UnLoadPlugins()
{
	QMap<QString, eIPlugin*>::iterator itr = m_listPlugins.begin();
	while (itr != m_listPlugins.end())
	{
		if (itr.value() != NULL)
		{
			itr.value()->BeforeUnLoad();
		}
		itr++;
	}

	itr = m_listPlugins.begin();
	while (itr != m_listPlugins.end())
	{
		if (itr.value() != NULL)
		{
			itr.value()->UnLoad();
		}
		itr++;
	}

	return true;
}

bool ePluginManager::UnLoadPlugin(eIPlugin* pPlugin)
{
	if (pPlugin == NULL)
	{
		return false;
	}
	QMap<QString, eIPlugin*>::iterator itr = m_listPlugins.find(pPlugin->Get_ClassName());
	if (itr != m_listPlugins.end())
	{
		itr.value()->BeforeUnLoad();
		itr.value()->UnLoad();
		delete itr.value();
		itr.value() = NULL;
		m_listPlugins.erase(itr);
		return true;
	}
	return false;
}

bool ePluginManager::FileExist(const QString& dllFilePath) const
{
	bool isExist = QFile::exists(dllFilePath);
	return isExist;
}

bool ePluginManager::IsLoaded(const QString & dllFilePath) const
{
	for (int i = 0; i < m_lstLibs.size(); ++i)
	{
		QLibrary *pLib = m_lstLibs.at(i);
		if (dllFilePath == pLib->fileName())
		{
			return true;
		}
	}
	return false;
}

bool ePluginManager::LoadPlugin(QLibrary *pLib)
{
	bool bRet = false;
	do
	{
#ifdef WIN32
		typedef eIPlugin *(__stdcall CreatePluginInstance)();
#else
		typedef eIPlugin *(__attribute__((stdcall)) CreatePluginInstance)();
#endif
		CreatePluginInstance *pFun = NULL;
		pFun = (CreatePluginInstance *)pLib->resolve("CreatePluginInstance");
		if (NULL == pFun)
		{
			break;
		}
		eIPlugin *pPlugin = pFun();
		if (NULL == pPlugin)
		{
			break;
		}
		pPlugin->Load();
		eCommandManager::GetInstance()->AddCommandSet(pPlugin);
		m_listPlugins[pPlugin->Get_ClassName()] = pPlugin;

		if (m_pCallbackLoadPlugin != NULL)
		{
			m_pCallbackLoadPlugin(pPlugin);
		}
		bRet = true;
	} while (false);
	return bRet;
}

void ePluginManager::SetLoadPluginCallBack(Callback_LoadPlugin pCallbackLoadPlugin)
{
	m_pCallbackLoadPlugin = pCallbackLoadPlugin;
}

void ePluginManager::AddListener(int nEventType, eIPlugin* pPlugin)
{
	ePluginManager::ListenerGroup::iterator itMap = m_listeners.find(nEventType);
	if (itMap == m_listeners.end())
	{
		QList<eIPlugin*> listeners;
		listeners.insert(listeners.begin(), pPlugin);

		m_listeners.insert(nEventType, listeners);
	}
	else
	{
		QList<eIPlugin*>::iterator it;
		for (it = itMap.value().begin(); it != itMap.value().end(); ++it)
		{
			if (*it == pPlugin)
			{
				continue;
			}
		}
		itMap.value().insert(itMap.value().begin(), pPlugin);
	}
}

void ePluginManager::RemoveListener(int nEventType, eIPlugin* pPlugin)
{
	ePluginManager::ListenerGroup::iterator itMap = this->m_listeners.find(nEventType);
	if (itMap != this->m_listeners.end())
	{
		for (QList<eIPlugin*>::iterator it = itMap.value().begin(); it != itMap.value().end(); ++it)
		{
			if (*it == pPlugin)
			{
				itMap.value().erase(it);
				break;
			}
		}
		if (itMap.value().empty())
		{
			this->m_listeners.erase(itMap);
		}
	}
}

void ePluginManager::DispatchEvent(eIPlugin* pPlugin, int nEventType, void* pEventData)
{
	ListenerGroup::iterator itMap = m_listeners.find(nEventType);
	if (itMap != m_listeners.end())
	{
		QList<eIPlugin*> listeners = itMap.value(); 
		for (QList<eIPlugin*>::iterator it = listeners.begin(); it != listeners.end(); ++it)
		{
			if (pPlugin != NULL)
			{
				if ((*it) == pPlugin)
				{
					(*it)->HandleEvent(nEventType, pEventData);
				}
			}
			else 
			{
				(*it)->HandleEvent(nEventType, pEventData);
			}
		}
	}
}

QMap<QString, eIPlugin*> ePluginManager::GetAllPlugins()
{
    return m_listPlugins;
}