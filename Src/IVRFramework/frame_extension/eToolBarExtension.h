#pragma once
#include "IVRFramework/frame_extension/eIFrameExtension.h"
#include "IVRFramework/uiconfig/eUIConfig.h"
#include "IVRFramework/base_widget/eToolBar.h"
#include "IVRFramework/ivrframework_global.h"

namespace IVRFramework {

class IVRFRAMEWORK_EXPORT eToolBarExtension : public eIFrameExtension
{
public:
	eToolBarExtension();
	~eToolBarExtension();

public:
	virtual QString GetKey();
	virtual void CreateFrame();

public:
	static eToolBar* s_pToolBar;
};

}
