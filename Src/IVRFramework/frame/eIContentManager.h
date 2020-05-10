/* Copyright (C) 2019, GDI. All rights reserved.
*
* File    : eIContentManager.h 
* Version : 2.0
* Author  : ZhaoY
*
* 
*/ 

#pragma once
#include "IVRFramework/ivrframework_global.h"


#include <QVector>

namespace IVRFramework {

	//class eIContentView;

	class IVRFRAMEWORK_EXPORT eIContentManager
	{
	public:
		eIContentManager();
		virtual ~eIContentManager();

	public:
		/*virtual eIContentView* ActivedContentView() = 0;
		virtual void AddContentView(eIContentView* pContentView) = 0;
		virtual QVector<eIContentView*> ContentViewList() = 0;*/
	};

}