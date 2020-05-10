#include "IVRFramework/frame_extension/eToolBarExtension.h"
#include "IVRFramework/eService.h"
#include "IVRFramework/uiconfig/ePageItem.h"
#include "IVRFramework/uiconfig/eGroupItem.h"
#include <QFileInfo>

using namespace IVRFramework;

eToolBar* eToolBarExtension::s_pToolBar = NULL;

eToolBarExtension::eToolBarExtension()
{
	if (s_pToolBar == NULL)
	{
		s_pToolBar = NULL;
	}
}

eToolBarExtension::~eToolBarExtension()
{
}

QString eToolBarExtension::GetKey()
{
	QFileInfo fileInfo(m_pUIConfig->GetFilePath());
	QString baseName = fileInfo.baseName();
	return baseName;
}

void eToolBarExtension::CreateFrame()
{
	QVector<ePageItem*>& vecPages = m_pUIConfig->GetPageItems();
	for (size_t i = 0; i < vecPages.size(); i++)
	{
		QVector<eGroupItem*>& vecGroups = vecPages[i]->GetGroupItems();
		for (size_t j = 0; j < vecGroups.size(); j++)
		{
			eGroupItem* pGroupItem = vecGroups[j];
			QVector<eIControl*>& vecControls = pGroupItem->GetControlItems();
			for (size_t n = 0; n < vecControls.size(); n++)
			{
				vecControls[n]->ToToolBarCtrl(s_pToolBar->GetToolBar());
			}
		}
	}
}
