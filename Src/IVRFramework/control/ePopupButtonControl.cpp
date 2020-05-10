#include "IVRFramework/control/ePopupButtonControl.h"
#include "IVRFramework/eAppInfo.h"

using namespace IVRFramework;

ePopupButtonControl::ePopupButtonControl()
{
	this->SetControlType(eIControl::PopupButton);
}

ePopupButtonControl::~ePopupButtonControl()
{
}

bool ePopupButtonControl::FromXmlElement(const QDomElement & xmlElement)
{
	return eContainerControl::FromXmlElement(xmlElement);
}

QDomElement ePopupButtonControl::ToXmlElement(QDomDocument xmlDoc)
{
	return QDomElement();
}
