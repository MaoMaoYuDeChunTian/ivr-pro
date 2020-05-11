#pragma once
#include <map>
#include <QList>
#include <QString>
#include "IVRFramework/eIPlugin.h"
#include "IVRFramework/ivrframework_global.h"

class QLibrary;

namespace IVRFramework{

class IVRFRAMEWORK_EXPORT ePluginManager
{
public:

	static ePluginManager* GetInstance();

private:

	ePluginManager(void);

public:

	~ePluginManager(void);

public:
	typedef QMap<int, QList<eIPlugin*> > ListenerGroup; 

public:

	bool LoadPlugins(QString workPath, QString pluginConfigFile);


	int LoadPlugin(const QString & dllFilePath);


	bool UnLoadPlugins();

	bool UnLoadPlugin(eIPlugin* pPlugin);

    QMap<QString, eIPlugin*>  GetAllPlugins();

public:
	
	void AddListener(int nEventType, eIPlugin* pPlugin);


	void RemoveListener(int nEventType, eIPlugin* pPlugin);

	void DispatchEvent(eIPlugin* pPlugin, int nEventType, void* pEventData);

public:
#ifdef _WIN32
	typedef void (__stdcall *Callback_LoadPlugin)(eIPlugin* pPlugin);
#else
        typedef void (*Callback_LoadPlugin)(eIPlugin* pPlugin);
#endif

	void SetLoadPluginCallBack(Callback_LoadPlugin pCallbackLoadPlugin);

private:
	bool LoadPlugin(QLibrary *pLib);
	bool FileExist(const QString& dllFilePath) const;
	bool IsLoaded(const QString& dllFilePath) const;


	bool LoadFrameExtensions();

private:
	QMap<QString, eIPlugin*> m_listPlugins;
	QList<QLibrary*> m_lstLibs;
	Callback_LoadPlugin m_pCallbackLoadPlugin;

	ListenerGroup m_listeners;
};
}//namespace IVRFramework
