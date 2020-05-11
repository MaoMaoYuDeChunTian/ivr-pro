#include "IVRFramework/base_widget/eMainWindowTitle.h"
#include <QIcon>
#include <QToolButton>
#include <QMenuBar>
#include <QHBoxLayout>


IVRFramework::eMainWindowTitle::eMainWindowTitle(QString title, QWidget* parent /*= nullptr*/)
	:eBaseTitle(title,parent)
{
	m_titleBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	m_titleBtn->setIcon(QIcon(":/IvrFramework/Resources/icon.png"));
	m_titleBtn->setStyleSheet("border-style: flat");
	m_titleBtn->setEnabled(false);

	m_menuBar = new QMenuBar();
	QFont _font = m_menuBar->font();
	_font.setPointSize(10);
	m_menuBar->setFont(_font);
	m_containerHbox->addWidget(m_menuBar, 1, Qt::AlignLeft | Qt::AlignVCenter);
}

IVRFramework::eMainWindowTitle::~eMainWindowTitle()
{

}

QMenuBar* IVRFramework::eMainWindowTitle::getMenuBar()
{
	return m_menuBar;
}