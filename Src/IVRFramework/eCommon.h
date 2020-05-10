/* Copyright (C) 2019, GDI. All rights reserved.
*
* File    : eCommon.h 
* Version : 2.0
* Author  : ZhaoY
*
* 共用宏函数
*/ 

#pragma once
#include <QString>
#include "IVRFramework/ivrframework_global.h"

#define DECLARE_CLASS(name)\
	public:\
	virtual QString Get_ClassName()\
	{\
	return #name;\
	}

#define DECLARE_CLASSEx(name)\
	public:\
	static QString Get_ClassName()\
	{\
	return #name;\
	}
