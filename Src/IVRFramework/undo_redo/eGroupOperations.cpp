#include "IVRFramework/undo_redo/eGroupOperations.h"

using namespace IVRFramework;

eGroupOperations::eGroupOperations()
{

}

eGroupOperations::~eGroupOperations()
{

}

void eGroupOperations::Do()
{
	for (QList<eIOperation*>::iterator it = m_lstOpt.begin(); it != m_lstOpt.end(); it++)
	{
		(*it)->Do();
	}

	eIOperation::Do();
}

void eGroupOperations::Undo()
{
	for (QList<eIOperation*>::iterator it = m_lstOpt.end() - 1; it >= m_lstOpt.begin(); it--)
	{
		(*it)->Undo();
	}

	eIOperation::Undo();
}

const QString& eGroupOperations::GetDescription()
{
	return m_strDescription;
}

void eGroupOperations::SetDescription(const QString& strDescription)
{
	m_strDescription = strDescription;
}

void eGroupOperations::AddOperation(eIOperation* ptrOpt)
{
	m_lstOpt.append(ptrOpt);
}
