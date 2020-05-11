#pragma once
#include <QString>
#include <QToolBar>
#include <QMenu>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include "IVRFramework/ePluginManager.h"
#include "IVRFramework/command/eCommandManager.h"
#include "IVRFramework/frame_extension/eFrameExtensionManager.h"
#include "IVRFramework/ivrframework_global.h"

namespace IVRFramework {

class IVRFRAMEWORK_EXPORT eIControl
{
public:
	///<summary>
	//控件类型枚举
	///</summary>
	enum enControlType
	{
		None = -1,
		Button = 0,//按钮
		CheckBox,//勾选按钮
		RadioButton,//互斥选择按钮
		HSeparatorLine,//水平分割线
		VSeparatorLine,//垂直分割线
		ButtonGroup,//主要用于实现RadioButton互斥选择
		PopupButton,//下拉按钮
		SplitButton,//Split按钮
		ComboBox,//下拉列表框
		Menu,//菜单控件
		UserControl,//用户自定义控件
	};

public:
	eIControl();
	virtual ~eIControl();

public://get
	enControlType GetControlType();
	
	bool IsEnable();
	QString GetCaption();
	QString GetCommandName();
	QString GetLibrary();
	QString GetToolTip();
	QString GetIcon();
	bool IsCheckable();
	QString GetShortcut();
	QString GetParameter();
	QString GetSize();
	bool IsAddToQuickAccess();
	QObject* GetTag();

public://set
	void SetEnable(bool bEnable);
	void SetCaption(QString caption);
	void SetCommandName(QString command);
	void SetLibrary(QString library);
	void SetToolTip(QString toolTip);
	void SetIcon(QString pIcon);
	void SetCheckable(bool bCheckable);
	void SetShortcut(QString shortcut);
	void SetParameter(QString parameter);
	void SetSize(QString size);
	void SetIsAddToQuickAccess(bool bAddToQuickAccess);
	void SetTag(QObject* tag);

protected:
	void SetControlType(enControlType controlType);

public:
	virtual bool FromXmlElement(const QDomElement& xmlElement);
	virtual QDomElement ToXmlElement(QDomDocument xmlDoc);
	virtual QObject* ToToolBarCtrl(QToolBar* pToolBar);
	virtual QObject* ToMenuBarCtrl(QMenu* pMenu, QToolBar* pToolBar);

public:
	static enControlType GetType(QString typeName);
	static eIControl* CreateControl(enControlType controlType);

private:
	enControlType m_ControlType;
	bool m_bEnable;
	QString m_Caption;
	QString m_CommandName;
	QString m_Library;
	QString m_Parameter;
	QString m_ToolTip;
	QString m_Icon;
	bool m_bCheckable;
	QString m_Shortcut;
	QString m_Size;
	bool m_bAddToQuickAccess;
	QObject* m_tag;

private:
	static QMap<QString, enControlType> s_ControlTypeDict;

};
}
