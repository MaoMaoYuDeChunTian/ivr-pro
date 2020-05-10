#pragma once
#include "IVRFramework/undo_redo/eIOperationStack.h"
#include "IVRFramework/undo_redo/eGroupOperations.h"
#include "IVRFramework/ivrframework_global.h"

namespace IVRFramework
{
/**@class eControlsOperationStack
* @brief  锟斤拷栈锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
*/
class IVRFRAMEWORK_EXPORT eControlsOperationStack : public eIOperationStack
{
public:
	/**
	* @brief  锟斤拷玫锟斤拷锟?
	* @return 锟斤拷栈锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷指锟斤拷
	*/
	static eControlsOperationStack* Instance();

	/**
	* @brief  锟斤拷锟劫讹拷锟斤拷
	* @return void
	*/
	static void Destroy();

	/**
	* @brief  锟斤拷始锟洁辑锟斤拷锟斤拷锟斤拷锟斤拷
	* @param [in] strDescription = ""  默锟较诧拷锟斤拷
	* @return bool  锟缴癸拷锟斤拷锟?
	*/
	virtual bool StartOperation(const QString& strDescription = "");

	/**
	* @brief  锟斤拷取锟斤拷前锟侥诧拷锟斤拷锟斤拷锟斤拷
	* @return eGroupOperations* 锟斤拷锟斤拷指锟斤拷
	*/
	virtual eGroupOperations* GetCurrentOperation();

	/**
	* @brief  停止锟斤拷锟斤拷
	* @return bool 锟缴癸拷锟斤拷锟?
	*/
	virtual bool StopOperation();

	/**
	* @brief  锟斤拷止锟斤拷锟斤拷
	* @return bool 锟缴癸拷锟斤拷锟?
	*/
	virtual bool AbortOperation();

	/**
	* @brief 锟斤拷锟接诧拷锟斤拷
	* @param [in] ptrOpt 锟斤拷锟斤拷锟斤拷锟斤拷
	* @return  bool 锟缴癸拷锟斤拷锟?
	*/
	virtual bool AddOperation(eIOperation* ptrOpt) override;

	/**
	* @brief 锟狡筹拷锟斤拷锟斤拷
	* @param [in] ptrOpt 锟斤拷锟斤拷锟斤拷锟斤拷
	* @return void
	*/
	virtual void RemoveOperation(eIOperation* overrideptrOpt) override;

	/**
	* @brief 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷取锟斤拷锟斤拷锟斤拷锟斤拷
	* @param [in] index 锟斤拷锟斤拷锟斤拷锟斤拷
	* @return eIOperation* 锟斤拷锟斤拷锟斤拷锟斤拷
	*/
	virtual eIOperation* GetOperation(int index) override;

	/**
	* @brief 锟斤拷取锟斤拷一锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
	* @return eIOperation* 锟斤拷锟斤拷锟斤拷锟斤拷
	*/
	virtual eIOperation* GetRedoOperation() override;

	/**
	* @brief 锟斤拷取锟斤拷一锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
	* @return eIOperation* 锟斤拷锟斤拷锟斤拷锟斤拷
	*/
	virtual eIOperation* GetUndoOperation() override;

	/**
	* @brief 锟角凤拷锟斤拷锟斤拷锟斤拷锟?
	* @return bool 锟斤拷 true, 锟斤拷 false
	*/
	virtual bool CanRedo() override;

	/**
	* @brief 锟角凤拷锟斤拷曰锟斤拷锟?
	* @return bool 锟斤拷 true, 锟斤拷 false
	*/
	virtual bool CanUndo() override;

	/**
	* @brief 锟斤拷锟斤拷
	* @return void
	*/
	virtual void Redo() override;

	/**
	* @brief 锟斤拷锟斤拷
	* @return void
	*/
	virtual void Undo() override;

	/**
	* @brief 锟斤拷取锟斤拷锟斤拷锟斤拷锟斤拷
	* @return void
	*/
	virtual int GetCount() override;

	/**
	* @brief 锟斤拷锟斤拷
	* @return void
	*/
	virtual void Reset() override;

private:
	/**
	* @brief  锟斤拷锟届函锟斤拷
	*/
	eControlsOperationStack();

	/**
	* @brief  锟斤拷锟斤拷锟斤拷锟斤拷
	*/
	~eControlsOperationStack();

private:
	/**
	* @brief 锟斤拷锟斤拷锟?
	*/
	eGroupOperations* m_pGroupOperation;

	/**
	* @brief 锟斤拷锟狡诧拷锟斤拷锟斤拷栈
	*/
	static eControlsOperationStack* m_sControlOperationStack;
};
}

