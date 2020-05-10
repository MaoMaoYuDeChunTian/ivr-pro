#pragma once
#include <QTextStream>
#include "IVRUtility/ivrutility_global.h"

namespace IVRUtility
{
class IVRUTILITY_EXPORT eLog
{
public:
	enum eLogType
	{
		wERROR = 0,
		wSUCCESS = 1,
	};
public:
	static eLog* GetInstance();

private:
	eLog(void);

public:
	~eLog();

public:
	bool Init(QString outDir);
	void Log(QString moduleName, QString className, QString funcName, eLogType enMessagType, QString message);

private:
	QTextStream* m_pStream;

};
}
