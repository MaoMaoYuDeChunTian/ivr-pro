#pragma once
#include <vector>
#include "IVRFramework/control/eContainerControl.h"
#include "IVRFramework/ivrframework_global.h"

namespace IVRFramework {

class IVRFRAMEWORK_EXPORT eButtonGroupControl : public eContainerControl
{
public:
	eButtonGroupControl();
	~eButtonGroupControl();

public:
	bool GetShowInToolBar(void);
	void SetShowInToolBar(bool bShowInToolBar);

public:
	virtual bool FromXmlElement(const QDomElement& xmlElement);
	virtual QDomElement ToXmlElement(QDomDocument xmlDoc);

private:
	bool m_bShowInToolBar;
};
}
