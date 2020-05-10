#pragma once

/* Copyright (C) 2019, GDI. All rights reserved.
*
* File    : eFramelessHelper.h
* Version : 2.0
* Author  : ZhaoY
*
* 窗口无边框化类
*/

#pragma once
#include <QObject>
#include <QHash>
#include "IVRFramework/ivrframework_global.h"

class QWidget;
class QEvent;

namespace IVRFramework
{
	class eWidgetData;

	class eFramelessHelperPrivate
	{
	public:
		QHash<QWidget*, eWidgetData*> m_widgetDataHash;
		bool m_bWidgetMovable = true;
		bool m_bWidgetResizable = true;
		bool m_bRubberBandOnResize = true;
		bool m_bRubberBandOnMove = true;
	};


	class IVRFRAMEWORK_EXPORT eFramelessHelper : public QObject
	{
		Q_OBJECT

	public:
		eFramelessHelper(QObject *parent = 0);
		~eFramelessHelper();

		// 激活窗体
		void activateOn(QWidget *topLevelWidget);
		// 移除窗体
		void removeFrom(QWidget *topLevelWidget);
		// 设置窗体移动
		void setWidgetMovable(bool movable);
		// 设置窗体缩放
		void setWidgetResizable(bool resizable);
		// 设置橡皮筋移动
		void setRubberBandOnMove(bool movable);
		// 设置橡皮筋缩放
		void setRubberBandOnResize(bool resizable);
		// 设置边框的宽度
		void setBorderWidth(uint width);
		// 设置标题栏高度
		void setTitleHeight(uint height);
		bool widgetResizable();
		bool widgetMovable();
		bool rubberBandOnMove();
		bool rubberBandOnResisze();
		uint borderWidth();
		uint titleHeight();

	protected:
		// 事件过滤，进行移动、缩放等
		virtual bool eventFilter(QObject *obj, QEvent *event);

	private:
		eFramelessHelperPrivate *m_d;
	};
}


