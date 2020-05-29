#pragma once
#include "IVRFramework/control/eIControl.h"
#include "IVRFramework/ivrframework_global.h"

namespace IVRFramework {

class IVRFRAMEWORK_EXPORT eUserControl : public eIControl
{
public:
	eUserControl();
	~eUserControl();

public:
	virtual bool FromXmlElement(const QDomElement& xmlElement);
	virtual QDomElement ToXmlElement(QDomDocument xmlDoc);
};

}