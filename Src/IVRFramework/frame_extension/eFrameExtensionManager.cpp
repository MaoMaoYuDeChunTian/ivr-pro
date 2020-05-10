#include "IVRFramework/frame_extension/eFrameExtensionManager.h"
#include "IVRFramework/command/eIPlugin.h"
#include "IVRFramework/command/ePluginManager.h"
#include "IVRFramework/frame_extension/eMenuBarExtension.h"
#include "IVRFramework/frame_extension/eToolBarExtension.h"
#include "IVRFramework/uiconfig/eUIConfig.h"
#include "IVRFramework/eAppInfo.h"
#include <QDir>
#include <QFile>
#include <QWidget>

using namespace std;
using namespace IVRFramework;

eFrameExtensionManager* eFrameExtensionManager::GetInstance()
{
	static eFrameExtensionManager s_instance;
	return &s_instance;
}

eFrameExtensionManager::eFrameExtensionManager(void)
{
}

eFrameExtensionManager::~eFrameExtensionManager(void)
{
	QMap<QString, eIFrameExtension*>::iterator itr = m_FrameExtensions.begin();
	while (itr != m_FrameExtensions.end())
	{
		if (itr.value() != NULL)
		{
			delete itr.value();
			itr.value() = NULL;
		}
		itr++;
	}
	m_FrameExtensions.clear();
}

bool eFrameExtensionManager::AddFrameExtension(eIFrameExtension* pFrameExtension)
{
	if (pFrameExtension == NULL)
	{
		return false;
	}
	if (m_FrameExtensions.find(pFrameExtension->GetKey()) != m_FrameExtensions.end())
	{
		return false;
	}
	m_FrameExtensions[pFrameExtension->GetKey()] = pFrameExtension;
	return true;
}

eIFrameExtension* eFrameExtensionManager::GetFrameExtension(QString strKey)
{
	if (m_FrameExtensions.find(strKey) != m_FrameExtensions.end())
	{
		return m_FrameExtensions[strKey];
	}
	return NULL;
}

bool eFrameExtensionManager::RemoveFrameExtension(eIFrameExtension* pFrameExtension)
{
	QMap<QString, eIFrameExtension*>::iterator itr = m_FrameExtensions.begin();
	while (itr != m_FrameExtensions.end())
	{
		if (itr.value() == pFrameExtension)
		{
			delete itr.value();
			itr.value() = NULL;
			m_FrameExtensions.erase(itr);
			return true;
		}
		itr++;
	}

	return false;
}

void eFrameExtensionManager::LoadUIConfigs(const QString& uiConfigFolder)
{
	QString strFolder = uiConfigFolder;
	QDir directory(strFolder);
	if (!directory.exists())
	{
		return;
	}
	QStringList filters;
	filters << "*.xml";
	QStringList uiConfigFiles = directory.entryList(filters, QDir::Files);
	for (QStringList::size_type i = 0; i != uiConfigFiles.size(); ++i)
	{
		QString strUIConfigFile = strFolder + "/" + uiConfigFiles.at(i);
		eUIConfig* pUIConfig = new eUIConfig();
		bool bSuccess = pUIConfig->LoadXmlFile(strUIConfigFile);
		if (bSuccess)
		{
			eIFrameExtension* pUIFrameExtension = NULL;
			if(eAppInfo::GetInstance()->MainMenuType() == 0)
			{
				pUIFrameExtension = new eMenuBarExtension();
			}
			else if(eAppInfo::GetInstance()->MainMenuType() == 1)
			{
				pUIFrameExtension = new eToolBarExtension();
			}
			pUIFrameExtension->SetUIConfig(pUIConfig);
			bSuccess = AddFrameExtension(pUIFrameExtension);
			if (bSuccess)
			{
				pUIFrameExtension->CreateFrame();
			}
			else
			{
				delete pUIFrameExtension;
				pUIFrameExtension = NULL;
			}
		}
		else
		{
			delete pUIConfig;
			pUIConfig = NULL;
		}
	}
}

bool eFrameExtensionManager::AddConditionPair(QString condition, QWidget* pWidget)
{
	if (condition == "" || pWidget == NULL)
	{
		return false;
	}
	if (m_Conditions.find(condition) != m_Conditions.end())
	{
		return false;
	}
	m_Conditions[condition] = pWidget;
	return true;
}

bool eFrameExtensionManager::SetCondition(QString condition, bool bFlag)
{
	if (m_Conditions.find(condition) == m_Conditions.end())
	{
		return false;
	}
	m_Conditions[condition]->setVisible(bFlag);
	return true;
}
