#include "eBaseDialog.h"
#include <QDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QtEvents>
#include "IVRFramework/frameless/eFramelessHelper.h"

using namespace IVRFramework;

IVRFramework::eBaseDialog::eBaseDialog(QWidget* parent /*= 0*/, Qt::WindowFlags f /*= 0*/)
	:QDialog(parent,f)
	,m_TitleHeight(40)
{
	setWindowFlags(f | Qt::FramelessWindowHint);

	//设置可缩放
	m_pHelper = new eFramelessHelper(this);
	m_pHelper->activateOn(this);
	m_pHelper->setTitleHeight(m_TitleHeight);

	SetUpUi();
}

IVRFramework::eBaseDialog::~eBaseDialog()
{

}

void IVRFramework::eBaseDialog::SetTitleHeight(int height)
{
	m_TitleHeight = height;
	m_pHelper->setTitleHeight(height);
	m_TitleBar->setFixedHeight(height);
	m_BtnMinimize->setFixedSize(m_TitleHeight - 1, m_TitleHeight - 1);
	m_BtnMaximize->setFixedSize(m_TitleHeight - 1, m_TitleHeight - 1);
	m_BtnClose->setFixedSize(m_TitleHeight - 1, m_TitleHeight - 1);
}

void IVRFramework::eBaseDialog::SetTitleName(const QString& name)
{
	m_Title->setText(name);
}

void IVRFramework::eBaseDialog::setMinBtnVisible(bool bVisible)
{
	m_BtnMinimize->setVisible(bVisible);
}

void IVRFramework::eBaseDialog::setMaxBtnVisible(bool bVisible)
{
	m_BtnMaximize->setVisible(bVisible);
}

void IVRFramework::eBaseDialog::setCloseBtnVisible(bool bVisible)
{
	m_BtnClose->setVisible(bVisible);
}

void IVRFramework::eBaseDialog::SetWidgetMoveble(bool isable)
{
	m_pHelper->setWidgetMovable(isable);
}

void IVRFramework::eBaseDialog::SetWidgetResizeble(bool isable)
{
	m_pHelper->setWidgetResizable(isable);
}

void IVRFramework::eBaseDialog::SetContentWidget(QWidget* w)
{
	m_ContentLayout->addWidget(w);
}

void IVRFramework::eBaseDialog::SetTitleContentWidget(QWidget* w)
{
	m_TitleContentLayout->addWidget(w);
}

void IVRFramework::eBaseDialog::mouseDoubleClickEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		if (event->pos().y() < m_TitleHeight)
			onMaxResize();
	}
}

void IVRFramework::eBaseDialog::SetUpUi()
{
	QVBoxLayout* _mainLayout = new QVBoxLayout(this);
	_mainLayout->setMargin(0);
	_mainLayout->setSpacing(0);

	m_TitleBar = new QWidget(this);
	m_TitleBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	m_TitleBar->setFixedHeight(m_TitleHeight);
	m_TitleBar->setStyleSheet("background:#2c2c2c");
	_mainLayout->addWidget(m_TitleBar);

	QHBoxLayout* _titleLayout = new QHBoxLayout(m_TitleBar);
	_titleLayout->setMargin(0);
	_titleLayout->setSpacing(0);
	m_Title = new QLabel(m_TitleBar);
	m_Title->setMaximumWidth(120);
	_titleLayout->addWidget(m_Title);


	QWidget* _contentWidget = new QWidget(m_TitleBar);
	_contentWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	_contentWidget->setContentsMargins(0, 0, 0, 0);
	m_TitleContentLayout = new QHBoxLayout(_contentWidget);
	m_TitleContentLayout->setMargin(0);
	m_TitleContentLayout->setSpacing(0);
	_titleLayout->addWidget(_contentWidget);

	m_BtnMinimize = new QPushButton(m_TitleBar);
	m_BtnMinimize->setFixedSize(m_TitleHeight, m_TitleHeight);
	m_BtnMinimize->setStyleSheet("QPushButton{background: #2c2c2c;border: 0px;border-radius: 0px; border-image: url(:/IvrFramework/Resources/min_normal.png);}"
		"QPushButton:hover{border-image: url(:/IvrFramework/Resources/min_hover.png);}"
		"QPushButton:pressed{border-image: url(:/IvrFramework/Resources/min_clicked.png);}");
	_titleLayout->addWidget(m_BtnMinimize);

	m_BtnMaximize = new QPushButton(m_TitleBar);
	m_BtnMaximize->setFixedSize(m_TitleHeight, m_TitleHeight);
	m_BtnMaximize->setStyleSheet("QPushButton{background: #2c2c2c;border: 0px;border-radius: 0px;border-image: url(:/IvrFramework/Resources/max_normal.png);}"
		"QPushButton:hover{border-image: url(:/IvrFramework/Resources/max_hover.png);}"
		"QPushButton:pressed{border-image: url(:/IvrFramework/Resources/max_clicked.png)}");
	_titleLayout->addWidget(m_BtnMaximize);

	m_BtnClose = new QPushButton(m_TitleBar);
	m_BtnClose->setFixedSize(m_TitleHeight, m_TitleHeight);
	m_BtnClose->setStyleSheet("QPushButton{background: #2c2c2c;border: 0px;border-radius: 0px;border-image: url(:/IvrFramework/Resources/close_normal.png);}"
		"QPushButton:hover{border-image: url(:/IvrFramework/Resources/close_hover.png);}"
		"QPushButton:pressed{border-image: url(:/IvrFramework/Resources/close_clicked.png)}");
	_titleLayout->addWidget(m_BtnClose);

	m_ContentLayout = new QVBoxLayout(this);
	_mainLayout->addLayout(m_ContentLayout);

	connect(m_BtnClose, &QPushButton::clicked, this, &eBaseDialog::onClosed);
	connect(m_BtnMaximize, &QPushButton::clicked, this, &eBaseDialog::onMaxResize);
	connect(m_BtnMinimize, &QPushButton::clicked, this, &eBaseDialog::onMinSize);
}

void IVRFramework::eBaseDialog::onClosed()
{
	close();
	emit sigDialogClosed();
}

void IVRFramework::eBaseDialog::onMinSize()
{
	showMinimized();
}

void IVRFramework::eBaseDialog::onMaxResize()
{
	if (isMaximized())
		showNormal();
	else
		showMaximized();
}
