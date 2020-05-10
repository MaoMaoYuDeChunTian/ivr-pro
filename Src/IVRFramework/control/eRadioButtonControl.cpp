#include "IVRFramework/control/eRadioButtonControl.h"
#include "IVRFramework/eAppInfo.h"

using namespace IVRFramework;

eRadioButtonControl::eRadioButtonControl()
{
	this->SetControlType(eIControl::RadioButton);
}

eRadioButtonControl::~eRadioButtonControl()
{
}

bool eRadioButtonControl::FromXmlElement(const QDomElement & xmlElement)
{
	bool bSuccess = eIControl::FromXmlElement(xmlElement);
	return bSuccess;
}

QDomElement eRadioButtonControl::ToXmlElement(QDomDocument xmlDoc)
{
	return QDomElement();
}
