#include <QComboBox>
#include "IVRFramework/command/eCommandManager.h"
#include "IVRFramework/ePluginManager.h"
#include "IVRFramework/frame_extension/eFrameExtensionManager.h"
#include "IVRFramework/frame/eIContentManager.h"
#include "IVRFramework/frame/eIContentView.h"
#include "IVRFramework/eService.h"
#include "IVRFramework/eAppInfo.h"

using namespace std;
using namespace IVRFramework;

eCommandManager* eCommandManager::GetInstance()
{
	static eCommandManager s_instance;
	return &s_instance;
}

eCommandManager::eCommandManager(void)
{
	connect(&m_cmdTimer, &QTimer::timeout, this, &eCommandManager::OnUpdateState);
	m_cmdTimer.start(500);
}

eCommandManager::~eCommandManager(void)
{
	m_cmdTimer.stop();
}

void eCommandManager::OnUpdateState()
{
	eIToolCommand* pCurToolCommand = NULL;
	eIContentView* pContentView = eService::GetInstance()->m_pContentManager->ActivedContentView();
	if (pContentView != NULL)
	{
		pCurToolCommand = pContentView->GetCurrentTool();
	}

	QVector<eCommandDelegate*>::iterator itr = m_lstCommandDelegate.begin();
	for (; itr != m_lstCommandDelegate.end(); ++itr)
	{
		eCommandDelegate* pCommandDelegate = *itr;
		eICommand* pCommand = pCommandDelegate->GetCommand();
		if (pCommand == NULL)
		{
			continue;
		}
		QObject* pSender = pCommandDelegate->GetSender();
		if (pCommandDelegate->GetControlType() == eCommandDelegate::Action)
		{
			QAction* pAction = static_cast<QAction*>(pSender);
			pAction->setEnabled(pCommand->IsEnable());

			eIToolCommand* pToolCommand = dynamic_cast<eIToolCommand*>(pCommand);
			if (pToolCommand != NULL)
			{
				if (pCurToolCommand != NULL && pCurToolCommand == pCommand)
				{
					pAction->setChecked(true);
				}
				else
				{
					pAction->setChecked(false);
				}
			}
		}
		else if (pCommandDelegate->GetControlType() == eCommandDelegate::Button)
		{
			QAbstractButton* pAbstractButton = static_cast<QAbstractButton*>(pSender);
			pAbstractButton->setEnabled(pCommand->IsEnable());
		}
		else if (pCommandDelegate->GetControlType() == eCommandDelegate::ComboBox)
		{
			QComboBox* pComboBox = static_cast<QComboBox*>(pSender);
			pComboBox->setEnabled(pCommand->IsEnable());
		}
		else
		{
			return;
		}
	}
}

bool eCommandManager::AddCommandSet(eICommandSet* pCommandSet)
{
	QString strCommandSetName = pCommandSet->Get_ClassName();
	if (m_CommandSets.find(strCommandSetName) != m_CommandSets.end())
	{
		return false;
	}
	m_CommandSets[strCommandSetName] = pCommandSet;
	m_CommandSets[strCommandSetName]->RegisterCommands();
	return true;
}

eICommandSet* eCommandManager::GetCommandSet(QString strCommandSetName)
{
	if (m_CommandSets.find(strCommandSetName) != m_CommandSets.end())
	{
		return m_CommandSets[strCommandSetName];
	}
	return NULL;
}

bool eCommandManager::RemoveCommandSet(QString strCommandSetName)
{
	QMap<QString, eICommandSet*>::iterator itr = m_CommandSets.find(strCommandSetName);
	if (itr != m_CommandSets.end())
	{
		delete itr.value();
		itr.value() = NULL;
		m_CommandSets.erase(itr);
		return true;
	}
	return false;
}

eICommand* eCommandManager::GetCommand(const QString & moduleName, const QString & cmdName)
{
	QString appPath = eAppInfo::GetInstance()->GetAppPath();

	QString dllName = moduleName;
	QString tempModuleName = moduleName.toLower();
	if (!tempModuleName.contains(".dll"))
	{
#ifdef _WIN32
		dllName += ".dll";
#else
		dllName = "lib" + dllName + ".so";
#endif
	}
#ifdef NDEBUG
	ePluginManager::GetInstance()->LoadPlugin(appPath + "/" + dllName);
#else
	ePluginManager::GetInstance()->LoadPlugin(appPath + "/" + dllName);
#endif

	eICommandSet* pCommandSet = eCommandManager::GetInstance()->GetCommandSet(moduleName);
	if (pCommandSet != NULL)
	{
		eICommand* pCommand = pCommandSet->GetCommand(cmdName);
		return pCommand;
	}
	return NULL;
}

