#include "IVRFramework/control/eSplitButtonControl.h"
#include "IVRFramework/eAppInfo.h"
#include "IVRFramework/eService.h"
#include <QToolButton>

using namespace IVRFramework;

eSplitButtonControl::eSplitButtonControl()
{
	this->SetControlType(eIControl::SplitButton);
}

eSplitButtonControl::~eSplitButtonControl()
{
}

bool eSplitButtonControl::FromXmlElement(const QDomElement & xmlElement)
{
	bool bSuccess = ePopupButtonControl::FromXmlElement(xmlElement);
	return true;
}

QDomElement eSplitButtonControl::ToXmlElement(QDomDocument xmlDoc)
{
	return QDomElement();
}

QObject* eSplitButtonControl::ToToolBarCtrl(QToolBar* pToolBar)
{
	QToolButton* pToolButton = new QToolButton();

	QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(pToolButton->sizePolicy().hasHeightForWidth());
	pToolButton->setSizePolicy(sizePolicy);

	pToolButton->setPopupMode(QToolButton::MenuButtonPopup);

	QMenu* pPopupMenu = new QMenu();
	this->CreateMenu(pPopupMenu);

	if(pPopupMenu->actions().size() < 0)
	{
		delete pPopupMenu;
		pPopupMenu = NULL;
		return NULL;
	}
	QAction* pDefaultAction = pPopupMenu->actions()[0];
	pPopupMenu->setDefaultAction(pDefaultAction);

	pToolButton->setMenu(pPopupMenu);
	pToolButton->setIcon(pDefaultAction->icon());
	pToolButton->setAutoFillBackground(true);
	pToolButton->setToolTip(this->GetToolTip());
	pToolButton->setShortcut(QKeySequence(this->GetShortcut()));

	//connect(pToolButton, SIGNAL(clicked()),this, SLOT(textButtonTriggered()));

	QAction* pBtnAction = pToolBar->addWidget(pToolButton);
	pBtnAction->setText(this->GetCaption());

	return pToolButton;
}
