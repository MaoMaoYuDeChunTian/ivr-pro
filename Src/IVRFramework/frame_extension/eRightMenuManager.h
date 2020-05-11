#pragma once
#include <QString>
#include "IVRFramework/control/eRightMenu.h"
#include "IVRFramework/ivrframework_global.h"

namespace IVRFramework {

	class IVRFRAMEWORK_EXPORT eRightMenuManager
	{
	public:
		static eRightMenuManager* GetInstance();

	private:
		eRightMenuManager(void);

	public:
		~eRightMenuManager(void);

	public:
		bool LoadXmlFile(const QString & strFileName);

	public:
		eRightMenu* GetRightMenu(QString strRightMenuName);

	protected:
		/*!
		*@brief  添加右键菜单
		*@author chengdz 2017年12月15日
		*@param[in]   eRightMenu* pRightMenu
		*/
		bool AddRightMenu(eRightMenu* pRightMenu);

		/*!
		*@brief  移除右键菜单
		*@author chengdz 2017年12月25日
		*@param[in]   QString strRightMenuName
		*@return bool
		*/
		bool RemoveRightMenu(QString strRightMenuName);

	private:
		QString m_FilePath;
		QMap<QString, eRightMenu*> m_RightMenus;//右键菜单集合
	};

}//namespace IVRFramework
