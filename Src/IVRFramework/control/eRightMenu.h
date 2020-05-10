#pragma once
#include "IVRFramework/control/eContainerControl.h"
#include "IVRFramework/ivrframework_global.h"
#include <QMenu>

namespace IVRFramework{

class IVRFRAMEWORK_EXPORT eRightMenu : public eContainerControl
{
public:
	/*!
	*@brief  锟斤拷锟届函锟斤拷
	*@author chengdz 2017锟斤拷12锟斤拷15锟斤拷
	*@param[in]   void
	*/
	eRightMenu(void);

	/*!
	*@brief  锟斤拷锟斤拷锟斤拷锟斤拷
	*@author chengdz 2017锟斤拷12锟斤拷15锟斤拷
	*@param[in]   void
	*@return virtual
	*/
	~eRightMenu(void);

public:
	/**
	* @brief 锟斤拷锟斤拷锟斤拷锟斤拷
	* @param[in] const QString &Name
	* @return void
	*/
	void SetName(const QString &Name);

	/**
	* @brief 锟斤拷取锟斤拷锟斤拷
	* @return QString
	*/
	QString GetName(void);

public:
	QMenu* GetPopupMenu();

public:
	bool FromXmlElement(const QDomElement& xmlElement);
	QDomElement ToXmlElement(QDomDocument xmlDoc);
	bool ToPopupMenu();

private:
	QString m_Name;
	QMenu* m_pPopupMenu;
};

}//namespace IVRFramework
