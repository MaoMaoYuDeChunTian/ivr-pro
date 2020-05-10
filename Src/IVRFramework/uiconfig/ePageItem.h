#pragma once
#include <QVector>
#include "IVRFramework/uiconfig/eIDisplayItem.h"
#include "IVRFramework/uiconfig/eGroupItem.h"
#include "IVRFramework/ivrframework_global.h"

namespace IVRFramework {

	class IVRFRAMEWORK_EXPORT ePageItem : public eIDisplayItem
	{
	public:
		ePageItem();
		~ePageItem();

	public:
		virtual bool FromXmlElement(const QDomElement& xmlElement);
		virtual QDomElement ToXmlElement(QDomDocument xmlDoc);
		QVector<eGroupItem*>& GetGroupItems();

	private:
		QVector<eGroupItem*> m_VecGroupItems;
	};
}
