#pragma once
#include "IVRFramework/control/eContainerControl.h"
#include "IVRFramework/ivrframework_global.h"

namespace IVRFramework {

class IVRFRAMEWORK_EXPORT ePopupButtonControl : public eContainerControl
{
public:
	ePopupButtonControl();
	~ePopupButtonControl();

public:
	virtual bool FromXmlElement(const QDomElement& xmlElement);
	virtual QDomElement ToXmlElement(QDomDocument xmlDoc);

private:

};
}
