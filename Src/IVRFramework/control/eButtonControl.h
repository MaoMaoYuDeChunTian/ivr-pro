#pragma once
#include "IVRFramework/control/eIControl.h"
#include "IVRFramework/ivrframework_global.h"

namespace IVRFramework {

class IVRFRAMEWORK_EXPORT eButtonControl : public eIControl
{
public:
	eButtonControl();
	~eButtonControl();

public:
	virtual bool FromXmlElement(const QDomElement& xmlElement);
	virtual QDomElement ToXmlElement(QDomDocument xmlDoc);
	virtual QObject* ToToolBarCtrl(QToolBar* pToolBar);
	virtual QObject* ToMenuBarCtrl(QMenu* pMenu, QToolBar* pToolBar);
};

}