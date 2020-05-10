#pragma once
#include <vector>
#include "IVRFramework/control/ePopupButtonControl.h"
#include "IVRFramework/ivrframework_global.h"

namespace IVRFramework {

class IVRFRAMEWORK_EXPORT eSplitButtonControl : public ePopupButtonControl
{
public:
	eSplitButtonControl();
	~eSplitButtonControl();

public:
	virtual bool FromXmlElement(const QDomElement& xmlElement);
	virtual QDomElement ToXmlElement(QDomDocument xmlDoc);
	virtual QObject* ToToolBarCtrl(QToolBar* pToolBar);

};
}
