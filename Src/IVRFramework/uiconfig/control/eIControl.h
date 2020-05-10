#pragma once
#include <QString>
#include <QtXml/QDomDocument>
#include <QtitanRibbon.h>
#include "IVRFramework/ePluginManager.h"
#include "IVRFramework/eCommandManager.h"
#include "IVRFramework/eFrameExtensionManager.h"
#include "IVRFramework/eFramework_global.h"

namespace IVRFramework {

//�ؼ�ģ�ͻ���
class PIEPROFRAMEWORK_EXPORT eIControl
{
public:
	///<summary>
	///�ؼ�����ö��
	///</summary>
	enum enControlType
	{
		None = -1,
		Button = 0,//��ť
		CheckBox,//��ѡ��ť
		RadioButton,//����ѡ��ť
		HSeparatorLine,//ˮƽ�ָ���
		VSeparatorLine,//��ֱ�ָ���
		ButtonGroup,//��Ҫ����ʵ��RadioButton����ѡ��
		PopupButton,//������ť
		SplitButton,//Split��ť
		ComboBox,//�����б��
		Menu,//�˵��ؼ�
		GalleryControl,//չ��ؼ�
		UserControl,//�û��Զ���ؼ�
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
	virtual QObject* ToRibbonCtrl(Qtitan::RibbonGroup *rGroup) = 0;
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
	static std::map<QString, enControlType> s_ControlTypeDict;

};
}
