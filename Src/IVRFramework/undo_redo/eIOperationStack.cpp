#include "IVRFramework/undo_redo/eIOperationStack.h"

using namespace IVRFramework;

eIOperationStack::eIOperationStack() : m_nCurrIndex(0)
{

}

eIOperationStack::~eIOperationStack()
{
	this->Reset();
}

bool eIOperationStack::AddOperation(eIOperation* ptrOpt)
{
	if (ptrOpt == NULL) return false;

	ptrOpt->Do();

	if (m_nCurrIndex > 0)
	{
		int nDelta = this->m_listOpts.count() - m_nCurrIndex;
		while (nDelta > 0)
		{
			this->m_listOpts.pop();
			nDelta--;
		}
	}

	this->m_listOpts.append(ptrOpt);

	m_nCurrIndex++;

	return true;
}

void eIOperationStack::RemoveOperation(eIOperation* ptrOpt)
{
	this->m_listOpts.removeOne(ptrOpt);
}

eIOperation* eIOperationStack::GetOperation(int index)
{
	if (index >= this->m_listOpts.count()) return NULL;
	return this->m_listOpts[index];
}

eIOperation* eIOperationStack::GetRedoOperation()
{
	return NULL;
}

eIOperation* eIOperationStack::GetUndoOperation()
{
	return NULL;
}

bool eIOperationStack::CanRedo()
{
	if (m_listOpts.count() < 1 || m_nCurrIndex >= m_listOpts.count())
		return false;
	else
		return true;
}

bool eIOperationStack::CanUndo()
{
	if (m_listOpts.count() < 1 || m_nCurrIndex < 1)
		return false;
	else
		return true;
}

void eIOperationStack::Redo()
{
	if (m_listOpts.count() < 1 || m_nCurrIndex >= m_listOpts.count()) return;

	eIOperation* ptrOpt = m_listOpts[m_nCurrIndex];

	m_nCurrIndex++;
}

void eIOperationStack::Undo()
{
	if (m_listOpts.count() < 1 || m_nCurrIndex < 1) return;

	eIOperation* ptrOpt = m_listOpts[m_nCurrIndex - 1];

	m_nCurrIndex--;
}

int eIOperationStack::GetCount()
{
	return this->m_listOpts.count();
}

void eIOperationStack::Reset()
{
	m_nCurrIndex = 0;
	this->m_listOpts.clear();
}
