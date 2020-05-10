#include "IVRFramework/base_widget/eToolBar.h"
#include "IVRFramework/base_widget/eMainWindow.h"
#include "IVRFramework/eService.h"
#include "IVRFramework/eAppInfo.h"
#include <QPainter>
#include <QHBoxLayout>
#include <QApplication>
#include <QDesktopWidget>

using namespace IVRFramework;

eToolBar::eToolBar(QWidget* parent/* = 0*/, Qt::WindowFlags f/* = 0*/)
	: QFrame(parent, f),
	m_bIsAutoHide(false)
{
	this->setAutoFillBackground(true);
	this->setAttribute(Qt::WA_TranslucentBackground, true);
	this->setWindowFlags(f|Qt::Dialog|Qt::FramelessWindowHint);

	setupUi();
	createConnection();

	QFont font;
	font.setPointSize(20);
	m_AppTitle->setFont(font);
	m_AppTitle->setText(eAppInfo::GetInstance()->ProductName());

	eMainWindow* pMainWindow = eService::GetInstance()->m_pMainWindow;
	pMainWindow->installEventFilter(this);
	this->installEventFilter(this);

	this->setObjectName("eToolBar");
	this->setStyleSheet("background-color:rgba(1,102,147,200);");
}

eToolBar::~eToolBar()
{

}

void eToolBar::setupUi()
{
	int nLogoIconSize = 64;
	int nActionIconSize = 32;
	int nCloseIconSize = 18;
	QHBoxLayout* hBoxlayout = new QHBoxLayout(this);
	hBoxlayout->setMargin(0);

	{
		QVBoxLayout* vBoxlayout = new QVBoxLayout();
		vBoxlayout->setMargin(0);

		QHBoxLayout* hBoxlayout1 = new QHBoxLayout();
		hBoxlayout1->setMargin(0);

		m_AppIcon = new QPushButton(this);
		QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
		sizePolicy.setHorizontalStretch(0);
		sizePolicy.setVerticalStretch(0);
		sizePolicy.setHeightForWidth(m_AppIcon->sizePolicy().hasHeightForWidth());
		m_AppIcon->setSizePolicy(sizePolicy);
		m_AppIcon->setIcon(QIcon(eAppInfo::GetInstance()->ProductIcon()));
		m_AppIcon->setIconSize(QSize(nLogoIconSize, nLogoIconSize));
		m_AppIcon->setFixedSize(nLogoIconSize,nLogoIconSize);
		m_AppIcon->setAutoFillBackground(true);
		m_AppIcon->setStyleSheet("background-color:rgba(0, 0, 0, 0);");
		hBoxlayout1->addWidget(m_AppIcon);

		m_AppTitle = new QLabel(this);
		m_AppTitle->setStyleSheet("background-color:rgba(0, 0, 0, 0);color:rgba(255, 255, 255, 255);");
		hBoxlayout1->addWidget(m_AppTitle);

		vBoxlayout->addLayout(hBoxlayout1);

		QSpacerItem* hSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
		vBoxlayout->addItem(hSpacer);

		hBoxlayout->addLayout(vBoxlayout);
	}

	QSpacerItem* hSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	hBoxlayout->addItem(hSpacer);

	{
		m_Toolbar = new QToolBar(this);
		m_Toolbar->setStyleSheet("border:none;background-color:rgba(0,0,0,0);color:rgba(255, 255, 255, 255);");
		m_Toolbar->setFloatable(false);
		m_Toolbar->setMovable(false);
		m_Toolbar->setIconSize(QSize(nActionIconSize, nActionIconSize));
		m_Toolbar->setAttribute(Qt::WA_AlwaysShowToolTips, false);
		m_Toolbar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

		hBoxlayout->addWidget(m_Toolbar);
	}

	//QSpacerItem* hSpacer2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	//hBoxlayout->addItem(hSpacer2);

	{
		QVBoxLayout* vLayout = new QVBoxLayout();
		vLayout->setMargin(1);

		m_btnClose = new QPushButton(this);
		m_btnClose->setFixedSize(QSize(nCloseIconSize, nCloseIconSize));
		//m_btnClose->setIcon(QIcon(eStringUtil::CStr2QStr(":/Resources/close.png")));
		vLayout->addWidget(m_btnClose);

		m_btnMin = new QPushButton(this);
		m_btnMin->setFixedSize(QSize(nCloseIconSize, nCloseIconSize));
		//m_btnMin->setIcon(QIcon(eStringUtil::CStr2QStr(":/Resources/min.png")));
		vLayout->addWidget(m_btnMin);

		m_btnMenuBarMinimize = new QPushButton(this);
		m_btnMenuBarMinimize->setFixedSize(QSize(nCloseIconSize, nCloseIconSize));
		//m_btnMenuBarMinimize->setIcon(QIcon(eStringUtil::CStr2QStr(":/Resources/ribbonMinimize.png")));
		vLayout->addWidget(m_btnMenuBarMinimize);

		QSpacerItem* verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
		vLayout->addItem(verticalSpacer);

		hBoxlayout->addLayout(vLayout);
	}

} // setupUi

