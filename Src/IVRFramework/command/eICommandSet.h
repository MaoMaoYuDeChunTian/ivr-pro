#pragma once
#include <map>
#include <QObject>
#include <QString>
#include "IVRFramework/eCommon.h"
#include "IVRFramework/command/eICommand.h"
#include "IVRFramework/command/eIToolCommand.h"
#include "IVRFramework/ivrframework_global.h"

namespace IVRFramework {

	class IVRFRAMEWORK_EXPORT eICommandSet
	{
		DECLARE_CLASS(eICommandSet)

	public:

		eICommandSet(void);


		virtual ~eICommandSet(void);

	public:

		virtual void RegisterCommands() = 0;


		bool AddCommand(eICommand* pCommand);


		eICommand* GetCommand(QString strCommandName);

	private:
		QMap<QString, eICommand*> m_CommandSet;

	};

}//namespace IVRFramework
