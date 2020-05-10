#include "IVRFramework/uiconfig/eGroupItem.h"

using namespace IVRFramework;

eGroupItem::eGroupItem()
{
}

eGroupItem::~eGroupItem()
{
}

QString eGroupItem::GetAlignment()
{
	return m_Alignment;
}

void eGroupItem::SetAlignment(QString alignment)
{
	m_Alignment = alignment;
}

bool eGroupItem::FromXmlElement(const QDomElement& xmlElement)
{
	if (xmlElement.tagName() != "Group")
	{
		return false;
	}
	eIDisplayItem::FromXmlElement(xmlElement);

	this->SetAlignment(xmlElement.attribute("alignment"));

	QDomNodeList controlNodeList = xmlElement.childNodes();
	for (int i = 0; i < controlNodeList.size(); ++i)
	{
		QDomElement controlElement = controlNodeList.at(i).toElement();
		QString nodeName = controlElement.nodeName();
		if (nodeName != "Item")
		{
			continue;
		}
		QString strTypeName = controlElement.attribute("type");
		eIControl::enControlType controlType = eIControl::GetType(strTypeName);

		eIControl* pControl = eIControl::CreateControl(controlType);
		if (pControl != NULL)
		{
			bool bSuccess = pControl->FromXmlElement(controlElement);
			if (bSuccess)
			{
				m_VecControlItems.push_back(pControl);
			}
			else
			{
				delete pControl;
				pControl = NULL;
			}
		}
	}
	return true;
}

QDomElement eGroupItem::ToXmlElement(QDomDocument xmlDoc)
{
	return QDomElement();
}

QVector<eIControl*>& eGroupItem::GetControlItems()
{
	return m_VecControlItems;
}
