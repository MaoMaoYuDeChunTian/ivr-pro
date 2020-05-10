/* Copyright (C) 2019, GDI. All rights reserved.
*
* File    : eLanguageManager.h
* Version : 2.0
* Author  : ZhaoY
*
* 翻译类
*/

#pragma once

#include "IVRFramework/ivrframework_global.h"
#include <QString>
#include <QList>

class QTranslator;

namespace IVRFramework
{
	class IVRFRAMEWORK_EXPORT eLanguageManager
	{
	private:
		struct Language
		{
			QString name;
			QString dir;
		};
	public:
		eLanguageManager();
		~eLanguageManager();

	public:
		/**
		* @brief 加载语言配置文件
		* @param [in] strFileName 文件路径
		* @return bool
		*/
		bool LoadConfigFile(const QString& strFileName);

		/**
		* @brief 获取语言列表
		* @return QList<QString>
		*/
		QList<QString> GetLanguageList();

		/**
		* @brief 设置当前的语言
		* @param [in] str 要设置的语言
		* @return
		*/
		void SetCurLanguage(const QString& strCurLanguage);

		/**
		* @brief 获取当前的语言
		* @return  QString
		*/
		QString GetCurLanguage();

	private:
		/**
		* @brief 安装翻译器
		* @return
		*/
		void InstallTranslator();

		/**
		* @brief 卸载翻译器
		* @return
		*/
		void UninstallTranslator();

	private:
		QString m_CurLanguage;//当前语言
		QList<Language> m_LanguageList;//语言列表
		QList<QTranslator*> m_TranslatorList;//翻译文件列表
	};
}