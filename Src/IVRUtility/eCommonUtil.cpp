#include "eCommonUtil.h"
#include <QFile>

using namespace IVRUtility;

QFile* eCommonUtil::OpenXml(QString filePath, QDomDocument& document, QDomElement& dRoot)
{
	QFile* pFile = new QFile(filePath);
	if (!pFile->open(QFile::ReadOnly | QFile::Text))
	{
		delete pFile;
		return NULL;
	}

	QString strError;
	int errLin = 0, errCol = 0;
	if (!document.setContent(pFile, false, &strError, &errLin, &errCol))
	{
		delete pFile;
		return NULL;
	}
	if (document.isNull())
	{
		delete pFile;
		return NULL;
	}
	dRoot = document.documentElement();
	return pFile;
}
