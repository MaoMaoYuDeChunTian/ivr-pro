#include "IVRFramework/control/eUserControl.h"
#include "IVRFramework/eAppInfo.h"

using namespace IVRFramework;

eUserControl::eUserControl()
{
	this->SetControlType(eIControl::UserControl);
}

eUserControl::~eUserControl()
{
}

bool eUserControl::FromXmlElement(const QDomElement & xmlElement)
{
	bool bSuccess = eIControl::FromXmlElement(xmlElement);
	return bSuccess;
}

QDomElement eUserControl::ToXmlElement(QDomDocument xmlDoc)
{
	return QDomElement();
}