#include <QFileInfo>
#include <QMenuBar>
#include "IVRFramework/frame_extension/eMenuBarExtension.h"
#include "IVRFramework/eService.h"
#include "IVRFramework/base_widget/eMainWindow.h"
#include "IVRFramework/uiconfig/ePageItem.h"
#include "IVRFramework/frame_extension/eFrameExtensionManager.h"

using namespace IVRFramework;

IVRFramework::eMenuBarExtension::eMenuBarExtension()
{
	m_menuBar = eService::GetInstance()->m_pMainWindow->GetMenuBar();
}

eMenuBarExtension::~eMenuBarExtension()
{
}

QString eMenuBarExtension::GetKey()
{
	QFileInfo fileInfo(m_pUIConfig->GetFilePath());
	QString baseName = fileInfo.baseName();
	return baseName;
}

void eMenuBarExtension::CreateFrame()
{
	QVector<ePageItem*>& vecPages = m_pUIConfig->GetPageItems();
	for (size_t i = 0; i < vecPages.size(); i++)
	{
		QMenu* pMenu = new QMenu(m_menuBar);
		pMenu->setTitle(vecPages[i]->GetCaption());
		m_menuBar->addMenu(pMenu);

		eFrameExtensionManager::GetInstance()->AddConditionPair(vecPages[i]->GetCondition(), pMenu);

		QVector<eGroupItem*>& vecGroups = vecPages[i]->GetGroupItems();

		for (size_t j = 0; j < vecGroups.size(); j++)
		{
			QToolBar* pToolBar = new QToolBar();

			eGroupItem* pGroupItem = vecGroups[j];
			QVector<eIControl*>& vecControls = pGroupItem->GetControlItems();
			for (size_t n = 0; n < vecControls.size(); n++)
			{
				vecControls[n]->ToMenuBarCtrl(pMenu, pToolBar);
			}
			if (j > 0)
			{
				pMenu->addSeparator();
			}

			if (pToolBar->actions().count() > 0)
			{
				//eService::GetInstance()->m_pMainWindow->addToolBar(pToolBar);
			}
			else
			{
				delete pToolBar;
				pToolBar = NULL;
			}
			eFrameExtensionManager::GetInstance()->AddConditionPair(pGroupItem->GetCondition(), pToolBar);
		}
	}
}
