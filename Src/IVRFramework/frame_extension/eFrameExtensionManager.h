#pragma once
#include <QMap>
#include <QString>
#include <QWidget>
#include "IVRFramework/frame_extension/eIFrameExtension.h"
#include "IVRFramework/ivrframework_global.h"

namespace IVRFramework {

class IVRFRAMEWORK_EXPORT eFrameExtensionManager
{
public:
	static eFrameExtensionManager* GetInstance();
	~eFrameExtensionManager();

private:
	eFrameExtensionManager();

public:
	bool AddFrameExtension(eIFrameExtension* pFrameExtension);
	eIFrameExtension* GetFrameExtension(QString strKey);
	bool RemoveFrameExtension(eIFrameExtension* pFrameExtension);
	
	void LoadUIConfigs(const QString& uiConfigFolder);

	bool AddConditionPair(QString condition, QWidget* pWidget);
	bool SetCondition(QString condition, bool bFlag);

private:
	QMap<QString, eIFrameExtension*> m_FrameExtensions;
	QMap<QString, QWidget*> m_Conditions;
};
}
