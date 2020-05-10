/* Copyright (C) 2019, GDI. All rights reserved.
*
* File    : eIContentView.h
* Version : 2.0
* Author  : ZhaoY
*
* 命令基类
*/

#pragma once

#include "IVRFramework/ivrframework_global.h"
#include <QVector>
#include <QString>

class QEvent;
class QMouseEvent;
class QKeyEvent;  
class QWheelEvent;
class QResizeEvent;

namespace IVRFramework {

	class eIToolCommand;
	class eIContentEventListener;

	class IVRFRAMEWORK_EXPORT eIContentView
	{
	public:
		eIContentView();
		virtual ~eIContentView();

	public:
		virtual eIToolCommand* GetCurrentTool();
		virtual void SetCurrentTool(eIToolCommand* ptrTool);

		void RegistContentListener(eIContentEventListener* pListener);

		/*!
		*@brief  移除地图窗体事件监听对象
		*@param[in]   eIContentEventListener* pListener
		*/
		void RemoveContentListener(eIContentEventListener* pListener);

		/*!
		*@brief  查找是否存在此事件监听对象
		*@param[in]   eIContentEventListener* pListener
		*@return bool
		*/
		bool FindContentListener(eIContentEventListener* pListener);

		/*!
		*@brief  根据事件监听对象名称查找事件监听对象
		*@param[in]   QString eventHandleName
		*@return eIContentEventListener*
		*/
		eIContentEventListener* FindContentListener(QString eventHandleName);

		/*!
		*@brief  得到事件监听对象集合
		*@return std::vector<eIContentEventListener*>&
		*/
		QVector<eIContentEventListener*>& GetContentListeners();

	protected:
		virtual void OnEnterEvent(QEvent* event);
		virtual void OnLeaveEvent(QEvent* event);
		virtual void OnKeyPressEvent(QKeyEvent* event);
		virtual void OnKeyReleaseEvent(QKeyEvent* event);
		virtual void OnMouseDoubleClickEvent(QMouseEvent* event);
		virtual void OnMousePressEvent(QMouseEvent *);
		virtual void OnMouseReleaseEvent(QMouseEvent *);
		virtual void OnMouseMoveEvent(QMouseEvent *);
		virtual void OnWheelEvent(QWheelEvent *);
		virtual void OnResizeEvent(QResizeEvent *event);

	protected:
		eIToolCommand* m_ptrCurrentTool;//当前工具
		eIToolCommand* m_ptrPreviousTool;//上一个工具
		QVector<eIContentEventListener*> m_uiEventHandles;//地图事件监听对象集合

	};
}