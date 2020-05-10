#pragma once
#include <QList>
#include "IVRFramework/undo_redo/eIOperation.h"
#include "IVRFramework/ivrframework_global.h"

namespace IVRFramework
{
/**@class eGroupOperations
* @brief 锟斤拷锟斤拷锟斤拷锟斤拷锟?
*/
class IVRFRAMEWORK_EXPORT eGroupOperations : public eIOperation
{
public:

	/**
	* @brief 锟斤拷锟届函锟斤拷
	* @return
	*/
	eGroupOperations();

	/**
	* @brief 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
	* @return
	*/
	virtual ~eGroupOperations();

	/**
	* @brief 执锟斤拷
	* @return
	*/
	virtual void Do();

	/**
	* @brief 锟斤拷锟斤拷
	* @return
	*/
	virtual void Undo();

	/**
	* @brief 锟斤拷锟斤拷锟斤拷锟斤拷锟较?
	* @return
	*/
	virtual const QString& GetDescription();

	/**
	* @brief 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷息
	* @param [in] strDescription 锟斤拷锟斤拷锟斤拷息锟斤拷锟街凤拷锟斤拷
	* @return
	*/
	virtual void SetDescription(const QString& strDescription);

	/**
	* @brief 锟斤拷锟接诧拷锟斤拷
	* @param [in] ptrOpt 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟?
	* @return
	*/
	virtual void AddOperation(eIOperation* ptrOpt);

protected:

	/**
	* @brief 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷硬锟斤拷锟斤拷锟斤拷锟?
	*/
	QList<eIOperation*> m_lstOpt;
};

}
