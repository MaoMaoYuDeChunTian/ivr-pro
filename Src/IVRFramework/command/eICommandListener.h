#pragma once
#include <QObject>
#include <QJsonObject>
#include "IVRFramework/eCommon.h"
#include "IVRFramework/ivrframework_global.h"

namespace IVRFramework {

class IVRFRAMEWORK_EXPORT eICommandListener
{
	DECLARE_CLASS(eICommandListener)

public:
	eICommandListener(void);
	virtual ~eICommandListener(void);
public:
	virtual void BeforeExecute(QObject* sender, QString param);
	virtual void AfterExecute(QObject* sender, QString param);
};

}//namespace IVRFramework
