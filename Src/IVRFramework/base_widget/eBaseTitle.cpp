#include "IVRFramework/base_widget/eBaseTitle.h"
#include <QSizePolicy>
#include <QToolButton>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QPushButton>


IVRFramework::eBaseTitle::eBaseTitle(QString title, QWidget* parent /*= nullptr*/)
	:QWidget(parent)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

	QHBoxLayout* _mainHbox = new QHBoxLayout(this);
	_mainHbox->setSpacing(0);
	_mainHbox->setContentsMargins(10, 2, 10, 2);
	m_titleBtn = new QToolButton();
	QFont _titleFont = m_titleBtn->font();
	_titleFont.setPointSize(10);
	m_titleBtn->setFont(_titleFont);
	_mainHbox->addWidget(m_titleBtn);

	m_containerHbox = new QHBoxLayout();
	_mainHbox->addLayout(m_containerHbox);

	QSize _size(30, 30);
	m_minBtn = new QPushButton();
	m_minBtn->setFixedSize(_size);
	m_minBtn->setStyleSheet("QPushButton{border-image: url(:/IvrFramework/Resources/min_normal.png);}"
		"QPushButton:hover{border-image: url(:/IvrFramework/Resources/min_hover.png);}"
		"QPushButton:pressed{border-image: url(:/IvrFramework/Resources/min_clicked.png);}");
	_mainHbox->addWidget(m_minBtn);

	m_maxBtn = new QPushButton();
	m_maxBtn->setStyleSheet("QPushButton{border-image: url(:/IvrFramework/Resources/max_normal.png);}"
		"QPushButton:hover{border-image: url(:/IvrFramework/Resources/max_hover.png);}"
		"QPushButton:pressed{border-image: url(:/IvrFramework/Resources/max_clicked.png)}");
	m_maxBtn->setFixedSize(_size);
	_mainHbox->addWidget(m_maxBtn);

	m_closeBtn = new QPushButton();
	m_closeBtn->setStyleSheet("QPushButton{border-image: url(:/IvrFramework/Resources/close_normal.png);}"
		"QPushButton:hover{border-image: url(:/IvrFramework/Resources/close_hover.png);}"
		"QPushButton:pressed{border-image: url(:/IvrFramework/Resources/close_clicked.png)}");
	m_closeBtn->setFixedSize(_size);
	_mainHbox->addWidget(m_closeBtn);

	connect(m_minBtn, &QPushButton::clicked, this, &eBaseTitle::sigMiniBtnClicked);
	connect(m_maxBtn, &QPushButton::clicked, this, &eBaseTitle::sigMaxBtnClicked);
	connect(m_closeBtn, &QPushButton::clicked, this, &eBaseTitle::sigCloseBtnClicked);
}

IVRFramework::eBaseTitle::~eBaseTitle()
{

}

void IVRFramework::eBaseTitle::setHeight(int height)
{
	setHeight(height);
}

int IVRFramework::eBaseTitle::getHeight()
{
	return this->height();
}

void IVRFramework::eBaseTitle::setTitleName(const QString& name)
{
	m_titleBtn->setText(name);
}

QString IVRFramework::eBaseTitle::getTitleName()
{
	return m_titleBtn->text();
}

void IVRFramework::eBaseTitle::setIcon(const QIcon& icon)
{
	m_titleBtn->setIcon(icon);
}

void IVRFramework::eBaseTitle::setMiniBtnVisible(bool isVisible)
{
	m_minBtn->setVisible(isVisible);
}

void IVRFramework::eBaseTitle::setMaxBtnVisible(bool isVisible)
{
	m_maxBtn->setVisible(isVisible);
}

void IVRFramework::eBaseTitle::setCloseBtnVisible(bool isVisible)
{
	m_closeBtn->setVisible(isVisible);
}
