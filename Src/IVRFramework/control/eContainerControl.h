﻿#pragma once
#include <QVector>
#include "IVRFramework/control/eIControl.h"
#include "IVRFramework/ivrframework_global.h"

namespace IVRFramework {

class IVRFRAMEWORK_EXPORT eContainerControl : public eIControl
{
public:
	eContainerControl();
	~eContainerControl();

public:
	virtual bool FromXmlElement(const QDomElement& xmlElement);
	virtual QDomElement ToXmlElement(QDomDocument xmlDoc);
	virtual QObject* ToToolBarCtrl(QToolBar* pToolBar);
	virtual QObject* ToMenuBarCtrl(QMenu* pMenu, QToolBar* pToolBar);

public:
	QVector<QAction*> CreateMenu(QMenu* pMenu);

protected:
	QVector<eIControl*> m_VecButtonControls;

};
}