void eToolBar::createConnection()
{
	connect(m_btnClose, SIGNAL(clicked(bool)),this,SLOT(slotClose(bool)));
	connect(m_btnMin, SIGNAL(clicked(bool)),this,SLOT(slotMinimize(bool))); 
	connect(m_btnMenuBarMinimize, SIGNAL(clicked(bool)),this,SLOT(slotMenuBarMinimize(bool)));
}

bool eToolBar::IsAutoHide()
{
	return m_bIsAutoHide;
}

void eToolBar::SetIsAutoHide(bool bIsAutoHide)
{
	m_bIsAutoHide = bIsAutoHide;
	m_btnMenuBarMinimize->setIcon(m_bIsAutoHide ? QIcon(":/Resources/ribbonMaximize.png") :  QIcon(":/Resources/ribbonMinimize.png"));
}

QToolBar* eToolBar::GetToolBar()
{
	return m_Toolbar;
}

void eToolBar::slotClose(bool checked)
{
	eMainWindow* pMainWindow = eService::GetInstance()->m_pMainWindow;
	pMainWindow->close();
}

void eToolBar::slotMinimize(bool checked)
{
	eMainWindow* pMainWindow = eService::GetInstance()->m_pMainWindow;
	pMainWindow->showMinimized();
}

void eToolBar::slotMenuBarMinimize(bool checked)
{
	SetIsAutoHide(!m_bIsAutoHide);
}

bool eToolBar::eventFilter(QObject *watched, QEvent *event)
{
	/*QMainWindow* pMainWindow = eService::GetInstance()->m_pMainWindow;
	if (watched == pMainWindow)
	{
		if (event->type() == QEvent::Resize)
		{
			this->move(pMainWindow->geometry().x(), pMainWindow->geometry().y());
			this->resize(pMainWindow->width(), this->height());

			QRect rect = QApplication::desktop()->availableGeometry();
			QSize size = pMainWindow->size();
			if (pMainWindow->width() == rect.width())
			{
				this->show();
			}
		}
		if (event->type() == QEvent::Move)
		{
			this->move(pMainWindow->geometry().x(), pMainWindow->geometry().y());
			this->resize(pMainWindow->width(), this->height());
		}
	}
	if (this->IsAutoHide())
	{
		QPoint curPos = QCursor::pos();
		int dy = curPos.y() - pMainWindow->geometry().y();

		if (dy < this->height())
		{
			this->move(pMainWindow->geometry().x(), pMainWindow->geometry().y());
			this->show();
		}
		else
		{
			this->hide();
		}
	}

	return QFrame::eventFilter(watched, event);*/
	return false;
}

void eToolBar::paintEvent(QPaintEvent *event)
{
	QFrame::paintEvent(event);

	QPen pen;
	Qt::PenJoinStyle join = Qt::PenJoinStyle::RoundJoin;
	pen.setJoinStyle(join);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setPen(Qt::NoPen);

	const QPoint points[6] = {
		QPoint(this->m_AppIcon->width()/2, 0),
		QPoint(this->m_AppIcon->width()/2, this->height() - 20),
		QPoint(this->m_Toolbar->pos().x() - 40, this->height() - 20),
		QPoint(this->m_Toolbar->pos().x(), this->height()),
		QPoint(this->width(), this->height()),
		QPoint(this->width(), 0),
	};

	QLinearGradient linearGradient(0, 0, 0, this->height());
	linearGradient.setColorAt(0.0, QColor(1,102,147,150));
	linearGradient.setColorAt(0.5, QColor(1,102,147,200));
	linearGradient.setColorAt(1.0, QColor(1,102,147,150));

	painter.setBrush(linearGradient);
	painter.drawPolygon(points, 6);
}