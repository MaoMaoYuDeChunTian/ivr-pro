#pragma once
#include "IVRFramework/frame_extension/eIFrameExtension.h"
#include "IVRFramework/uiconfig/eUIConfig.h"
#include "IVRFramework/ivrframework_global.h"

class QMenuBar;
namespace IVRFramework {

	class IVRFRAMEWORK_EXPORT eMenuBarExtension : public eIFrameExtension
	{
	public:
		eMenuBarExtension();
		~eMenuBarExtension();

	public:
		virtual QString GetKey();
		virtual void CreateFrame();

	private:
		QMenuBar* m_menuBar;
	};

}
