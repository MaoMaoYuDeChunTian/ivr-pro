#include "eICommand.h"
#include <QMap>
#include <QObject>
//#include "eICommandListener.h"

using namespace IVRFramework;

IVRFramework::eICommand::eICommand(void)
{

}

IVRFramework::eICommand::~eICommand(void)
{
 	auto itr = m_CommandListenerSet.begin();
 	while (itr != m_CommandListenerSet.end())
 	{
 		if (itr.value() != NULL)
 		{
 			delete itr.value();
 			itr.value() = NULL;
 		}
 		itr++;
 	}
 	m_CommandListenerSet.clear();
}

void IVRFramework::eICommand::Execute(const QJsonObject &json)
{

}

bool IVRFramework::eICommand::AddListener(eICommandListener* pCommandListener)
{
	if (m_CommandListenerSet.find(pCommandListener->Get_ClassName()) != m_CommandListenerSet.end())
	{
		return false;
	}
	m_CommandListenerSet[pCommandListener->Get_ClassName()] = pCommandListener;
	return true;
}

eICommandListener* IVRFramework::eICommand::GetListener(QString strListenerName)
{
	if (m_CommandListenerSet.find(strListenerName) != m_CommandListenerSet.end())
	{
		return m_CommandListenerSet[strListenerName];
	}
	return NULL;
}

void IVRFramework::eICommand::BeforeExecNotify(QObject* sender, QString param)
{
 	auto itr = m_CommandListenerSet.begin();
 	while (itr != m_CommandListenerSet.end())
 	{
 		if (itr.value() != NULL)
 		{
			itr.value()->BeforeExecute(sender, param);
 		}
 		itr++;
 	}
 	m_CommandListenerSet.clear();
}

void IVRFramework::eICommand::AfterExecNotify(QObject* sender, QString param)
{
 	auto  itr = m_CommandListenerSet.begin();
 	while (itr != m_CommandListenerSet.end())
 	{
 		if (itr.value() != NULL)
 		{
			itr.value()->AfterExecute(sender, param);
 		}
 		itr++;
 	}
 	m_CommandListenerSet.clear();
}

// void IVRFramework::ExecuteCommand(std::string moduleName, std::string commandName, std::string jsonParam)
// {
// 	eICommand* pCommand = eCommandManager::GetInstance()->GetCommand(moduleName.c_str(),commandName.c_str());
// 
// 	if (pCommand != NULL)
// 	{
// 		QJsonObject json;
// 		if (jsonParam != "")
// 		{
// 			QString qstrParams = eStringUtil::CStr2QStr(jsonParam.c_str());
// 			QByteArray paramData = qstrParams.toLatin1();
// 			QJsonDocument jsonDoc(QJsonDocument::fromJson(paramData));
// 			json = jsonDoc.object();
// 		}
// 		pCommand->Execute(json);
// 	}
// }
