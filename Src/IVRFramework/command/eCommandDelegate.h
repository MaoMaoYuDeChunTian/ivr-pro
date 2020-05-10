#pragma once
#include <QtWidgets/QAction> 
#include <QtWidgets/QAbstractButton>
#include "IVRFramework/command/eICommand.h"
#include "IVRFramework/ivrframework_global.h"

namespace IVRFramework {

//命令代理
class IVRFRAMEWORK_EXPORT eCommandDelegate
{
public:
	enum QControlType
	{
		Action,
		Button,
		RibbonGallery,
		ComboBox,
	};
public:
	eCommandDelegate(const QString& moduleName, eICommand* command, QString cmdParam, QObject* pSender, QControlType controlType);
	~eCommandDelegate();

public:
	/**
	* @brief 获取DLL模块名称
	* @return DLL模块名称
	*/
	QString GetModuleName();

	/**
	* @brief 获取命令插件
	* @return 命令插件对象
	*/
	eICommand* GetCommand();

	/**
	* @brief 获取命令参数
	* @return 命令插件对象
	*/
	QString GetCmdParam();

	/**
	* @brief 获取信号发送者
	* @return QObject*
	*/
	QObject* GetSender();

	/**
	* @brief 获取信号发送者控件类型
	* @return QControlType
	*/
	QControlType GetControlType();

	/**
	* @brief 设置是否选中
	*/
	void SetChecked(bool bChecked);

	/**
	* @brief 获取是否选中
	* @return QControlType
	*/
	bool IsChecked();

	/**
	* @brief 设置是否在按钮组里
	*/
	void SetInButtonGroup(bool bInButtonGroup);

	/**
	* @brief 获取是否在按钮组里
	* @return QControlType
	*/
	bool IsInButtonGroup();

private:
	QString m_moduleName;//动态库名称
	eICommand* m_pCommand;//命令
	QString m_cmdParam;//命令参数
	QObject* m_pSender;	//信号发送者
	QControlType m_enControlType;//控件类型
	bool m_bChecked;//是否是选中状态
	bool m_bInButtonGroup;//是否在按钮组里
};

}
