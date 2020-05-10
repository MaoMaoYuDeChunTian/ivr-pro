#include "IVRFramework/command/eICommandSet.h"

using namespace IVRFramework;

eICommandSet::eICommandSet(void)
{
}

eICommandSet::~eICommandSet(void)
{
	QMap<QString, eICommand*>::iterator itr = m_CommandSet.begin();
	while (itr != m_CommandSet.end())
	{
		if (itr.value() != NULL)
		{
			delete itr.value();
			itr.value() = NULL;
		}
		itr++;
	}
	m_CommandSet.clear();
}

bool eICommandSet::AddCommand(eICommand* pCommand)
{
	if(m_CommandSet.find(pCommand->Get_ClassName()) != m_CommandSet.end())
	{
		return false;
	}
	m_CommandSet[pCommand->Get_ClassName()] = pCommand;
	return true;
}

eICommand* eICommandSet::GetCommand(QString strCommandName)
{
	if(m_CommandSet.find(strCommandName) != m_CommandSet.end())
	{
		return m_CommandSet[strCommandName];
	}
	return NULL;
}