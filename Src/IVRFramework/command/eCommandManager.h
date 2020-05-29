#pragma once
#include <map>
#include <vector>
#include <QString>
#include <QtCore/QTimer> 
#include <QtWidgets/QAction> 
#include <QtWidgets/QWidget>
#include "IVRFramework/command/eICommandSet.h"
#include "IVRFramework/command/eCommandDelegate.h"
#include "IVRFramework/ivrframework_global.h"

namespace IVRFramework {

class IVRFRAMEWORK_EXPORT eCommandManager : public QObject
{
	Q_OBJECT

public:
	static eCommandManager* GetInstance();

private:

	eCommandManager(void);

public:

	~eCommandManager(void);

public:
	bool AddCommandSet(eICommandSet* pCommandSet);
	eICommandSet* GetCommandSet(QString strCommandSetName);
	bool RemoveCommandSet(QString strCommandSetName);
	eICommand* GetCommand(const QString& moduleName, const QString& cmdName);
public:
	bool ConnectCmd(const QString& moduleName, const QString& cmdName, const QString& cmdType, QObject* pSender, eCommandDelegate::QControlType controlType, QString strParam = "");
	eCommandDelegate* GetCommandDelegate(QObject* pSender);

private slots:
	void OnUpdateState();
	void OnCommandTriggered();
	void OnCombCurIndexChanged(const QString & text);

private:
	QMap<QString, eICommandSet*> m_CommandSets;
	QVector<eCommandDelegate*> m_lstCommandDelegate;
	QTimer m_cmdTimer;
};
}//namespace IVRFramework
