#include "IVRFramework/control/eRightMenu.h"
#include "IVRFramework/command/eCommandManager.h"
#include "IVRFramework/eAppInfo.h"
#include <QtWidgets/qproxystyle.h>

using namespace IVRFramework;

eRightMenu::eRightMenu(void)
{
	m_pPopupMenu = NULL;
}

eRightMenu::~eRightMenu(void)
{
	delete m_pPopupMenu;
	m_pPopupMenu = NULL;
}

void eRightMenu::SetName(const QString &Name)
{
	m_Name = Name;
}

QString eRightMenu::GetName(void)
{
	return m_Name;
}

QMenu* eRightMenu::GetPopupMenu()
{
	return m_pPopupMenu;
}

bool eRightMenu::FromXmlElement(const QDomElement& xmlElement)
{
	this->SetName(xmlElement.attribute("name"));
	return eContainerControl::FromXmlElement(xmlElement);
}

QDomElement eRightMenu::ToXmlElement(QDomDocument xmlDoc)
{
	return QDomElement();
}

bool eRightMenu::ToPopupMenu()
{
	QString workPath = eAppInfo::GetInstance()->GetWorkPath();

	m_pPopupMenu = new QMenu();
	this->CreateMenu(m_pPopupMenu);

	QProxyStyle *pStyle = new QProxyStyle();
	m_pPopupMenu->setStyle(pStyle);
	return true;
}
