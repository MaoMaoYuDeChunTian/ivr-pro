#include "IVRFramework/eIControl.h"
#include "IVRFramework/eButtonControl.h"
#include "IVRFramework/eCheckBoxControl.h"
#include "IVRFramework/eRadioButtonControl.h"
#include "IVRFramework/eVSeparatorLine.h"
#include "IVRFramework/eHSeparatorLine.h"
#include "IVRFramework/eButtonGroupControl.h"
#include "IVRFramework/ePopupButtonControl.h"
#include "IVRFramework/eSplitButtonControl.h"
#include "IVRFramework/eComboBoxControl.h"
#include "IVRFramework/eMenuControl.h"
#include "IVRFramework/eGalleryControl.h"
#include "IVRFramework/eUserControl.h"

using namespace IVRFramework;

std::map<QString, eIControl::enControlType> eIControl::s_ControlTypeDict;

eIControl::eIControl()
	:m_ControlType(None),
	m_bEnable(false),
	m_Caption(""),
	m_CommandName(""),
	m_Library(""),
	m_ToolTip(""),
	m_Icon(""),
	m_bCheckable(false),
	m_Shortcut(""),
	m_Parameter(""),
	m_Size("large"),
	m_bAddToQuickAccess(false),
	m_tag(NULL)
{

}

eIControl::~eIControl()
{
}

eIControl::enControlType eIControl::GetControlType()
{
	return m_ControlType;
}

bool eIControl::IsEnable()
{
	return m_bEnable;
}

QString eIControl::GetCaption()
{
	return m_Caption;
}

QString eIControl::GetCommandName()
{
	return m_CommandName;
}

QString eIControl::GetLibrary()
{
	return m_Library;
}

QString eIControl::GetToolTip()
{
	return m_ToolTip;
}

QString eIControl::GetIcon()
{
	if (m_Icon.isEmpty())
	{
		return m_CommandName + ".png";
	}
	else
	{
		return m_Icon;
	}
}

bool eIControl::IsCheckable()
{
	return m_bCheckable;
}

QString eIControl::GetShortcut()
{
	return m_Shortcut;
}

QString eIControl::GetParameter()
{
	return m_Parameter;
}

QString eIControl::GetSize()
{
	return m_Size;
}

bool eIControl::IsAddToQuickAccess()
{
	return m_bAddToQuickAccess;
}

QObject* eIControl::GetTag()
{
	return m_tag;
}

void eIControl::SetControlType(enControlType controlType)
{
	m_ControlType = controlType;
}

void eIControl::SetEnable(bool bEnable)
{
	m_bEnable = bEnable;
}

void eIControl::SetCaption(QString caption)
{
	m_Caption = caption;
}

void eIControl::SetCommandName(QString command)
{
	m_CommandName = command;
}

void eIControl::SetLibrary(QString library)
{
	m_Library = library;
}

void eIControl::SetToolTip(QString toolTip)
{
	m_ToolTip = toolTip;
}

void eIControl::SetIcon(QString pIcon)
{
	if (pIcon.contains('.') == false)
	{
		pIcon += ".png";
	}
	m_Icon = pIcon;
}

void eIControl::SetCheckable(bool bCheckable)
{
	m_bCheckable = bCheckable;
}

void eIControl::SetShortcut(QString shortcut)
{
	m_Shortcut = shortcut;
}

void eIControl::SetParameter(QString parameter)
{
	m_Parameter = parameter;
}

void eIControl::SetSize(QString size)
{
	m_Size = size;
}

void eIControl::SetIsAddToQuickAccess(bool bAddToQuickAccess)
{
	m_bAddToQuickAccess = bAddToQuickAccess;
}

void eIControl::SetTag(QObject* tag)
{
	m_tag = tag;
}

