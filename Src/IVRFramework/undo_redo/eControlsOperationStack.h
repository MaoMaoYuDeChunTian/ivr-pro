#pragma once
#include "IVRFramework/undo_redo/eIOperationStack.h"
#include "IVRFramework/undo_redo/eGroupOperations.h"
#include "IVRFramework/ivrframework_global.h"

namespace IVRFramework
{
class IVRFRAMEWORK_EXPORT eControlsOperationStack : public eIOperationStack
{
public:
	static eControlsOperationStack* Instance();
	static void Destroy();
	virtual bool StartOperation(const QString& strDescription = "");
	virtual eGroupOperations* GetCurrentOperation();
	virtual bool StopOperation();
	virtual bool AbortOperation();
	virtual bool AddOperation(eIOperation* ptrOpt) override;
	virtual void RemoveOperation(eIOperation* overrideptrOpt) override;
	virtual eIOperation* GetOperation(int index) override;
	virtual eIOperation* GetRedoOperation() override;
	virtual eIOperation* GetUndoOperation() override;
	virtual bool CanRedo() override;
	virtual bool CanUndo() override;
	virtual void Redo() override;
	virtual void Undo() override;
	virtual int GetCount() override;
	virtual void Reset() override;

private:
	eControlsOperationStack();
	~eControlsOperationStack();

private:
	eGroupOperations* m_pGroupOperation;
	static eControlsOperationStack* m_sControlOperationStack;
};
}

