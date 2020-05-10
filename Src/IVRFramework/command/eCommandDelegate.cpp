#include "IVRFramework/command/eCommandDelegate.h"

using namespace IVRFramework;

eCommandDelegate::eCommandDelegate(const QString& moduleName, eICommand* command, QString cmdParam, QObject* pSender, eCommandDelegate::QControlType controlType)
{
	m_moduleName = moduleName;
	m_pCommand = command;
	m_cmdParam = cmdParam;
	m_pSender = pSender;
	m_enControlType = controlType;
	m_bChecked = false;
	m_bInButtonGroup = false;
}

eCommandDelegate::~eCommandDelegate()
{

}

QString eCommandDelegate::GetModuleName()
{
	return m_moduleName;
}

eICommand* eCommandDelegate::GetCommand()
{
	return m_pCommand;
}

QString eCommandDelegate::GetCmdParam()
{
	return m_cmdParam;
}

QObject* eCommandDelegate::GetSender()
{
	return m_pSender;
}

eCommandDelegate::QControlType eCommandDelegate::GetControlType()
{
	return m_enControlType;
}

void eCommandDelegate::SetChecked(bool bChecked)
{
	m_bChecked = bChecked;
}

bool eCommandDelegate::IsChecked()
{
	return m_bChecked;
}

void eCommandDelegate::SetInButtonGroup(bool bInButtonGroup)
{
	m_bInButtonGroup = bInButtonGroup;
}

bool eCommandDelegate::IsInButtonGroup()
{
	return m_bInButtonGroup;
}
