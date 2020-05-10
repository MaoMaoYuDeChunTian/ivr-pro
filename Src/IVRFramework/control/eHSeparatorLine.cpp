#include "IVRFramework/control/eHSeparatorLine.h"
#include "IVRFramework/eAppInfo.h"

using namespace IVRFramework;

eHSeparatorLine::eHSeparatorLine()
{
	this->SetControlType(eIControl::HSeparatorLine);
}

eHSeparatorLine::~eHSeparatorLine()
{
}

bool eHSeparatorLine::FromXmlElement(const QDomElement & xmlElement)
{
	bool bSuccess = eIControl::FromXmlElement(xmlElement);
	return bSuccess;
}

QDomElement eHSeparatorLine::ToXmlElement(QDomDocument xmlDoc)
{
	return QDomElement();
}