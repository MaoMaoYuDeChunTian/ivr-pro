#include "IVRFramework/uiconfig/ePageItem.h"

using namespace IVRFramework;

ePageItem::ePageItem()
{
}

ePageItem::~ePageItem()
{
}

bool ePageItem::FromXmlElement(const QDomElement& xmlElement)
{
	if (xmlElement.tagName() != "Page")
	{
		return false;
	}
	eIDisplayItem::FromXmlElement(xmlElement);

	QDomNodeList GroupNodeList = xmlElement.elementsByTagName("Group");
	for (int i = 0; i < GroupNodeList.size(); ++i)
	{
		QDomElement groupElement = GroupNodeList.at(i).toElement();
		eGroupItem* pGroupItem = new eGroupItem();
		bool bSuccess = pGroupItem->FromXmlElement(groupElement);
		if (bSuccess)
		{
			m_VecGroupItems.push_back(pGroupItem);
		}
		else
		{
			delete pGroupItem;
			pGroupItem = NULL;
		}
	}
	return true;
}

QDomElement ePageItem::ToXmlElement(QDomDocument xmlDoc)
{
	return QDomElement();
}

QVector<eGroupItem*>& ePageItem::GetGroupItems()
{
	return m_VecGroupItems;
}