bool eCommandManager::ConnectCmd(const QString& moduleName, const QString& cmdName, const QString& cmdType, QObject* pSender, eCommandDelegate::QControlType controlType, const QString strParam /*= ""*/)
{
	eICommand* pCommand = GetCommand(moduleName, cmdName);
	if (pCommand == NULL)
	{
		return false;
	}
	if (controlType == eCommandDelegate::Action)
	{
		QAction* pAction = static_cast<QAction*>(pSender);
		connect(pAction, &QAction::triggered, this, &eCommandManager::OnCommandTriggered);

		eIToolCommand* ptrTool = dynamic_cast<eIToolCommand*>(pCommand);
		if (ptrTool != NULL)
		{
			pAction->setCheckable(true);
		}
	}
	else if (controlType == eCommandDelegate::Button)
	{
		QAbstractButton* pAbstractButton = static_cast<QAbstractButton*>(pSender);
		connect(pAbstractButton, &QAbstractButton::toggled, this, &eCommandManager::OnCommandTriggered);
	}
	else if (controlType == eCommandDelegate::ComboBox)
	{
		QComboBox* pComboBox = static_cast<QComboBox*>(pSender);
		connect(pComboBox, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(OnCombCurIndexChanged(const QString &)));
	}
	else
	{
		return false;
	}

	eCommandDelegate* pCommandDelegate = new eCommandDelegate(moduleName, pCommand, strParam, pSender, controlType);
	m_lstCommandDelegate.push_back(pCommandDelegate);

	return true;
}

eCommandDelegate* eCommandManager::GetCommandDelegate(QObject* pSender)
{
	if (pSender == NULL)
	{
		return NULL;
	}

	QVector<eCommandDelegate*>::iterator itr = m_lstCommandDelegate.begin();
	for (; itr != m_lstCommandDelegate.end(); ++itr)
	{
		eCommandDelegate *pCommandDelegate = *itr;
		if (pCommandDelegate->GetSender() == pSender)
		{
			return pCommandDelegate;
		}
	}

	return NULL;
}

void eCommandManager::OnCommandTriggered()
{
	QObject* pSender = sender();

	eIContentView* pContentView = eService::GetInstance()->m_pContentManager->ActivedContentView();

	eCommandDelegate* pCommandDelegate = GetCommandDelegate(pSender);
	if (pCommandDelegate == NULL)
	{
		return;
	}
	if (pCommandDelegate->GetControlType() == eCommandDelegate::Action)
	{
		QAction* pAction = static_cast<QAction*>(pSender);
		if (pAction->isCheckable() && pCommandDelegate->IsInButtonGroup() == false)
		{
			pAction->setChecked(!pCommandDelegate->IsChecked());
			pCommandDelegate->SetChecked(pAction->isChecked());
		}
	}

	eICommand* pCommand = pCommandDelegate->GetCommand();
	if (pCommandDelegate == NULL || pCommand == NULL || !pCommand->IsEnable())
	{
		return;
	}
	eIToolCommand* ptrTool = dynamic_cast<eIToolCommand*>(pCommand);
	if (ptrTool != NULL && pContentView)
	{
		pContentView->SetCurrentTool(ptrTool);
	}

	pCommand->BeforeExecNotify(pSender, pCommandDelegate->GetCmdParam());
	pCommand->Execute(pSender, pCommandDelegate->GetCmdParam());
	pCommand->AfterExecNotify(pSender, pCommandDelegate->GetCmdParam());

	if (ptrTool == NULL && pContentView)
	{
		eIToolCommand* pCurToolCommand = pContentView->GetCurrentTool();
		if (pCurToolCommand != NULL && !pCurToolCommand->Activate())
		{
			pContentView->SetCurrentTool(NULL);
		}
	}
}

void eCommandManager::OnCombCurIndexChanged(const QString & text)
{
	OnCommandTriggered();
}
