#include "IVRFramework/eAppInfo.h"
#include <QFile>
#include <QDir>
#include <QDomDocument>
#include "eLanguageManager.h"

using namespace IVRFramework;

eAppInfo* eAppInfo::GetInstance()
{
	static eAppInfo s_AppInfo;
	return &s_AppInfo;
}

eAppInfo::eAppInfo()
	:m_WorkPath("")
	, m_UIConfigPath("")
	, m_ProductName("")
	, m_ProductIcon("")
	, m_AppPath("")
{
	m_pLanguageManager = new eLanguageManager();
}

QString eAppInfo::GetWorkPath() const
{
	return m_WorkPath;
}

QString eAppInfo::UIConfigPath() const
{
	return m_UIConfigPath;
}

eAppInfo::~eAppInfo()
{

}

void eAppInfo::SetAppPath(const QString& strAppPath)
{
	m_AppPath = strAppPath;

	QDir dir(m_AppPath);
	dir.cdUp();
	dir.cdUp();
	m_WorkPath = dir.path() + "/";
}

QString eAppInfo::GetAppPath() const
{
	return m_AppPath;
}

QString eAppInfo::ProductVersion() const
{
	return m_ProductVersion;
}

QString eAppInfo::ProductName() const
{
	return m_ProductName;
}

QString eAppInfo::ProductIcon() const
{
	return m_ProductIcon;
}

bool eAppInfo::LoadConfig()
{
	QString strConfigFile(eAppInfo::GetInstance()->GetWorkPath() + "Config/AppConfig.xml");

	if (strConfigFile.isEmpty())
		return false;

	QFile* pFile = new QFile(strConfigFile);
	if (!pFile->open(QFile::ReadOnly | QFile::Text))
	{
		pFile->close();
		delete pFile;
		return false;
	}

	QString strError;
	int errLin = 0, errCol = 0;

	QDomDocument document;
	if (!document.setContent(pFile, false, &strError, &errLin, &errCol))
	{
		pFile->close();
		delete pFile;
		return false;
	}
	if (document.isNull())
	{
		pFile->close();
		delete pFile;
		return false;
	}

	QDomElement dRoot = document.documentElement();

	QDomElement eleVersion = dRoot.firstChildElement("ProductVersion");
	m_ProductVersion = eleVersion.text();

	QDomElement eleProductName = dRoot.firstChildElement("ProductName");
	m_ProductName = eleProductName.text();

	QDomElement eleProductIcon = dRoot.firstChildElement("ProductIcon");
	m_ProductIcon = eleProductIcon.text();

	QDomElement eleUIConfigPath = dRoot.firstChildElement("UIConfigPath");
	m_UIConfigPath = eleUIConfigPath.text();

	m_pLanguageManager->LoadConfigFile(GetWorkPath() + "Config/Language/LanguageConfig.xml");

	if (pFile)
	{
		pFile->close();
		delete pFile;
	}

	return true;
}
