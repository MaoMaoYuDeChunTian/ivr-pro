#include "eIDisplayItem.h"



IVRFramework::eIDisplayItem::eIDisplayItem()
	:m_bEnable(true)
	,m_Caption("")
	,m_Conditon("")
{

}

IVRFramework::eIDisplayItem::~eIDisplayItem()
{

}

bool IVRFramework::eIDisplayItem::IsEnable()
{
	return m_bEnable;
}

void IVRFramework::eIDisplayItem::SetEnable(bool bEnable)
{
	m_bEnable = bEnable;
}

QString IVRFramework::eIDisplayItem::GetCaption()
{
	return m_Caption;
}

void IVRFramework::eIDisplayItem::SetCaption(const QString& caption)
{
	m_Caption = caption;
}

QString IVRFramework::eIDisplayItem::GetCondition()
{
	return m_Conditon;
}

void IVRFramework::eIDisplayItem::SetCondition(const QString& condition)
{
	m_Conditon = condition;
}

bool IVRFramework::eIDisplayItem::FromXmlElement(const QDomElement& xmlElement)
{
	this->SetEnable(xmlElement.attribute("enable").toInt());
	this->SetCaption(xmlElement.attribute("caption"));
	this->SetCondition(xmlElement.attribute("condition"));
	return true;
}
