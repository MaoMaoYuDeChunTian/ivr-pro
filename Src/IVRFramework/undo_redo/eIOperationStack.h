#pragma once
#include <QStack>
#include "IVRFramework/undo_redo/eIOperation.h"
#include "IVRFramework/ivrframework_global.h"

namespace IVRFramework
{
/**@class eIOperationStack
* @brief 锟斤拷锟斤拷锟斤拷栈锟斤拷
*/
class IVRFRAMEWORK_EXPORT eIOperationStack
{
public:
	/**
	* @brief 锟斤拷锟接诧拷锟斤拷
	* @param [in] ptrOpt 锟斤拷锟斤拷锟斤拷锟斤拷
	* @return
	*/
	virtual bool AddOperation(eIOperation* ptrOpt);

	/**
	* @brief 锟狡筹拷锟斤拷锟斤拷
	* @param [in] ptrOpt 锟斤拷锟斤拷锟斤拷锟斤拷
	* @return
	*/
	virtual void RemoveOperation(eIOperation* ptrOpt);

	/**
	* @brief 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷取锟斤拷锟斤拷锟斤拷锟斤拷
	* @param [in] index 锟斤拷锟斤拷锟斤拷锟斤拷
	* @return eIOperation* 锟斤拷锟斤拷锟斤拷锟斤拷
	*/
	virtual eIOperation* GetOperation(int index);

	/**
	* @brief 锟斤拷取锟斤拷一锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
	* @return eIOperation* 锟斤拷锟斤拷锟斤拷锟斤拷
	*/
	virtual eIOperation* GetRedoOperation();

	/**
	* @brief 锟斤拷取锟斤拷一锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
	* @return eIOperation* 锟斤拷锟斤拷锟斤拷锟斤拷
	*/
	virtual eIOperation* GetUndoOperation();

	/**
	* @brief 锟角凤拷锟斤拷锟斤拷锟斤拷锟?
	* @return 锟缴癸拷 true,失锟斤拷  false
	*/
	virtual bool CanRedo();

	/**
	* @brief 锟角凤拷锟斤拷曰锟斤拷锟?
	* @return  锟缴癸拷 true,失锟斤拷 false
	*/
	virtual bool CanUndo();

	/**
	* @brief 锟斤拷锟斤拷
	* @return
	*/
	virtual void Redo();

	/**
	* @brief 锟斤拷锟斤拷
	* @return
	*/
	virtual void Undo();

	/**
	* @brief 锟斤拷取锟斤拷锟斤拷锟斤拷锟斤拷
	* @return  锟斤拷锟斤拷锟斤拷锟斤拷
	*/
	virtual int GetCount();

	/**
	* @brief 锟斤拷锟斤拷
	* @return
	*/
	virtual void Reset();

protected:

	/**
	* @brief 锟斤拷锟届函锟斤拷
	* @return
	*/
	eIOperationStack();

	/**
	* @brief 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
	* @return
	*/
	virtual ~eIOperationStack();

protected:

	/**
	* @brief 锟斤拷锟斤拷锟斤拷栈锟叫碉拷前锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
	*/
	int m_nCurrIndex;

	/**
	* @brief 锟斤拷锟斤拷锟斤拷栈锟叫诧拷锟斤拷锟斤拷锟斤拷栈
	*/
	QStack<eIOperation*> m_listOpts;
};

}
