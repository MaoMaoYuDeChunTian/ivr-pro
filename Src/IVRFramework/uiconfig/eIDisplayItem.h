/* Copyright (C) 2019, GDI. All rights reserved.
*
* File    : eIDisplayItem.h 
* Version : 2.0
* Author  : ZhaoY
*
* 
*/ 

#pragma once

#include <QString>
#include <qdom.h>
#include "ivrframework_global.h"

namespace IVRFramework
{
	class IVRFRAMEWORK_EXPORT eIDisplayItem
	{
	public:
		eIDisplayItem();
		~eIDisplayItem();

	public:
		bool IsEnable();
		void SetEnable(bool bEnable);

		QString GetCaption();
		void SetCaption(const QString& caption);

		QString GetCondition();
		void SetCondition(const QString& condition);

		virtual bool FromXmlElement(const QDomElement& xmlElement);
		virtual QDomElement ToXmlElement(QDomDocument xmlDoc) = 0;

	private:
		bool m_bEnable;
		QString m_Caption;
		QString m_Conditon;//条件
	};
}