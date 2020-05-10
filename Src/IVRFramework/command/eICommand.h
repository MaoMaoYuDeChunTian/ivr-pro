/* Copyright (C) 2019, GDI. All rights reserved.
*
* File    : eICommand.h 
* Version : 2.0
* Author  : ZhaoY
*
* 命令基类

*/ 

#pragma once

#pragma once
#include <QJsonObject>
#include <QString>
#include <QMap>
#include "IVRFramework/ivrframework_global.h"
#include "IVRFramework/eCommon.h"

class QObject;
namespace IVRFramework {

	class eICommandListener;

	class IVRFRAMEWORK_EXPORT eICommand
	{
		//子类必须加此宏定义
		DECLARE_CLASS(eICommand)

	public:
		eICommand(void);
		virtual ~eICommand(void);

	public:
		/**
		* @brief 命令是否可用
		* @return true：可用；false：不可用。
		*/
		virtual bool IsEnable() = 0;

		/*!
		*@brief 命令执行函数
		*@return virtual void
		*/
		virtual void Execute(QObject* sender, QString param) = 0;

		/*!
		*@brief  让js调的命令必须重写此接口
		*@param[in]   const QJsonObject &json
		*@return virtual void
		*/
		virtual void Execute(const QJsonObject &json);

	public:
		/*!
		*@brief  添加命令监听
		*@param[in]   eICommandListener* pCommandListener
		*/
		bool AddListener(eICommandListener* pCommandListener);

		/*!
		*@brief  获得指定名称的命令监听
		*@param[in]   QString strListenerName
		*@return eICommandListener*
		*/
		eICommandListener* GetListener(QString strListenerName);

		/*!
		*@brief  命令执行前通知监听
		
		*/
		void BeforeExecNotify(QObject* sender, QString param);

		/*!
		*@brief  命令执行后通知监听
		*/
		void AfterExecNotify(QObject* sender, QString param);

	private:
		//命令监听集合
		QMap<QString, eICommandListener*> m_CommandListenerSet;

	};


	/*!
	*@brief  根据模块名，命令名和参数调用命令
	*@author chengdz 2017年12月19日
	*@param[in]   std::string moduleName 模块名
	*@param[in]   std::string commandName 命令名
	*@param[in]   std::string jsonParam json参数
	*/
	//IVRFRAMEWORK_EXPORT void ExecuteCommand(std::string moduleName, std::string commandName, std::string jsonParam);
}
