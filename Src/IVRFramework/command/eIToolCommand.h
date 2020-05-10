/* Copyright (C) 2019, GDI. All rights reserved.
*
* File    : eIToolCommand.h 
* Version : 2.0
* Author  : ZhaoY
*
* 工具类命令基类
*/ 

#pragma once

#include "ivrframework_global.h"
#include "eCommon.h"
#include "eICommand.h"
#include <QCursor>

class QContextMenuEvent;
class QMouseEvent;
class QWheelEvent;
class QKeyEvent;
class QObject;
class QEvent;

namespace IVRFramework {

	class IVRFRAMEWORK_EXPORT eIToolCommand : public eICommand
	{
		DECLARE_CLASS(eICommand)

	public:
		eIToolCommand();
		virtual ~eIToolCommand();

	public:
		/**
		* @brief 是否选中状态
		* @return true：选中；false：未选中。
		* @remark 此选项只在命令是工具插件时才使用，且同一时刻，最多一个Tool在选中状态。
		*/
		virtual bool IsChecked();

		/*!
		*@brief 命令执行函数
		*@author chengdz 2018年1月9日
		*@return virtual void
		*/
		virtual void Execute(QObject* sender, QString param);

		/**
		* @brief 获取光标
		* @return 光标对象
		*/
		virtual QCursor GetCursor();

		/**
		* @brief 激活工具
		* @return
		*/
		virtual bool Activate();

		/**
		* @brief
		* @return
		*/
		virtual bool Deactivate();

		/**
		* @brief 菜单操作
		* @param[in] event 菜单事件参数
		* @return
		*/
		virtual bool OnContextMenu(QContextMenuEvent* event);

		/**
		* @brief 鼠标双击操作
		* @param[in] event 鼠标事件参数
		*/
		virtual void OnDoubleClick(QMouseEvent* event);

		/**
		* @brief 键盘按键按下操作
		* @param[in] event 键盘事件参数
		*/
		virtual void OnKeyDown(QKeyEvent* event);

		/**
		* @brief 键盘按键抬起操作
		* @param[in] event 键盘事件参数
		*/
		virtual void OnKeyUp(QKeyEvent* event);

		/**
		* @brief 鼠标按下操作
		* @param[in] event 鼠标事件参数
		*/
		virtual void OnMouseDown(QMouseEvent* event);

		/**
		* @brief 鼠标移动操作
		* @param[in] event 鼠标事件参数
		* @remark 需要有按键操作
		*/
		virtual void OnMouseMove(QMouseEvent* event);

		/**
		* @brief 鼠标抬起操作
		* @param[in] event 鼠标事件参数
		*/
		virtual void OnMouseUp(QMouseEvent* event);

		/**
		* @brief 鼠标移动操作
		* @param[in] event 鼠标事件参数
		* @remark 无鼠标按键时才触发
		*/
		virtual void OnJustMouseMove(QMouseEvent* event);

		/**
		* @brief 焦点进入操作
		* @param [in] event 事件参数
		*/
		virtual void OnEnterEvent(QEvent* event);

		/**
		* @brief 焦点离开操作
		* @param [in] event 事件参数
		* @return
		*/
		virtual void OnLeaveEvent(QEvent* event);

		/**
		* @brief 鼠标滚轮操作
		* @param[in] event 鼠标事件参数
		* @return 是否响应
		*/
		virtual bool OnWheelEvent(QWheelEvent* event);

	protected:

		/**
		* @brief 设置当前操作视图光标
		* @param[in] cursor 光标对象
		*/
		virtual void SetCurrentCursor(const QCursor& cursor);

	protected:
		QCursor m_pCursor;
	};
}