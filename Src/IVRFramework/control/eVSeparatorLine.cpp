#include "IVRFramework/control/eVSeparatorLine.h"
#include "IVRFramework/eAppInfo.h"

using namespace IVRFramework;

eVSeparatorLine::eVSeparatorLine()
{
	this->SetControlType(eIControl::VSeparatorLine);
}

eVSeparatorLine::~eVSeparatorLine()
{
}

bool eVSeparatorLine::FromXmlElement(const QDomElement & xmlElement)
{
	bool bSuccess = eIControl::FromXmlElement(xmlElement);
	return bSuccess;
}

QDomElement eVSeparatorLine::ToXmlElement(QDomDocument xmlDoc)
{
	return QDomElement();
}
