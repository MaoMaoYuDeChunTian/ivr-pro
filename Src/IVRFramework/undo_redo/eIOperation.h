#pragma once
#include <QString>
#include "IVRFramework/ivrframework_global.h"

namespace IVRFramework
{
/**@class eIOperation
* @brief  ��������
*/
class IVRFRAMEWORK_EXPORT eIOperation
{
public:

	/**
	* @brief �Ƿ��������
	* @return  �� true,�� false
	*/
	virtual bool CanRedo();

	/**
	* @brief �Ƿ���Ի���
	* @return   �� true,�� false
	*/
	virtual bool CanUndo();

	/**
	* @brief ִ��
	* @return
	*/
	virtual void Do();

	/**
	* @brief ����
	* @return
	*/
	virtual void Redo();

	/**
	* @brief ����
	* @return
	*/
	virtual void Undo();

	/**
	* @brief ���������Ϣ
	* @return ������Ϣ
	*/
	virtual const QString& GetDescription();

protected:

	/**
	* @brief ���캯��
	* @return
	*/
	eIOperation();

	/**
	* @brief ����������
	* @return
	*/
	virtual ~eIOperation();

protected:

	/**
	* @brief ������Ϣ
	*/
	QString m_strDescription;

	/**
	* @brief �Ƿ��Ѿ�ִ��
	*/
	bool m_bDone;
};

}
