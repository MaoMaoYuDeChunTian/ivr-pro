#include "IVRFramework/control/eContainerControl.h"
#include "IVRFramework/control/eButtonGroupControl.h"
#include "IVRFramework/eAppInfo.h"
#include <QPushButton>
#include <QMenu>

using namespace IVRFramework;

eContainerControl::eContainerControl()
{
	this->SetControlType(eIControl::None);
}

eContainerControl::~eContainerControl()
{
}

bool eContainerControl::FromXmlElement(const QDomElement & xmlElement)
{
	bool bSuccess = eIControl::FromXmlElement(xmlElement);
	if (bSuccess == false)
	{
		return false;
	}

	QDomNodeList btnCtrlNodeList = xmlElement.childNodes();
	int nCount = btnCtrlNodeList.size();
	for (int i = 0; i < nCount; ++i)
	{
		QDomElement controlElement = btnCtrlNodeList.at(i).toElement();
		QString nodeName = controlElement.nodeName();
		if (nodeName != "Item")
		{
			continue;
		}

		QString strTypeName = controlElement.attribute("type");
		eIControl::enControlType controlType = eIControl::GetType(strTypeName);

		eIControl* pControl = eIControl::CreateControl(controlType);
		if (pControl != NULL)
		{
			bool bSuccess = pControl->FromXmlElement(controlElement);
			if (bSuccess)
			{
				m_VecButtonControls.push_back(pControl);
			}
			else
			{
				delete pControl;
				pControl = NULL;
			}
		}
	}
	return true;
}

QDomElement eContainerControl::ToXmlElement(QDomDocument xmlDoc)
{
	return QDomElement();
}

QVector<QAction*> eContainerControl::CreateMenu(QMenu* pMenu)
{
	QVector<QAction*> vecResultActions;

	QString workPath = eAppInfo::GetInstance()->GetWorkPath();

	QVector<eIControl*>::iterator itr = this->m_VecButtonControls.begin();
	for (; itr != this->m_VecButtonControls.end(); ++itr)
	{
		eIControl* pControl = *itr;
		if (pControl->IsEnable())
		{
			if (pControl->GetControlType() == eIControl::Button)
			{
				QAction* pAction = NULL;
				{
					QPixmap pix;
					bool bLoadSuccess = pix.load(workPath + "res/" + pControl->GetIcon());
					if (bLoadSuccess == true)
					{
						pAction = pMenu->addAction(QIcon(pix.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation)), pControl->GetCaption());
					}
					else
					{
						pAction = pMenu->addAction(pControl->GetCaption());
					}
					pAction->setShortcut(QKeySequence(pControl->GetShortcut()));
					pAction->setToolTip(pControl->GetToolTip());
					pAction->setCheckable(pControl->IsCheckable());
					pAction->setObjectName(pControl->GetCaption());

					pControl->SetTag(pAction);

					eCommandManager::GetInstance()->ConnectCmd(pControl->GetLibrary(), pControl->GetCommandName(), pControl->GetCommandName(), pAction, eCommandDelegate::Action, pControl->GetParameter());
				}
				vecResultActions.push_back(pAction);
			}
			else if (pControl->GetControlType() == eIControl::HSeparatorLine)
			{
				pMenu->addSeparator();
			}
			else if (pControl->GetControlType() == eIControl::ButtonGroup)
			{
				eButtonGroupControl* pButtonGroup = (eButtonGroupControl*)pControl;
				QActionGroup* pActionGroup = new QActionGroup(pMenu);
				QVector<QAction*> vecActionGroup = pButtonGroup->CreateMenu(pMenu);
				for (int k = 0; k < vecActionGroup.size(); ++k)
				{
					pActionGroup->addAction(vecActionGroup[k]);
					eCommandDelegate* pCommandDelegate = eCommandManager::GetInstance()->GetCommandDelegate(vecActionGroup[k]);
					if(pCommandDelegate != NULL)
					{
						pCommandDelegate->SetInButtonGroup(true);
					}
				}
				pControl->SetTag(pActionGroup);
			}
		}
	}
	return vecResultActions;
}

QObject* eContainerControl::ToToolBarCtrl(QToolBar* pToolBar)
{
	int nActionIconSize = 32;
	QPushButton* pPushButton = new QPushButton();
	pPushButton->setIconSize(QSize(nActionIconSize,nActionIconSize));

	QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(pPushButton->sizePolicy().hasHeightForWidth());
	pPushButton->setSizePolicy(sizePolicy);

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

	pPushButton->setMenu(pPopupMenu);
	pPushButton->setIcon(pDefaultAction->icon());
	pPushButton->setAutoFillBackground(true);
	pPushButton->setToolTip(this->GetToolTip());
	pPushButton->setShortcut(QKeySequence(this->GetShortcut()));

	QAction* pBtnAction = pToolBar->addWidget(pPushButton);
	pBtnAction->setText(this->GetCaption());

	return pPushButton;
}

QObject* eContainerControl::ToMenuBarCtrl(QMenu* pMenu, QToolBar* pToolBar)
{
	QString workPath = eAppInfo::GetInstance()->GetWorkPath();

	QMenu* pSubMenu = new QMenu();
	pSubMenu->setTitle(this->GetCaption());
	pSubMenu->setToolTipsVisible(true);
	pSubMenu->setToolTip(this->GetToolTip());
	this->CreateMenu(pSubMenu);
	pMenu->addMenu(pSubMenu);

	QVector<eIControl*>::iterator itr = this->m_VecButtonControls.begin();
	for (; itr != this->m_VecButtonControls.end(); ++itr)
	{
		eIControl* pControl = *itr;
		if (pControl->GetControlType() == eIControl::Button)
		{
			if (this->IsAddToQuickAccess())
			{
				pToolBar->addAction((QAction*)pControl->GetTag());
			}
		}
	}

	return pSubMenu;
}