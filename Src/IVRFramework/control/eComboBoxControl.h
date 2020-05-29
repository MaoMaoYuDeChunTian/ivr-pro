#pragma once
#include <vector>
#include "IVRFramework/control/eContainerControl.h"
#include "IVRFramework/ivrframework_global.h"

namespace IVRFramework {

class IVRFRAMEWORK_EXPORT eComboBoxControl : public eContainerControl
{
public:
	eComboBoxControl();
	~eComboBoxControl();

public:
	virtual bool FromXmlElement(const QDomElement& xmlElement);
	virtual QDomElement ToXmlElement(QDomDocument xmlDoc);
};
}
