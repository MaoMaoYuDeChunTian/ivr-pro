#include "IVRFramework/frame/eIContentEventListener.h"

using namespace IVRFramework;

eIContentEventListener::eIContentEventListener(void)
	:m_bIsActive(true),
	m_pContentView(NULL)
{
}

eIContentEventListener::~eIContentEventListener(void)
{
}

void eIContentEventListener::SetIsActive(bool bIsActive)
{
	m_bIsActive = bIsActive;
}

bool eIContentEventListener::IsActive()
{
	return m_bIsActive;
}

void eIContentEventListener::onPainting()
{

}

void eIContentEventListener::onMousePressEvent(QMouseEvent *event)
{

}

void eIContentEventListener::onMouseMoveEvent(QMouseEvent *event)
{

}

void eIContentEventListener::onMouseReleaseEvent(QMouseEvent *event)
{

}

void eIContentEventListener::onWheelEvent(QWheelEvent *event)
{

}