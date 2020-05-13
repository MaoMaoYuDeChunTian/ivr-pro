 #pragma once

#include "IVRFramework/eIPlugin.h"
#include "IVRTestPlugin/ivrtestplugin_global.h"

using namespace IVRFramework;

extern "C" IVRTESTPLUGIN_EXPORT eIPlugin* CreatePluginInstance();

namespace IVRTest
{
	class IVRTESTPLUGIN_EXPORT IVRTestPlugin : public eIPlugin
	{
		DECLARE_CLASS(IVRTestPlugin)
	public:
		IVRTestPlugin();
		~IVRTestPlugin();

	public:
		virtual bool Load();
		virtual void RegisterCommands();
		virtual eIFrameExtension* LoadFrameExtemsion();

		virtual void HandleEvent(int nEventType, void* pEventData);
	};
}

