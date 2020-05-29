/* Copyright (C) 2019, GDI. All rights reserved.
*
* File    : eService.h
* Version : 2.0
* Author  : ZhaoY
*
* 程序主要窗口服务类
*/

#pragma once
#include "IVRFramework/ivrframework_global.h"

#include <QString>

class QSplashScreen;

namespace IVRFramework
{
	class eBaseDialog;
	class eMainWindow;
	class eIContentManager;

	class IVRFRAMEWORK_EXPORT eService
	{
	public:
		static eService* GetInstance();

	private:
		eService(void);

	public:
		~eService();

	public:
		/*!
		*@brief  程序启动
		*@author chengdz 2017年12月8日
		*/
		void StartApp();

		/*!
		*@brief  程序退出
		*@author chengdz 2017年12月8日
		*/
		void EndApp();

	public:
		eMainWindow* m_pMainWindow;
		eBaseDialog* m_MainDialog;
		eIContentManager* m_pContentManager;
		QSplashScreen* m_pSplashScreen;//启动界面

		QString m_pSaveWindowPicDir;

	public:
		static int IconSizeX;
		static int IconSizeY;
		static int IconBigSizeX;
		static int IconBigSizeY;
	};
}