bool eIControl::FromXmlElement(const QDomElement & xmlElement)
{
	this->SetEnable(xmlElement.attribute("enable").toInt());
	this->SetCaption(xmlElement.attribute("caption"));
	this->SetCommandName(xmlElement.attribute("command"));
	this->SetLibrary(xmlElement.attribute("library"));
	this->SetParameter(xmlElement.attribute("parameter"));
	this->SetToolTip(xmlElement.attribute("tip"));
	this->SetIcon(xmlElement.attribute("icon"));
	this->SetSize(xmlElement.attribute("size"));
	this->SetCheckable(xmlElement.attribute("checkable").toInt());
	this->SetShortcut(xmlElement.attribute("shortcut"));
	this->SetIsAddToQuickAccess(xmlElement.attribute("isaddQuickaccess").toInt());
	//this->SetDescription(xmlElement.attribute("description"));
	//this->SetCmdType(xmlElement.attribute("cmdType"));
	return true;
}

QDomElement eIControl::ToXmlElement(QDomDocument xmlDoc)
{
	return QDomElement();
}

QObject* eIControl::ToToolBarCtrl(QToolBar* pToolBar)
{
	return NULL;
}

QObject* eIControl::ToMenuBarCtrl(QMenu* pMenu, QToolBar* pToolBar)
{
	return NULL;
}

eIControl::enControlType eIControl::GetType(QString typeName)
{
	if (s_ControlTypeDict.size() <= 0)
	{
		s_ControlTypeDict["button"] = eIControl::Button;
		s_ControlTypeDict["checkbox"] = eIControl::CheckBox;
		s_ControlTypeDict["radiobutton"] = eIControl::RadioButton;
		s_ControlTypeDict["separator"] = eIControl::VSeparatorLine;
		s_ControlTypeDict["vseparator"] = eIControl::VSeparatorLine;
		s_ControlTypeDict["hseparator"] = eIControl::HSeparatorLine;

		s_ControlTypeDict["buttongroup"] = eIControl::ButtonGroup;
		s_ControlTypeDict["popupbutton"] = eIControl::PopupButton;
		s_ControlTypeDict["splitbutton"] = eIControl::SplitButton;
		s_ControlTypeDict["combobox"] = eIControl::ComboBox;
		s_ControlTypeDict["menu"] = eIControl::Menu;
		s_ControlTypeDict["gallerycontrol"] = eIControl::GalleryControl;
		s_ControlTypeDict["usercontrol"] = eIControl::UserControl;
	}
	if (s_ControlTypeDict.find(typeName) != s_ControlTypeDict.end())
	{
		return s_ControlTypeDict[typeName];
	}
	return eIControl::None;
}

eIControl* eIControl::CreateControl(eIControl::enControlType controlType)
{
	eIControl* pControl = NULL;

	switch (controlType)
	{
	case eIControl::Button:
		{
			pControl = new eButtonControl();
		}
		break;
	case eIControl::CheckBox:
		{
			pControl = new eCheckBoxControl();
		}
		break;
	case eIControl::RadioButton:
		{
			pControl = new eRadioButtonControl();
		}
		break;
	case eIControl::VSeparatorLine:
		{
			pControl = new eVSeparatorLine();
		}
		break;
	case eIControl::HSeparatorLine:
		{
			pControl = new eHSeparatorLine();
		}
		break;
	case eIControl::ButtonGroup:
		{
			pControl = new eButtonGroupControl();
		}
		break;
	case eIControl::PopupButton:
		{
			pControl = new ePopupButtonControl();
		}
		break;
	case eIControl::SplitButton:
		{
			pControl = new eSplitButtonControl();
		}
		break;
	case eIControl::ComboBox:
		{
			pControl = new eComboBoxControl();
		}
		break;
	case eIControl::Menu:
		{
			pControl = new eMenuControl();
		}
		break;
	case eIControl::GalleryControl:
		{
			pControl = new eGalleryControl();
		}
		break;
	case eIControl::UserControl:
		{
			pControl = new eUserControl();
		}
		break;
	default:
		{
			pControl = new eButtonControl();
		}
	}
	return pControl;
}