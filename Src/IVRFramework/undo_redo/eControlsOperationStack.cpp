#include "IVRFramework/undo_redo/eControlsOperationStack.h"
#include "IVRFramework/undo_redo/eGroupOperations.h"

using namespace IVRFramework;

eControlsOperationStack* eControlsOperationStack::m_sControlOperationStack = NULL;

eControlsOperationStack::eControlsOperationStack()
{
}

eControlsOperationStack::~eControlsOperationStack()
{
	this->Reset();
}

eControlsOperationStack* eControlsOperationStack::Instance()
{
	if (m_sControlOperationStack == NULL)
		m_sControlOperationStack = new eControlsOperationStack;

	return m_sControlOperationStack;
}

void eControlsOperationStack::Destroy()
{
	if (m_sControlOperationStack)
		delete m_sControlOperationStack;

	m_sControlOperationStack = NULL;
}

bool eControlsOperationStack::StartOperation(const QString& strDescription)
{
	if (m_pGroupOperation)
		return false;

	//m_pGroupOperation.Attach(new eGroupOperations);
	m_pGroupOperation = new eGroupOperations();
	m_pGroupOperation->SetDescription(strDescription);
	return true;
}

eGroupOperations* eControlsOperationStack::GetCurrentOperation()
{
	return m_pGroupOperation;
}

bool eControlsOperationStack::StopOperation()
{
	if (!m_pGroupOperation)
		return false;

	AddOperation(m_pGroupOperation);
	m_pGroupOperation = NULL;
	return true;
}

bool eControlsOperationStack::AbortOperation()
{
	m_pGroupOperation = NULL;
	return true;
}

bool eControlsOperationStack::AddOperation(eIOperation* ptrOpt)
{
	if (ptrOpt == NULL)
		return false;

	if (m_pGroupOperation != ptrOpt)
		return false;

	//ptrOpt->Do();

	if (m_nCurrIndex >= 0)
	{
		int nDelta = this->m_listOpts.count() - m_nCurrIndex;
		while (nDelta > 0)
		{
			this->m_listOpts.pop();
			nDelta--;
		}
	}

	this->m_listOpts.push(ptrOpt);

	m_nCurrIndex++;

	return true;
}

void eControlsOperationStack::RemoveOperation(eIOperation* ptrOpt)
{
	this->m_listOpts.removeOne(ptrOpt);
}

eIOperation* eControlsOperationStack::GetOperation(int index)
{
	if (index < 0 || index >= m_listOpts.count()) return nullptr;
	return this->m_listOpts[index];
}

eIOperation* eControlsOperationStack::GetRedoOperation()
{
	if (m_listOpts.isEmpty() || m_nCurrIndex >= m_listOpts.count())
		return nullptr;

	return m_listOpts[m_nCurrIndex];

}

eIOperation* eControlsOperationStack::GetUndoOperation()
{
	if (m_listOpts.isEmpty() || m_nCurrIndex < 1)
		return nullptr;

	return m_listOpts[m_nCurrIndex - 1];
}

bool eControlsOperationStack::CanRedo()
{
	if (m_listOpts.isEmpty() || m_nCurrIndex >= m_listOpts.count())
		return false;
	else
		return true;
}

bool eControlsOperationStack::CanUndo()
{
	if (m_listOpts.isEmpty() || m_nCurrIndex < 1)
		return false;
	else
		return true;
}

void eControlsOperationStack::Redo()
{
	// 锟叫讹拷
	if (m_listOpts.isEmpty() || m_nCurrIndex >= m_listOpts.count()) return;

	eIOperation* ptrOpt = m_listOpts[m_nCurrIndex];

	ptrOpt->Do();

	m_nCurrIndex++;
}

void eControlsOperationStack::Undo()
{
	if (m_listOpts.isEmpty() || m_nCurrIndex < 1) return;

	eIOperation* ptrOpt = m_listOpts[m_nCurrIndex - 1];

	ptrOpt->Undo();

	m_nCurrIndex--;
}

int eControlsOperationStack::GetCount()
{
	return this->m_listOpts.count();
}

void eControlsOperationStack::Reset()
{
	m_nCurrIndex = 0;
	this->m_listOpts.clear();
}
