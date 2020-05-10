#include "IVRFramework/eAutoHideWidget.h"
#include <QStyle>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QApplication>
#include <QDesktopWidget>

using namespace IVRFramework;

eAutoHideWidget::eAutoHideWidget(QWidget *parent/* = 0*/, Qt::WindowFlags flags/* = 0*/)
	: eBaseWidget(parent, flags)
	, m_enDriection(None)
	, m_bIsAutoHide(false)
	, m_bIsHide(true)
	, m_relatePos(Mid)
	, m_offset(0)
	, m_bClose(false)
{
	if (parent == NULL)
	{
		m_nParentWidth = QApplication::desktop()->width();
	}
	else
	{
		m_nParentWidth = parent->width();
	}
	m_nSusceptibility = 5;
	m_nAnimaDuration = 100;
	resize(200, 500);

	m_btnCtrl = new QPushButton(parent);
	m_btnCtrl->setFlat(true);
	m_btnCtrl->setAutoFillBackground(true);
	m_btnCtrl->setObjectName("ButtonCtrl");
	m_btnCtrl->setStyleSheet("QWidget#ButtonCtrl{color: rgb(255,255,255);background-color: rgb(62,152,197);border:1px groove rgb(62,152,197);}");
	m_btnCtrl->setFixedSize(24,70);
	m_btnCtrl->hide();
	m_btnCtrl->installEventFilter(this);

	parent->installEventFilter(this);
	m_titleBar->installEventFilter(this);
	this->installEventFilter(this);
	this->hide();

	this->setExpanding(false);

	connect(m_btnCtrl, SIGNAL(clicked()), this, SLOT(slotClick()));
}

eAutoHideWidget::~eAutoHideWidget()
{

}

void eAutoHideWidget::SetAttr(Direction direction, bool bIsAutoHide)
{
	m_bIsAutoHide = bIsAutoHide;
	m_enDriection = direction;
	if (m_bIsAutoHide == true)
	{
		m_bIsHide = false;
	}
	updateCtrButtonPos();
}

void eAutoHideWidget::SetRelatePos(RelatePos relatePos, int offset)
{
	m_relatePos = relatePos;
	m_offset = offset;
}

QPushButton* eAutoHideWidget::GetButtonCtrl()
{
	return m_btnCtrl;
}

void eAutoHideWidget::InitState(QPoint pos, bool bIsHide)
{
	int nOld = m_nAnimaDuration;
	m_nAnimaDuration = 0;
	this->move(pos);
	m_bIsHide = bIsHide;
	if (m_bIsHide)
	{
		m_btnCtrl->setVisible(true);
		hideWidget();
	}
	else
	{
		m_btnCtrl->setVisible(false);
		showWidget();
	}
	m_nAnimaDuration = nOld;
}

void eAutoHideWidget::updateCtrButtonPos()
{
	if (m_enDriection == Left || m_enDriection == Right)
	{
		if (m_enDriection == Left)
		{
			int x = this->pos().x() + this->width();
			int y = this->pos().y() + (this->height() - m_btnCtrl->height()) / 2;
			m_btnCtrl->move(x, y);
		}
		else
		{
			int x = this->pos().x() - m_btnCtrl->width();
			int y = this->pos().y() + (this->height() - m_btnCtrl->height()) / 2;
			m_btnCtrl->move(x, y);
		}
	}
	if (m_enDriection == TOP || m_enDriection == Down)
	{
		if (m_enDriection == TOP)
		{
			int x = this->pos().x() + (this->width() - m_btnCtrl->width()) / 2;
			int y = this->pos().y() + this->height();
			m_btnCtrl->move(x, y);
		}
		else
		{
			int x = this->pos().x() + (this->width() - m_btnCtrl->width()) / 2;
			int y = this->pos().y() - m_btnCtrl->height();
			m_btnCtrl->move(x, y);
		}
	}
}

void eAutoHideWidget::slotClick()
{
	if (m_bIsAutoHide)
	{
		return;
	}
	if (m_bIsHide)
	{
		showWidget();
		m_bIsHide = false;
	}
	else
	{
		hideWidget();
		m_bIsHide = true;
	}
}

bool eAutoHideWidget::isCanHide()
{
	if (m_bIsAutoHide == false)
	{
		return false;
	}
	QPoint pos = this->pos();
	if (m_enDriection == Left)
	{
		if (pos.x() < m_nSusceptibility)
		{
			return true;
		}
	}
	else if (m_enDriection == Right)
	{
		if (this->pos().x() + this->width() > m_nParentWidth - m_nSusceptibility)
		{
			return true;
		}
	}
	else if (m_enDriection == TOP)
	{
		if (pos.y() < m_nSusceptibility)
		{
			return true;
		}
	}
	else if (m_enDriection == Down)
	{
		if (pos.y() + this->height() < m_nSusceptibility)
		{
			return true;
		}
	}
	else
	{
		return false;
	}
	return false;
}

void eAutoHideWidget::hideWidget()
{
	QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
	animation->setDuration(m_nAnimaDuration);
	animation->setStartValue(QRect(this->pos(), this->size()));

	QRect rcEnd;
	if (m_enDriection == TOP)
	{
		rcEnd = QRect(QPoint(this->x(), -this->height()), this->size());
	}
	else if (m_enDriection == Down)
	{
		rcEnd = QRect(QPoint(this->x(), 0), this->size());
	}
	else if (m_enDriection == Left)
	{
		rcEnd = QRect(QPoint(-this->width(), this->y()), this->size());
	}
	else if (m_enDriection == Right)
	{
		rcEnd = QRect(QPoint(m_nParentWidth, this->y()), this->size());
	}
	else
	{
		rcEnd = QRect(this->pos(), this->size());
	}
	animation->setEndValue(rcEnd);
	animation->start();
}

