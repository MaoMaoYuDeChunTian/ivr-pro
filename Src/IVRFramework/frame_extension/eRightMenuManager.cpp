#include "IVRFramework/frame_extension/eRightMenuManager.h"
#include "IVRUtility/eCommonUtil.h"
#include <QtXml/QDomDocument>
#include <QFile>

using namespace IVRUtility;
using namespace IVRFramework;

eRightMenuManager* eRightMenuManager::GetInstance()
{
	static eRightMenuManager s_instance;
	return &s_instance;
}

eRightMenuManager::eRightMenuManager(void)
{
}

eRightMenuManager::~eRightMenuManager(void)
{
	QMap<QString, eRightMenu*>::iterator itr = m_RightMenus.begin();
	while (itr != m_RightMenus.end())
	{
		if (itr.value() != NULL)
		{
			delete itr.value();
			itr.value() = NULL;
		}
		itr++;
	}
	m_RightMenus.clear();
}

eRightMenu* eRightMenuManager::GetRightMenu(QString strRightMenuName)
{
	if (m_RightMenus.find(strRightMenuName) != m_RightMenus.end())
	{
		return m_RightMenus[strRightMenuName];
	}
	return NULL;
}

bool eRightMenuManager::AddRightMenu(eRightMenu* pRightMenu)
{
	QString strRightMenuName = pRightMenu->GetName();
	if (m_RightMenus.find(strRightMenuName) != m_RightMenus.end())
	{
		return false;
	}
	m_RightMenus[strRightMenuName] = pRightMenu;
	return true;
}

bool eRightMenuManager::RemoveRightMenu(QString strRightMenuName)
{
	QMap<QString, eRightMenu*>::iterator itr = m_RightMenus.find(strRightMenuName);
	if (itr != m_RightMenus.end())
	{
		delete itr.value();
		itr.value() = NULL;
		m_RightMenus.erase(itr);
		return true;
	}
	return false;
}

bool eRightMenuManager::LoadXmlFile(const QString & strFileName)
{
	m_FilePath = strFileName;

	QDomDocument document;
	QDomElement dRoot;
	QFile* pFile = eCommonUtil::OpenXml(strFileName, document, dRoot);

	QDomNodeList RightMenuNodeList = dRoot.elementsByTagName("RightMenu");
	for (int i = 0; i < RightMenuNodeList.size(); ++i)
	{
		QDomElement pageElement = RightMenuNodeList.at(i).toElement();
		eRightMenu* pRightMenu = new eRightMenu();
		bool bSuccess1 = pRightMenu->FromXmlElement(pageElement);
		bool bSuccess2 = pRightMenu->ToPopupMenu();
		if (bSuccess1 && bSuccess2)
		{
			AddRightMenu(pRightMenu);
		}
		else
		{
			delete pRightMenu;
			pRightMenu = NULL;
		}
	}

	delete pFile;
	pFile = NULL;
	return true;
}
