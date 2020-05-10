#include "eLanguageManager.h"
#include <QDomDocument>
#include <QFile>
#include <QDir>
#include <QApplication>
#include <QTranslator>
#include "eAppInfo.h"
#include "IVRUtility/eCommonUtil.h"

using namespace IVRFramework;
using namespace IVRUtility;

eLanguageManager::eLanguageManager()
{

}

eLanguageManager::~eLanguageManager()
{

}

bool eLanguageManager::LoadConfigFile(const QString & strFileName)
{
	QDomDocument document;
	QDomElement dRoot;
	QFile* pFile = eCommonUtil::OpenXml(strFileName, document, dRoot);

	m_CurLanguage = dRoot.attribute("curLanguage");
	QDomNodeList LanguageNodeList = dRoot.elementsByTagName("Language");
	for (int i = 0; i < LanguageNodeList.size(); ++i)
	{
		QDomElement LanguageElement = LanguageNodeList.at(i).toElement();

		Language theLanguage;
		theLanguage.name = LanguageElement.attribute("name");
		theLanguage.dir = LanguageElement.attribute("dir");
		m_LanguageList.push_back(theLanguage);
	}

	delete pFile;
	pFile = NULL;

	//设置当前语言
	SetCurLanguage(m_CurLanguage);
	return true;
}

QList<QString> eLanguageManager::GetLanguageList()
{
	QList<QString> strLanguageList;
	for (int i = 0; i < m_LanguageList.size(); ++i)
	{
		strLanguageList.push_back(m_LanguageList[i].name);
	}
	return strLanguageList;
}

void eLanguageManager::SetCurLanguage(const QString& strCurLanguage)
{
	m_CurLanguage = strCurLanguage;
	UninstallTranslator();
	InstallTranslator();
}

QString eLanguageManager::GetCurLanguage()
{
	return m_CurLanguage;
}

void eLanguageManager::InstallTranslator()
{
	QString strCurLanguageDir;
	for (int i = 0; i < m_LanguageList.size(); ++i)
	{
		if (m_LanguageList[i].name == m_CurLanguage)
		{
			strCurLanguageDir = m_LanguageList[i].dir;
		}
	}
	QString strTranslatorFileDir = eAppInfo::GetInstance()->GetWorkPath() + "Config/Language/" + strCurLanguageDir;

	//获取国际化qm文件
	QDir dir(strTranslatorFileDir);
	dir.setFilter(QDir::Files | QDir::NoSymLinks);

	QFileInfoList list = dir.entryInfoList();
	QFileInfoList::iterator itr;

	for (itr = list.begin(); itr != list.end(); ++itr)
	{
		QFileInfo fileInfo = *itr;
		if (!fileInfo.suffix().compare("qm", Qt::CaseInsensitive))
		{
			QString strFile = fileInfo.filePath();
			QTranslator *pAppTranslator = new QTranslator();
			m_TranslatorList.push_back(pAppTranslator);
			pAppTranslator->load(strFile);
			qApp->installTranslator(pAppTranslator);
		}
	}
}

void eLanguageManager::UninstallTranslator()
{
	QList<QTranslator*>::iterator it;
	for (it = m_TranslatorList.begin(); it != m_TranslatorList.end(); ++it)
	{
		QTranslator *pAppTranslator = *it;
		qApp->removeTranslator(pAppTranslator);
		delete pAppTranslator;
	}
	m_TranslatorList.clear();
}