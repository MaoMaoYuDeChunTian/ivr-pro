#include "IVRFramework/eUIConfig.h"
#include <QFile>
#include "IVRFramework/ePageItem.h"
#include "IVRUtility/eCommonUtil.h"

using namespace IVRFramework;
using namespace IVRUtility;

IVRFramework::eUIConfig::eUIConfig()
{

}

IVRFramework::eUIConfig::~eUIConfig()
{

}

bool IVRFramework::eUIConfig::LoadXmlFile(const QString &strFileName)
{
	m_FilePath = strFileName;

	QDomDocument document;
	QDomElement dRoot;
	QFile* pFile = eCommonUtil::OpenXml(strFileName, document, dRoot);

	QDomNodeList PageNodeList = dRoot.elementsByTagName("Page");
	for (int i = 0; i < PageNodeList.size(); ++i)
	{
		QDomElement pageElement = PageNodeList.at(i).toElement();
		ePageItem* pPageItem = new ePageItem();
		bool bSuccess = pPageItem->FromXmlElement(pageElement);
		if (bSuccess)
		{
			m_VecPageItems.push_back(pPageItem);
		}
		else
		{
			delete pPageItem;
			pPageItem = NULL;
		}
	}

	delete pFile;
	pFile = NULL;
	return true;
}

QVector<ePageItem*>& IVRFramework::eUIConfig::GetPageItems()
{
	return m_VecPageItems;
}

QString IVRFramework::eUIConfig::GetFilePath()
{
	return m_FilePath;
}

