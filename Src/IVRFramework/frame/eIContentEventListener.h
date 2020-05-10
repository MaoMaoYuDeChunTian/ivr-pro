#pragma once
#include <QtGui/QtEvents>
#include "IVRFramework/eCommon.h"
#include "IVRFramework/ivrframework_global.h"

namespace IVRFramework {

class eIContentView;

class IVRFRAMEWORK_EXPORT eIContentEventListener
{
	friend class eIContentView;

public:
	enum Status
	{
		Begin = 0,
		Finish = 1,
		Continue = 2,
		Cancle = 3,
	};

public:
	DECLARE_CLASS(eIContentEventListener)

public:
	eIContentEventListener(void);
	virtual ~eIContentEventListener(void);

public:
	virtual void SetIsActive(bool bIsActive);
	virtual bool IsActive();

public:
	virtual void onPainting();
	virtual void onMousePressEvent(QMouseEvent *event);
	virtual void onMouseMoveEvent(QMouseEvent *event);
	virtual void onMouseReleaseEvent(QMouseEvent *event);
	virtual void onWheelEvent(QWheelEvent *event);

protected:
	bool m_bIsActive;
	eIContentView* m_pContentView;
};
}
