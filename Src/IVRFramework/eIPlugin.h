#pragma once
#include "IVRFramework/eCommon.h"
#include "IVRFramework/eEventType.h"
#include "IVRFramework/command/eICommandSet.h"
#include "IVRFramework/frame_extension/eIFrameExtension.h"
#include "IVRFramework/ivrframework_global.h"

namespace IVRFramework {

	class IVRFRAMEWORK_EXPORT eIPlugin : public eICommandSet
	{
		DECLARE_CLASS(eIPlugin)
	public:
		eIPlugin(void);
		virtual ~eIPlugin(void);

	public:
		virtual bool Load() = 0;
		virtual void RegisterCommands() = 0;
		virtual eIFrameExtension* LoadFrameExtension();
		virtual bool AfterLoad();
		virtual bool BeforeUnLoad();
		virtual bool UnLoad();

		virtual void HandleEvent(int nEventType, void* pEventData);
		virtual QWidget* GetSetWidget();

	protected:
		void SubscribeEvent(int nEventType);

	private:
		QMap<int, int> m_SubscribeEventTypes;
	};

}//namespace IVRFramework
