#include "IVRFramework/frame_extension/eIFrameExtension.h"



IVRFramework::eIFrameExtension::eIFrameExtension()
	:m_pUIConfig(nullptr)
{

}

IVRFramework::eIFrameExtension::~eIFrameExtension()
{

}

void IVRFramework::eIFrameExtension::SetUIConfig(eUIConfig* pUIConfig)
{
	m_pUIConfig = pUIConfig;
}
