#include "IVRFramework/undo_redo/eIOperation.h"

using namespace IVRFramework;

eIOperation::eIOperation()
{
	m_bDone = false;
}

eIOperation::~eIOperation()
{

}

bool eIOperation::CanRedo()
{
	return !m_bDone;
}

bool eIOperation::CanUndo()
{
	return m_bDone;
}

void eIOperation::Redo()
{
	if (!m_bDone)
	{
		Do();
	}
}

void eIOperation::Do()
{
	m_bDone = !m_bDone;
}

void eIOperation::Undo()
{
	m_bDone = !m_bDone;
}

const QString& eIOperation::GetDescription()
{
	return this->m_strDescription;
}
