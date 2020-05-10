#include "IVRFramework/frameless/eFramelessHelper.h"
#include <QList>
#include <QEvent>
#include <QWidget>
#include "eWidgetData.h"

using namespace IVRFramework;

IVRFramework::eFramelessHelper::eFramelessHelper(QObject *parent)
	:QObject(parent)
{
	m_d = new eFramelessHelperPrivate();
	m_d->m_bWidgetMovable = true;
	m_d->m_bWidgetResizable = true;
	m_d->m_bRubberBandOnResize = false;
	m_d->m_bRubberBandOnMove = false;
}

IVRFramework::eFramelessHelper::~eFramelessHelper()
{
	if (!m_d)
		return;

	QList<QWidget*> _keys = m_d->m_widgetDataHash.keys();
	for (int i = 0; i < _keys.size(); i++)
	{
		delete m_d->m_widgetDataHash.take(_keys[i]);
	}
	delete m_d;
	m_d = nullptr;
}

void IVRFramework::eFramelessHelper::activateOn(QWidget *topLevelWidget)
{
	if (!m_d->m_widgetDataHash.contains(topLevelWidget))
	{
		eWidgetData *data = new eWidgetData(m_d, topLevelWidget);
		m_d->m_widgetDataHash.insert(topLevelWidget, data);

		topLevelWidget->installEventFilter(this);
	}
}

void IVRFramework::eFramelessHelper::removeFrom(QWidget *topLevelWidget)
{
	eWidgetData *data = m_d->m_widgetDataHash.take(topLevelWidget);
	if (data)
	{
		topLevelWidget->removeEventFilter(this);
		delete data;
	}
}

void IVRFramework::eFramelessHelper::setWidgetMovable(bool movable)
{
	m_d->m_bWidgetMovable = movable;
}

void IVRFramework::eFramelessHelper::setWidgetResizable(bool resizable)
{
	m_d->m_bWidgetResizable = resizable;
}

void IVRFramework::eFramelessHelper::setRubberBandOnMove(bool movable)
{
	m_d->m_bRubberBandOnMove = movable;
	QList<eWidgetData*> list = m_d->m_widgetDataHash.values();
	foreach(eWidgetData *data, list)
	{
		data->updateRubberBandStatus();
	}
}

void IVRFramework::eFramelessHelper::setRubberBandOnResize(bool resizable)
{
	m_d->m_bRubberBandOnResize = resizable;
	QList<eWidgetData*> list = m_d->m_widgetDataHash.values();
	foreach(eWidgetData *data, list)
	{
		data->updateRubberBandStatus();
	}
}

void IVRFramework::eFramelessHelper::setBorderWidth(uint width)
{
	if (width > 0)
	{
		eCursorPosCalculator::m_nBorderWidth = width;
	}
}

void IVRFramework::eFramelessHelper::setTitleHeight(uint height)
{
	if (height > 0)
	{
		eCursorPosCalculator::m_nTitleHeight = height;
	}
}

bool IVRFramework::eFramelessHelper::widgetResizable()
{
	return m_d->m_bWidgetResizable;
}

bool IVRFramework::eFramelessHelper::widgetMovable()
{
	return m_d->m_bWidgetMovable;
}

bool IVRFramework::eFramelessHelper::rubberBandOnMove()
{
	return m_d->m_bRubberBandOnMove;
}

bool IVRFramework::eFramelessHelper::rubberBandOnResisze()
{
	return m_d->m_bRubberBandOnResize;
}

uint IVRFramework::eFramelessHelper::borderWidth()
{
	return eCursorPosCalculator::m_nBorderWidth;
}

uint IVRFramework::eFramelessHelper::titleHeight()
{
	return eCursorPosCalculator::m_nTitleHeight;
}

bool IVRFramework::eFramelessHelper::eventFilter(QObject *obj, QEvent *event)
{
	switch (event->type())
	{
	case QEvent::MouseMove:
	case QEvent::HoverMove:
	case QEvent::MouseButtonPress:
	case QEvent::MouseButtonRelease:
	case QEvent::Leave:
	{
		eWidgetData *data = m_d->m_widgetDataHash.value(static_cast<QWidget*>(obj));
		if (data)
		{
			data->handleWidgetEvent(event);
			return true;
		}
	}
	}
	return QObject::eventFilter(obj, event);
}
