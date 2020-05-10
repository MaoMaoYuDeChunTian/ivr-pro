#include "IVRFramework/base_widget/eMainWindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QFile>
#include <QTextStream>
#include <QMouseEvent>
#include <QHBoxLayout>
#include "IVRFramework/eAppInfo.h"
#include "IVRFramework/eService.h"
#include "IVRFramework/frameless/eFramelessHelper.h"
#include "IVRFramework/base_widget/eMainWindowTitle.h"

using namespace IVRFramework;

eMainWindow::eMainWindow(QWidget* parent /*= nullptr*/)
	:QWidget(parent)
{
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
	setWindowFlags(Qt::FramelessWindowHint);

	//设置可缩放
	m_pHelper = new eFramelessHelper(this);
	m_pHelper->activateOn(this);  //激活当前窗体
	m_pHelper->setTitleHeight(30);  //设置窗体的标题栏高度
	m_pHelper->setWidgetMovable(true);  //设置窗体可移动
	m_pHelper->setWidgetResizable(true);  //设置窗体可缩放
	m_pHelper->setRubberBandOnResize(false);  //设置橡皮筋效果-可缩放

	SetUpUi();

	eAppInfo::GetInstance()->SetAppPath(QApplication::applicationDirPath());
	eAppInfo::GetInstance()->LoadConfig();
}

eMainWindow::~eMainWindow()
{

}

void IVRFramework::eMainWindow::SetUpUi()
{
	m_mainVbox = new QVBoxLayout(this);
	m_mainVbox->setSpacing(0);
	m_mainVbox->setContentsMargins(0, 0, 0, 0);

	m_titleWidget = new eMainWindowTitle(tr("IDVR"));
	m_mainVbox->addWidget(m_titleWidget);

	m_mainWindow = new QMainWindow(this);
	m_mainWindow->setWindowFlags(Qt::FramelessWindowHint);
	m_mainVbox->addWidget(m_mainWindow);

	eService::GetInstance()->m_pMainWindow = this;

	connect(m_titleWidget, &eMainWindowTitle::sigMiniBtnClicked, this, &eMainWindow::onMinSize);
	connect(m_titleWidget, &eMainWindowTitle::sigMaxBtnClicked, this, &eMainWindow::onMaxResize);
	connect(m_titleWidget, &eMainWindowTitle::sigCloseBtnClicked, this, &eMainWindow::onClosed);
}

void IVRFramework::eMainWindow::setTitleHeight(int height)
{
	m_pHelper->setTitleHeight(height);
	m_titleWidget->setHeight(height);
}

int IVRFramework::eMainWindow::getTitleHeight()
{
	return m_titleWidget->getHeight();
}

void IVRFramework::eMainWindow::setTitleName(const QString& name)
{
	m_titleWidget->setTitleName(name);
}

QString IVRFramework::eMainWindow::getTitleName()
{
	return m_titleWidget->getTitleName();
}

void IVRFramework::eMainWindow::setTitleIcon(const QIcon& icon)
{
	m_titleWidget->setIcon(icon);
}

void IVRFramework::eMainWindow::setMinBtnVisible(bool bVisible)
{
	m_titleWidget->setMiniBtnVisible(bVisible);
}

void IVRFramework::eMainWindow::setMaxBtnVisible(bool bVisible)
{
	m_titleWidget->setMaxBtnVisible(bVisible);
}

void IVRFramework::eMainWindow::setCloseBtnVisible(bool bVisible)
{
	m_titleWidget->setCloseBtnVisible(bVisible);
}

void IVRFramework::eMainWindow::setCentralWidget(QWidget* widget)
{
	m_mainWindow->setCentralWidget(widget);
}

void IVRFramework::eMainWindow::addDockWidget(Qt::DockWidgetArea area, QDockWidget *dockwidget)
{
	m_mainWindow->addDockWidget(area, dockwidget);
}

QMenuBar* IVRFramework::eMainWindow::GetMenuBar()
{
	return m_titleWidget->getMenuBar();
}

QMainWindow* IVRFramework::eMainWindow::getQMainWindow()
{
	return m_mainWindow;
}

void IVRFramework::eMainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		if (event->pos().y() < m_TitleHeight)
			onMaxResize();
	}
}

void IVRFramework::eMainWindow::onClosed()
{
	close();
	emit sigMainWindowClosed();
}

void IVRFramework::eMainWindow::onMinSize()
{
	showMinimized();
}

void IVRFramework::eMainWindow::onMaxResize()
{
	if (isMaximized())
		showNormal();
	else
		showMaximized();
}
