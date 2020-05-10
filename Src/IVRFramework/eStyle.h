/* Copyright (C) 2019, GDI. All rights reserved.
*
* File    : eStyle.h 
* Version : 2.0
* Author  : ZhaoY
*
* 界面风格类
*/ 

#pragma once


#include "IVRFramework/ivrframework_global.h"
#include <QApplication>
#include <QProxyStyle>

namespace IVRFramework
{
	class IVRFRAMEWORK_EXPORT eStyle : public QProxyStyle {
		Q_OBJECT

	public:
		eStyle();
		explicit eStyle(QStyle *style);

		QStyle *baseStyle() const;

		void polish(QPalette &palette) override;
		void polish(QApplication *app) override;

	private:
		QStyle *styleBase(QStyle *style = Q_NULLPTR) const;

	};
}

