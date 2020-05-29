#pragma once
#include <QStack>
#include "IVRFramework/undo_redo/eIOperation.h"
#include "IVRFramework/ivrframework_global.h"

namespace IVRFramework
{
class IVRFRAMEWORK_EXPORT eIOperationStack
{
public:
	virtual bool AddOperation(eIOperation* ptrOpt);
	virtual void RemoveOperation(eIOperation* ptrOpt);
	virtual eIOperation* GetOperation(int index);
	virtual eIOperation* GetRedoOperation();
	virtual eIOperation* GetUndoOperation();
	virtual bool CanRedo();
	virtual bool CanUndo();
	virtual void Redo();
	virtual void Undo();
	virtual int GetCount();
	virtual void Reset();

protected:
	eIOperationStack();
	virtual ~eIOperationStack();

protected:
	int m_nCurrIndex;
	QStack<eIOperation*> m_listOpts;
};

}
