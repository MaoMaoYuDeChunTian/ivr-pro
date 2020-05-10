#include "IVRFramework/control/eMenuControl.h"
#include "IVRFramework/eAppInfo.h"

using namespace IVRFramework;

eMenuControl::eMenuControl()
{
	this->SetControlType(eIControl::Menu);
}

eMenuControl::~eMenuControl()
{
}

bool eMenuControl::FromXmlElement(const QDomElement & xmlElement)
{
	return eContainerControl::FromXmlElement(xmlElement);
}

QDomElement eMenuControl::ToXmlElement(QDomDocument xmlDoc)
{
	return QDomElement();
}
