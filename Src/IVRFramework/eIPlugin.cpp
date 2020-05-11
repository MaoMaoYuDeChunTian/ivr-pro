#include "IVRFramework/eIPlugin.h"
#include "IVRFramework/ePluginManager.h"

using namespace IVRFramework;

eIPlugin::eIPlugin(void)
{
}

eIPlugin::~eIPlugin(void)
{
	QMap<int, int>::iterator itr = m_SubscribeEventTypes.begin();
	while (itr != m_SubscribeEventTypes.end())
	{
		ePluginManager::GetInstance()->RemoveListener(itr.key(), this);
		itr++;
	}
}

eIFrameExtension* eIPlugin::LoadFrameExtension()
{
	return NULL;
}

bool eIPlugin::AfterLoad()
{
	return false;
}

bool eIPlugin::BeforeUnLoad()
{
	return false;
}

bool eIPlugin::UnLoad()
{
	return false;
}

QWidget* eIPlugin::GetSetWidget()
{
    return NULL;
}

void eIPlugin::HandleEvent(int nEventType, void* pEventData)
{

}

void eIPlugin::SubscribeEvent(int nEventType)
{
	if (m_SubscribeEventTypes.find(nEventType) != m_SubscribeEventTypes.end())
	{
		return;
	}
	m_SubscribeEventTypes[nEventType] = nEventType;
	ePluginManager::GetInstance()->AddListener(nEventType, this);
}
