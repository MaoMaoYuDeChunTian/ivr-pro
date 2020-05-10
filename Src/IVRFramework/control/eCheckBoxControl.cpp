#include "IVRFramework/control/eCheckBoxControl.h"
#include "IVRFramework/eAppInfo.h"

using namespace IVRFramework;

eCheckBoxControl::eCheckBoxControl()
{
	this->SetControlType(eIControl::CheckBox);
}

eCheckBoxControl::~eCheckBoxControl()
{
}

bool eCheckBoxControl::FromXmlElement(const QDomElement & xmlElement)
{
	bool bSuccess = eIControl::FromXmlElement(xmlElement);
	return bSuccess;
}

QDomElement eCheckBoxControl::ToXmlElement(QDomDocument xmlDoc)
{
	return QDomElement();
}