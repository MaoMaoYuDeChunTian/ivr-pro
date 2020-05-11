#include "IVRUtility/eLog.h"
#include <QDateTime>
#include <QFile>

using namespace std;
using namespace IVRUtility;

eLog* eLog::GetInstance()
{
	static eLog s_wLog;
	return &s_wLog;
}

eLog::eLog(void)
	:m_pStream(nullptr)
{

}

eLog::~eLog()
{

}

bool eLog::Init(QString outDir)
{
	QString qstrLogFile = outDir + "eLog.txt";
	QFile file(qstrLogFile);
	if (!file.open(QFileDevice::WriteOnly))
	{
		file.close();
		return false;
	}

	m_pStream = new QTextStream(&file);
	m_pStream->setCodec("utf-8");

	QDateTime beginDateTime = QDateTime::currentDateTime();
	QString dataTime = beginDateTime.toString("yyyy/MM/dd/hh:mm:ss:zzz");
	QString info = "=====================程序启动:";
	(*m_pStream) << info<< dataTime << endl;

	return true;
}

void eLog::Log(QString moduleName, QString className, QString funcName, eLogType enMessagType, QString message)
{
	QDateTime curDateTime = QDateTime::currentDateTime();
	QString dataTime = curDateTime.toString("[yyyy/MM/dd/hh:mm:ss:zzz]");
	QString strMessageType = "error:";
	if (enMessagType == wSUCCESS)
	{
		strMessageType = "success:";
	}
	(*m_pStream) << "-" << dataTime << endl;
	(*m_pStream) << "-" << strMessageType << moduleName << "$" << className << "$" << funcName << "$" << message << endl;
}
