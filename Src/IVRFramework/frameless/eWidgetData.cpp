#include "IVRFramework/frameless/eWidgetData.h"
#include <QWidget>
#include <QRubberBand>
#include "eFramelessHelper.h"

using namespace IVRFramework;

int eCursorPosCalculator::m_nBorderWidth = 5;
int eCursorPosCalculator::m_nTitleHeight = 30;

IVRFramework::eCursorPosCalculator::eCursorPosCalculator()
{
	reset();
}

void IVRFramework::eCursorPosCalculator::reset()
{
	m_bOnEdges = false;
	m_bOnLeftEdge = false;
	m_bOnRightEdge = false;
	m_bOnTopEdge = false;
	m_bOnBottomEdge = false;
	m_bOnTopLeftEdge = false;
	m_bOnBottomLeftEdge = false;
	m_bOnTopRightEdge = false;
	m_bOnBottomRightEdge = false;
}

void IVRFramework::eCursorPosCalculator::recalculate(const QPoint &gMousePos, const QRect &frameRect)
{
	int globalMouseX = gMousePos.x();
	int globalMouseY = gMousePos.y();

	int frameX = frameRect.x();
	int frameY = frameRect.y();

	int frameWidth = frameRect.width();
	int frameHeight = frameRect.height();

	m_bOnLeftEdge = (globalMouseX >= frameX &&
		globalMouseX <= frameX + m_nBorderWidth);


	m_bOnRightEdge = (globalMouseX >= frameX + frameWidth - m_nBorderWidth &&
		globalMouseX <= frameX + frameWidth);

	m_bOnTopEdge = (globalMouseY >= frameY &&
		globalMouseY <= frameY + m_nBorderWidth);

	m_bOnBottomEdge = (globalMouseY >= frameY + frameHeight - m_nBorderWidth &&
		globalMouseY <= frameY + frameHeight);

	m_bOnTopLeftEdge = m_bOnTopEdge && m_bOnLeftEdge;
	m_bOnBottomLeftEdge = m_bOnBottomEdge && m_bOnLeftEdge;
	m_bOnTopRightEdge = m_bOnTopEdge && m_bOnRightEdge;
	m_bOnBottomRightEdge = m_bOnBottomEdge && m_bOnRightEdge;

	m_bOnEdges = m_bOnLeftEdge || m_bOnRightEdge || m_bOnTopEdge || m_bOnBottomEdge;

	m_bOnTitle = (globalMouseY >= frameY &&
		globalMouseY <= frameY + m_nTitleHeight);
}

IVRFramework::eWidgetData::eWidgetData(eFramelessHelperPrivate* d, QWidget* widget)
	:m_d(d)
	, m_pWidget(widget)
	, m_bLeftButtonPressed(false)
	, m_bCursorShapeChanged(false)
	, m_bLeftButtonTitlePressed(false)
	, m_pRubberBand(nullptr)
{
	m_windowFlags = m_pWidget->windowFlags();
	m_pWidget->setMouseTracking(true);
	m_pWidget->setAttribute(Qt::WA_Hover, true);

	updateRubberBandStatus();
}

IVRFramework::eWidgetData::~eWidgetData()
{
	m_pWidget->setMouseTracking(false);
	m_pWidget->setWindowFlags(m_windowFlags);
	m_pWidget->setAttribute(Qt::WA_Hover, false);

	delete m_pRubberBand;
	m_pRubberBand = NULL;
}

QWidget* IVRFramework::eWidgetData::widget()
{
	return m_pWidget;
}

void IVRFramework::eWidgetData::handleWidgetEvent(QEvent *event)
{
	switch (event->type())
	{
	default:
		break;
	case QEvent::MouseButtonPress:
		handleMousePressEvent(static_cast<QMouseEvent*>(event));
		break;
	case QEvent::MouseButtonRelease:
		handleMouseReleaseEvent(static_cast<QMouseEvent*>(event));
		break;
	case QEvent::MouseMove:
		handleMouseMoveEvent(static_cast<QMouseEvent*>(event));
		break;
	case QEvent::Leave:
		handleLeaveEvent(static_cast<QMouseEvent*>(event));
		break;
	case QEvent::HoverMove:
		handleHoverMoveEvent(static_cast<QHoverEvent*>(event));
		break;
	}
}

void IVRFramework::eWidgetData::updateRubberBandStatus()
{
	if (m_d->m_bRubberBandOnMove || m_d->m_bRubberBandOnResize)
	{
		if (NULL == m_pRubberBand)
			m_pRubberBand = new QRubberBand(QRubberBand::Rectangle);
	}
	else
	{
		delete m_pRubberBand;
		m_pRubberBand = NULL;
	}
}

void IVRFramework::eWidgetData::updateCursorShape(const QPoint &gMousePos)
{
	if (m_pWidget->isFullScreen() || m_pWidget->isMaximized())
	{
		if (m_bCursorShapeChanged)
		{
			m_pWidget->unsetCursor();
			m_bCursorShapeChanged = false;
		}
		return;
	}

	m_moveMousePos.recalculate(gMousePos, m_pWidget->frameGeometry());

	if (m_d->m_bWidgetResizable) {
		if (m_moveMousePos.m_bOnTopLeftEdge || m_moveMousePos.m_bOnBottomRightEdge)
		{
			m_pWidget->setCursor(Qt::SizeFDiagCursor);
			m_bCursorShapeChanged = true;
			return;
		}
		else if (m_moveMousePos.m_bOnTopRightEdge || m_moveMousePos.m_bOnBottomLeftEdge)
		{
			m_pWidget->setCursor(Qt::SizeBDiagCursor);
			m_bCursorShapeChanged = true;
			return;
		}
		else if (m_moveMousePos.m_bOnLeftEdge || m_moveMousePos.m_bOnRightEdge)
		{
			m_pWidget->setCursor(Qt::SizeHorCursor);
			m_bCursorShapeChanged = true;
			return;
		}
		else if (m_moveMousePos.m_bOnTopEdge || m_moveMousePos.m_bOnBottomEdge)
		{
			m_pWidget->setCursor(Qt::SizeVerCursor);
			m_bCursorShapeChanged = true;
			return;
		}
	}
	if (m_d->m_bWidgetMovable) {
		if (m_moveMousePos.m_bOnTitle)
		{
			//m_pWidget->setCursor(Qt::SizeAllCursor);
			m_pWidget->unsetCursor();
			m_bCursorShapeChanged = true;
			return;
		}
	}
	if (m_bCursorShapeChanged)
	{
		m_pWidget->unsetCursor();
		m_bCursorShapeChanged = false;
	}
}