void eAutoHideWidget::showWidget()
{
	QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
	animation->setDuration(m_nAnimaDuration);
	animation->setStartValue(QRect(this->pos(), this->size()));

	QRect rcEnd;
	if (m_enDriection == TOP)
	{
		rcEnd = QRect(QPoint(this->x(), 0), this->size());
	}
	else if (m_enDriection == Down)
	{
		rcEnd = QRect(QPoint(this->x(), this->size().height()), this->size());
	}
	else if (m_enDriection == Left)
	{
		rcEnd = QRect(QPoint(0, this->y()), this->size());
	}
	else if (m_enDriection == Right)
	{
		rcEnd = QRect(QPoint(m_nParentWidth - this->width(), this->y()), this->size());
	}
	else
	{
		rcEnd = QRect(this->pos(), this->size());
	}
	animation->setEndValue(rcEnd);
	animation->start();
}

bool eAutoHideWidget::eventFilter(QObject *watched, QEvent *event)
{
	if (this == watched)
	{
		if (event->type() == QEvent::Move || event->type() == QEvent::Resize)
		{
			updateCtrButtonPos();
		}
	}
	else if (m_btnCtrl == watched)
	{
		if (event->type() == QEvent::Enter)
		{
			onEnter();
		}
		else if (event->type() == QEvent::Leave)
		{
			onLeave();
		}
	}
	if (m_titleBar == watched)
	{
		QMouseEvent *pMouseEvent = dynamic_cast<QMouseEvent*>(event);
		if (pMouseEvent != NULL)
		{
			if (pMouseEvent->type() == QEvent::MouseButtonRelease)
			{
				if (m_bIsAutoHide)
				{
					bool bIsCanHide = isCanHide();
					if (!bIsCanHide)
					{
						m_btnCtrl->setVisible(false);
					}
					else
					{
						m_btnCtrl->setVisible(true);
					}
				}
			}
		}
	}
	if (watched == parent())
	{
		if (event->type() == QEvent::Resize)
		{
			QWidget* parentWidget = (QWidget*)watched;
			m_nParentWidth = parentWidget->width();
			if (isVisible())
			{
				QPoint newPos = this->pos();
				if(m_enDriection == TOP || m_enDriection == Down)
				{
					if (m_relatePos == Mid)
					{
						newPos = QPoint((parentWidget->width() - this->width()) / 2, this->pos().y());
					}
					else if (m_relatePos == L)
					{
						newPos = QPoint(parentWidget->x(), this->pos().y());
					}
					else if (m_relatePos == R)
					{
						newPos = QPoint(parentWidget->x() + (parentWidget->width() - this->width()), this->pos().y());
					}
					newPos.setX(newPos.x() + m_offset);
				}
				else if (m_enDriection == Left || m_enDriection == Right)
				{
					if (m_relatePos == Mid)
					{
						newPos = QPoint(this->pos().x(), (parentWidget->height() - this->height()) / 2);
					}
					else if (m_relatePos == L)
					{
						newPos = QPoint(this->pos().x(), parentWidget->y());
					}
					else if (m_relatePos == R)
					{
						newPos = QPoint(this->pos().x(), parentWidget->y() + (parentWidget->height() - this->height()));
					}
					newPos.setY(newPos.y() + m_offset);
				}
				bool bTempHide = m_bIsHide;
				if(m_bIsAutoHide)
				{
					bTempHide = true;
				}
				int nOld = m_nAnimaDuration;
				m_nAnimaDuration = 0;
				this->InitState(newPos, bTempHide);
				m_nAnimaDuration = nOld;
			}
		}
	}

	return eBaseWidget::eventFilter(watched, event);
}

void eAutoHideWidget::leaveEvent(QEvent *event)
{
	if (m_bClose == false)
	{
		onLeave();
	}
	eBaseWidget::leaveEvent(event);
}

void eAutoHideWidget::enterEvent(QEvent *event)
{
	onEnter();
	eBaseWidget::enterEvent(event);
}

void eAutoHideWidget::onEnter()
{
	if (m_bIsAutoHide)
	{
		bool bIsCanHide = isCanHide();
		if (bIsCanHide)
		{
			showWidget();
		}
	}
	else
	{
		if (!m_bIsHide)
		{
			m_btnCtrl->setVisible(true);
		}
	}
}

void eAutoHideWidget::onLeave()
{
	if (m_bIsAutoHide)
	{
		bool bIsCanHide = isCanHide();
		if (bIsCanHide)
		{
			hideWidget();
			m_btnCtrl->setVisible(true);
		}
	}
	else
	{
		if (!m_bIsHide)
		{
			m_btnCtrl->setVisible(false);
		}
	}
}

void eAutoHideWidget::showEvent(QShowEvent * event)
{
	m_bClose = false;
	if (m_btnCtrl != NULL)
	{
		if (!m_bIsHide)
		{
			m_btnCtrl->setVisible(true);
		}
	}
	eBaseWidget::showEvent(event);
}

void eAutoHideWidget::closeEvent(QCloseEvent *event)
{
	//onLeave();
	//event->ignore();
	m_bClose = true;
	if (m_btnCtrl != NULL)
	{
		m_btnCtrl->setVisible(false);
	}
	eBaseWidget::closeEvent(event);
}
