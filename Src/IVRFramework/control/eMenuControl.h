#pragma once
#include <vector>
#include "IVRFramework/control/eContainerControl.h"
#include "IVRFramework/ivrframework_global.h"

namespace IVRFramework {

class IVRFRAMEWORK_EXPORT eMenuControl : public eContainerControl
{
public:
	eMenuControl();
	~eMenuControl();
public:
	virtual bool FromXmlElement(const QDomElement& xmlElement);
	virtual QDomElement ToXmlElement(QDomDocument xmlDoc);
};

}