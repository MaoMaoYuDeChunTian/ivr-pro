/* Copyright (C) 2019, GDI. All rights reserved.
*
* File    : eWidgetData.h
* Version : 2.0
* Author  : ZhaoY
*
* 鼠标样式、移动窗体、缩放窗体
*/

#pragma once

#include <QPoint>
#include <QtEvents>
#include "IVRFramework/ivrframework_global.h"

class QWidget;
class QRubberBand;

namespace IVRFramework
{
	class eFramelessHelperPrivate;

	class eCursorPosCalculator
	{
	public:
		explicit eCursorPosCalculator();
		void reset();
		void recalculate(const QPoint &globalMousePos, const QRect &frameRect);

	public:
		bool m_bOnEdges = true;
		bool m_bOnLeftEdge = true;
		bool m_bOnRightEdge = true;
		bool m_bOnTopEdge = true;
		bool m_bOnBottomEdge = true;
		bool m_bOnTopLeftEdge = true;
		bool m_bOnBottomLeftEdge = true;
		bool m_bOnTopRightEdge = true;
		bool m_bOnBottomRightEdge = true;
		bool m_bOnTitle = true;

		static int m_nBorderWidth;
		static int m_nTitleHeight;
	};



	class eWidgetData
	{
	public:
		eWidgetData(eFramelessHelperPrivate* d, QWidget* widget);
		~eWidgetData();

		QWidget* widget();
		// 处理鼠标事件-划过、按下、释放、移动
		void handleWidgetEvent(QEvent *event);
		// 更新橡皮筋状态
		void updateRubberBandStatus();

	private:
		// 更新鼠标样式
		void updateCursorShape(const QPoint &gMousePos);
		// 重置窗体大小
		void resizeWidget(const QPoint &gMousePos);
		// 移动窗体
		void moveWidget(const QPoint &gMousePos);
		// 处理鼠标按下
		void handleMousePressEvent(QMouseEvent *event);
		// 处理鼠标释放
		void handleMouseReleaseEvent(QMouseEvent *event);
		// 处理鼠标移动
		void handleMouseMoveEvent(QMouseEvent *event);
		// 处理鼠标离开
		void handleLeaveEvent(QEvent *event);
		// 处理鼠标进入
		void handleHoverMoveEvent(QHoverEvent *event);

	private:
		eFramelessHelperPrivate *m_d;
		QRubberBand *m_pRubberBand;
		QWidget *m_pWidget;
		QPoint m_ptDragPos;
		eCursorPosCalculator m_pressedMousePos;
		eCursorPosCalculator m_moveMousePos;
		bool m_bLeftButtonPressed;
		bool m_bCursorShapeChanged;
		bool m_bLeftButtonTitlePressed;
		Qt::WindowFlags m_windowFlags;

	};
}