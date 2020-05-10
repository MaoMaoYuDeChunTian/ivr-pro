/* Copyright (C) 2019, GDI. All rights reserved.
*
* File    : eAppInfo.h 
* Version : 2.0
* Author  : ZhaoY
*
* 程序信息管理类
*/ 

#pragma once

#include <QString>
#include "IVRFramework/ivrframework_global.h"

namespace IVRFramework
{

	class eLanguageManager;

	class IVRFRAMEWORK_EXPORT eAppInfo
	{
	public:
		static eAppInfo* GetInstance();
		~eAppInfo();

	private:
		eAppInfo();

	public:
		void SetAppPath(const QString& strAppPath);

		QString GetAppPath()const;
		QString GetWorkPath() const;
		QString UIConfigPath() const;

		QString ProductVersion()const;
		QString ProductName()const;
		QString ProductIcon()const;

		bool LoadConfig();

	protected:

	private:
		QString m_AppPath;
		QString m_ProductVersion;
		QString m_WorkPath;
		QString m_UIConfigPath;
		QString m_ProductName;
		QString m_ProductIcon;

		eLanguageManager* m_pLanguageManager;
	};
}


