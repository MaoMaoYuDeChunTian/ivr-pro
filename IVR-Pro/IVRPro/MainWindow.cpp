#include "MainWindow.h"
#include <QtEvents>
#include "IVRFramework/base_widget/eMdiArea.h"
#include "IVRFramework/eService.h"
#include "QDockWidget"
#include "QPushButton"

using namespace IVRFramework;

MainWindow::MainWindow(QWidget *parent)
	: eMainWindow(parent)
	,m_oldSubWindow(nullptr)
{
	m_mdiArea = new eMdiArea(this);
	m_mdiArea->setLineWidth(1);
	m_mdiArea->setFrameShape(QFrame::Panel);
	m_mdiArea->setFrameShadow(QFrame::Plain);
	m_mdiArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_mdiArea->setViewMode(QMdiArea::TabbedView);
	m_mdiArea->setTabPosition(QTabWidget::North);
	m_mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	m_mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	m_mdiArea->setTabsClosable(true);
	eService::GetInstance()->m_pContentManager = (eMdiArea*)m_mdiArea;

	setTitleName(tr("text"));

	setCentralWidget(m_mdiArea);
	connect(m_mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(slotSubWindowActivated(QMdiSubWindow*)));
}

void MainWindow::slotSubWindowActivated(QMdiSubWindow* subWindow)
{

}

void MainWindow::closeEvent(QCloseEvent* event)
{
	m_mdiArea->closeAllSubWindows();
	if (m_mdiArea->currentSubWindow())
	{
		event->ignore();
	}
	else
	{
		event->accept();
	}
}
