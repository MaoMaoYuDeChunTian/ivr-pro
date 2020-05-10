#include "IVRFramework/control/eButtonControl.h"
#include "IVRFramework/eAppInfo.h"

using namespace IVRFramework;

eButtonControl::eButtonControl()
{
	this->SetControlType(eIControl::Button);
}

eButtonControl::~eButtonControl()
{
}

bool eButtonControl::FromXmlElement(const QDomElement & xmlElement)
{
	bool bSuccess = eIControl::FromXmlElement(xmlElement);
	return bSuccess;
}

QDomElement eButtonControl::ToXmlElement(QDomDocument xmlDoc)
{
	return QDomElement();
}

QObject* eButtonControl::ToToolBarCtrl(QToolBar* pToolBar)
{
	QString workPath = eAppInfo::GetInstance()->GetWorkPath();
	QAction* pAction = NULL;
	{
		Qt::ToolButtonStyle buttonStyle = Qt::ToolButtonTextUnderIcon;
		if (this->GetSize() == "small")
		{
			buttonStyle = Qt::ToolButtonTextBesideIcon;
		}
		else
		{
			buttonStyle = Qt::ToolButtonTextUnderIcon;
		}
		if (this->GetCaption() == "")
		{
			buttonStyle = Qt::ToolButtonIconOnly;
		}
		if (this->GetIcon() == "")
		{
			buttonStyle = Qt::ToolButtonTextOnly;
		}
		pToolBar->setToolButtonStyle(buttonStyle);

		QPixmap pix;
		bool bLoadSuccess = pix.load(workPath + "res/" + this->GetIcon());
		if (bLoadSuccess == false)
		{
			bLoadSuccess = pix.load(workPath + "res/default.png");
		}

		pAction = pToolBar->addAction(QIcon(pix.scaled(pToolBar->iconSize().width(), pToolBar->iconSize().height(), Qt::KeepAspectRatio, Qt::SmoothTransformation)), this->GetCaption());
		pAction->setShortcut(QKeySequence(this->GetShortcut()));
		pAction->setToolTip(this->GetToolTip());
		pAction->setCheckable(this->IsCheckable());
		eCommandManager::GetInstance()->ConnectCmd(this->GetLibrary(), this->GetCommandName(), this->GetCommandName(), pAction, eCommandDelegate::Action, this->GetParameter());
	}
	return pAction;
}

QObject* eButtonControl::ToMenuBarCtrl(QMenu* pMenu, QToolBar* pToolBar)
{
	QString workPath = eAppInfo::GetInstance()->GetWorkPath();
	QAction* pAction = NULL;
	{
		QPixmap pix;
		bool bLoadSuccess = pix.load(workPath + "res/" + this->GetIcon());
		if (bLoadSuccess == false)
		{
			bLoadSuccess = pix.load(workPath + "res/default.png");
		}

		pAction = pMenu->addAction(QIcon(pix.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation)), this->GetCaption());
		pAction->setShortcut(QKeySequence(this->GetShortcut()));
		pAction->setToolTip(this->GetToolTip());
		pAction->setCheckable(this->IsCheckable());

		if (this->IsAddToQuickAccess())
		{
			pToolBar->addAction(pAction);
		}
		eCommandManager::GetInstance()->ConnectCmd(this->GetLibrary(), this->GetCommandName(), this->GetCommandName(), pAction, eCommandDelegate::Action, this->GetParameter());
	}
	return pAction;
}
