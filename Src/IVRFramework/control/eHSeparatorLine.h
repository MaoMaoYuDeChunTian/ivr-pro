#pragma once
#include "IVRFramework/control/eIControl.h"
#include "IVRFramework/ivrframework_global.h"

namespace IVRFramework {

class IVRFRAMEWORK_EXPORT eHSeparatorLine : public eIControl
{
public:
	eHSeparatorLine();
	~eHSeparatorLine();

public:
	virtual bool FromXmlElement(const QDomElement& xmlElement);
	virtual QDomElement ToXmlElement(QDomDocument xmlDoc);

private:

};

}