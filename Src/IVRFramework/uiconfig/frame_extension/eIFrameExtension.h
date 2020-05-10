/* Copyright (C) 2019, GDI. All rights reserved.
*
* File    : eIFrameExtension.h 
* Version : 2.0
* Author  : ZhaoY
*
* 创建菜单接口类
*/ 

#pragma once

#include <QString>
#include "ivrframework_global.h"

namespace IVRFramework
{
	class eUIConfig;

	class IVRFRAMEWORK_EXPORT eIFrameExtension
	{
	public:
		eIFrameExtension();
		~eIFrameExtension();

		//获取Key
		virtual QString GetKey() = 0;
		//创建菜单框架
		virtual void CreateFrame() = 0;
		
		void SetUIConfig(eUIConfig* pUIConfig);

	protected:
		eUIConfig* m_pUIConfig;
	};
}