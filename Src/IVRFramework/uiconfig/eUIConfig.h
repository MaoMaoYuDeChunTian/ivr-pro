/* Copyright (C) 2019, GDI. All rights reserved.
*
* File    : eUIConfig.h 
* Version : 2.0
* Author  : ZhaoY
*
* 
*/ 

#pragma once
#include "IVRFramework/ivrframework_global.h"
#include <QString>
#include <QVector>

namespace IVRFramework
{
	class ePageItem;

	class IVRFRAMEWORK_EXPORT eUIConfig
	{
	public:
		eUIConfig();
		~eUIConfig();

	public:
		bool LoadXmlFile(const QString &strFileName);
		QVector<ePageItem*>& GetPageItems();
		QString GetFilePath();

	private:
		QString m_FilePath;
		QVector<ePageItem*> m_VecPageItems;
	};
}