void IVRFramework::eWidgetData::resizeWidget(const QPoint &gMousePos)
{
	QRect origRect;

	if (m_d->m_bRubberBandOnResize)
		origRect = m_pRubberBand->frameGeometry();
	else
		origRect = m_pWidget->frameGeometry();

	int left = origRect.left();
	int top = origRect.top();
	int right = origRect.right();
	int bottom = origRect.bottom();
	origRect.getCoords(&left, &top, &right, &bottom);

	int minWidth = m_pWidget->minimumWidth();
	int minHeight = m_pWidget->minimumHeight();

	if (m_pressedMousePos.m_bOnTopLeftEdge)
	{
		left = gMousePos.x();
		top = gMousePos.y();
	}
	else if (m_pressedMousePos.m_bOnBottomLeftEdge)
	{
		left = gMousePos.x();
		bottom = gMousePos.y();
	}
	else if (m_pressedMousePos.m_bOnTopRightEdge)
	{
		right = gMousePos.x();
		top = gMousePos.y();
	}
	else if (m_pressedMousePos.m_bOnBottomRightEdge)
	{
		right = gMousePos.x();
		bottom = gMousePos.y();
	}
	else if (m_pressedMousePos.m_bOnLeftEdge)
	{
		left = gMousePos.x();
	}
	else if (m_pressedMousePos.m_bOnRightEdge)
	{
		right = gMousePos.x();
	}
	else if (m_pressedMousePos.m_bOnTopEdge)
	{
		top = gMousePos.y();
	}
	else if (m_pressedMousePos.m_bOnBottomEdge)
	{
		bottom = gMousePos.y();
	}

	QRect newRect(QPoint(left, top), QPoint(right, bottom));

	if (newRect.isValid())
	{
		if (minWidth > newRect.width())
		{
			if (left != origRect.left())
				newRect.setLeft(origRect.left());
			else
				newRect.setRight(origRect.right());
		}
		if (minHeight > newRect.height())
		{
			if (top != origRect.top())
				newRect.setTop(origRect.top());
			else
				newRect.setBottom(origRect.bottom());
		}

		if (m_d->m_bRubberBandOnResize)
		{
			m_pRubberBand->setGeometry(newRect);
		}
		else
		{
			m_pWidget->setGeometry(newRect);
		}
	}
}

void IVRFramework::eWidgetData::moveWidget(const QPoint &gMousePos)
{
	if (m_d->m_bRubberBandOnMove)
	{
		m_pRubberBand->move(gMousePos - m_ptDragPos);
	}
	else
	{
		m_pWidget->move(gMousePos - m_ptDragPos);
	}
}

void IVRFramework::eWidgetData::handleMousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_bLeftButtonPressed = true;
		m_bLeftButtonTitlePressed = event->pos().y() < m_moveMousePos.m_nTitleHeight;

		QRect frameRect = m_pWidget->frameGeometry();
		m_pressedMousePos.recalculate(event->globalPos(), frameRect);

		m_ptDragPos = event->globalPos() - frameRect.topLeft();

		if (m_pressedMousePos.m_bOnEdges)
		{
			if (m_d->m_bRubberBandOnResize)
			{
				m_pRubberBand->setGeometry(frameRect);
				m_pRubberBand->show();
			}
		}
		else if (m_d->m_bRubberBandOnMove && m_bLeftButtonTitlePressed)
		{
			m_pRubberBand->setGeometry(frameRect);
			m_pRubberBand->show();
		}
	}
}

void IVRFramework::eWidgetData::handleMouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_bLeftButtonPressed = false;
		m_bLeftButtonTitlePressed = false;
		m_pressedMousePos.reset();
		if (m_pRubberBand && m_pRubberBand->isVisible())
		{
			m_pRubberBand->hide();
			m_pWidget->setGeometry(m_pRubberBand->geometry());
		}
	}
}

void IVRFramework::eWidgetData::handleMouseMoveEvent(QMouseEvent *event)
{
	if (m_bLeftButtonPressed)
	{
		if (m_d->m_bWidgetResizable && m_pressedMousePos.m_bOnEdges)
		{
			resizeWidget(event->globalPos());
		}
		else if (m_d->m_bWidgetMovable && m_bLeftButtonTitlePressed)
		{
			moveWidget(event->globalPos());
		}
	}
	else if (m_d->m_bWidgetResizable || m_d->m_bWidgetMovable)
	{
		updateCursorShape(event->globalPos());
	}
}

void IVRFramework::eWidgetData::handleLeaveEvent(QEvent *event)
{
	Q_UNUSED(event);
	if (!m_bLeftButtonPressed)
	{
		m_pWidget->unsetCursor();
	}
}

void IVRFramework::eWidgetData::handleHoverMoveEvent(QHoverEvent *event)
{
	if (m_d->m_bWidgetResizable)
	{
		updateCursorShape(m_pWidget->mapToGlobal(event->pos()));
	}
}

