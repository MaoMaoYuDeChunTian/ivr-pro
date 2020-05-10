#include "IVRFramework/control/eComboBoxControl.h"
#include "IVRFramework/eAppInfo.h"

using namespace IVRFramework;

eComboBoxControl::eComboBoxControl()
{
	this->SetControlType(eIControl::ComboBox);
}

eComboBoxControl::~eComboBoxControl()
{
}

bool eComboBoxControl::FromXmlElement(const QDomElement & xmlElement)
{
	return eContainerControl::FromXmlElement(xmlElement);
}

QDomElement eComboBoxControl::ToXmlElement(QDomDocument xmlDoc)
{
	return QDomElement();
}
