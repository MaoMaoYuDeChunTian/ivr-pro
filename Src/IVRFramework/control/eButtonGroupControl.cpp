#include "IVRFramework/control/eButtonGroupControl.h"
#include "IVRFramework/eAppInfo.h"
#include <QButtonGroup>

using namespace IVRFramework;

eButtonGroupControl::eButtonGroupControl()
	:m_bShowInToolBar(false)
{
	this->SetControlType(eIControl::ButtonGroup);
}

eButtonGroupControl::~eButtonGroupControl()
{
}

bool eButtonGroupControl::GetShowInToolBar(void)
{
	return m_bShowInToolBar;
}

void eButtonGroupControl::SetShowInToolBar(bool bShowInToolBar)
{
	m_bShowInToolBar = bShowInToolBar;
}

bool eButtonGroupControl::FromXmlElement(const QDomElement & xmlElement)
{
	this->SetShowInToolBar(xmlElement.attribute("showInToolBar").toInt());
	return eContainerControl::FromXmlElement(xmlElement);
}

QDomElement eButtonGroupControl::ToXmlElement(QDomDocument xmlDoc)
{
	return QDomElement();
}