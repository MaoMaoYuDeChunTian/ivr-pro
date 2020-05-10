#pragma once
#include <vector>
#include "IVRFramework/uiconfig/eIDisplayItem.h"
#include "IVRFramework/control/eIControl.h"
#include "IVRFramework/ivrframework_global.h"

namespace IVRFramework {

class IVRFRAMEWORK_EXPORT eGroupItem : public eIDisplayItem
{
public:
	eGroupItem();
	~eGroupItem();

public:
	QString GetAlignment();
	void SetAlignment(QString alignment);

public:
	virtual bool FromXmlElement(const QDomElement& xmlElement);
	virtual QDomElement ToXmlElement(QDomDocument xmlDoc);
	QVector<eIControl*>& GetControlItems();

private:
	QString m_Alignment;
	QVector<eIControl*> m_VecControlItems;
};

}
