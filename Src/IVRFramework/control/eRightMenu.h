#pragma once
#include "IVRFramework/control/eContainerControl.h"
#include "IVRFramework/ivrframework_global.h"
#include <QMenu>

namespace IVRFramework{

class IVRFRAMEWORK_EXPORT eRightMenu : public eContainerControl
{
public:
	eRightMenu(void);
	~eRightMenu(void);

public:
	void SetName(const QString &Name);
	QString GetName(void);

public:
	QMenu* GetPopupMenu();

public:
	bool FromXmlElement(const QDomElement& xmlElement);
	QDomElement ToXmlElement(QDomDocument xmlDoc);
	bool ToPopupMenu();

private:
	QString m_Name;
	QMenu* m_pPopupMenu;
};

}//namespace IVRFramework
